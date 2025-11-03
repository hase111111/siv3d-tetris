#include "penalty_updater.h"

#include "my_assert.h"

namespace mytetris {

PenaltyUpdater::PenaltyUpdater(const std::shared_ptr<IScoreCalculator>& player,
                               const std::shared_ptr<IScoreCalculator>& enemy)
    : player_score_calculator_ptr_(player), enemy_score_calculator_ptr_(enemy) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(player_score_calculator_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_score_calculator_ptr_);
}

std::tuple<int, int> PenaltyUpdater::Update() {
  // プレイヤーを正, 敵を負としたスコアを取得.
  const int player_score = player_score_calculator_ptr_->GetScore();
  const int enemy_score = enemy_score_calculator_ptr_->GetScore();
  const int score_difference = player_score - enemy_score;

  // 値をリセット.
  player_score_calculator_ptr_->Update();
  enemy_score_calculator_ptr_->Update();

  if (score_difference != 0) {
    ++dic_counter_;
    if (0 < score_difference * penalty_lines_) {
      counter_ = std::max(0, counter_ - penalty_interval_ / 2 / dic_counter_);
    } else {
      counter_ = std::max(0, counter_ - penalty_interval_ / dic_counter_);
    }
  }

  // ペナルティライン数を更新.
  penalty_lines_ += score_difference;

  if (penalty_lines_ == 0) {
    counter_ = 0;
    dic_counter_ = 0;
    return std::make_tuple(0, 0);
  } else {
    ++counter_;

    if (counter_ < penalty_interval_) {
      return std::make_tuple(0, 0);
    } else {
      // ペナルティライン数を返す.
      const int res = penalty_lines_;
      penalty_lines_ = 0;
      return std::make_tuple(res < 0 ? -res : 0, 0 < res ? res : 0);
    }
  }
}

}  // namespace mytetris
