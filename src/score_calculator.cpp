#include "score_calculator.h"

namespace mytetris {

void ScoreCalculator::Update() {
  if (score_difference_ > 0) {
    // スコア差分表示カウンタを進める.
    ++diff_display_counter_;
    if (diff_display_counter_ >= diff_display_duration_) {
      // 表示時間を超えたらスコア差分をリセット.
      score_difference_ = 0;
      diff_display_counter_ = 0;
    }
  }
}

void ScoreCalculator::AddScore(const int lines_num, const bool is_tspin,
                               bool is_perfect_clear) {
  if (lines_num <= 0) {
    // ラインを消していない場合はスコアを加算しない.
    return;
  }

  // コンボ数を加算.
  ++combo_num_;

  // コンボボーナス加算.
  int diff{0};
  diff += Get(combo_bonus_, combo_num_ - 1);

  if (is_perfect_clear) {
    // パーフェクトクリア時のスコア加算.
    diff += Get(perfect_clear_scores_, lines_num - 1);
  } else {
    diff += Get(line_clear_scores_, lines_num - 1);
  }

  score_ += diff;
  score_difference_ += diff;
  diff_display_counter_ = 0;
}

void ScoreCalculator::AddDropScore(const int drop_distance,
                                   const bool is_hard_drop) {
  const int diff = is_hard_drop ? drop_distance * hard_drop_score_
                                : drop_distance * drop_score_;
  score_ += diff;
  score_difference_ += diff;
  diff_display_counter_ = 0;
}

int ScoreCalculator::Get(const std::vector<int> v, int idx) const {
  if (idx < 0) {
    return 0;
  }
  if (idx >= static_cast<int>(v.size())) {
    return v.back();
  }
  return v[idx];
}

}  // namespace mytetris
