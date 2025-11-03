#include "battle_announce.h"

#include "game_const.h"
#include "log_print.h"
#include "my_format.h"

namespace mytetris {

BattleAnnounce::BattleAnnounce(
    const std::shared_ptr<const ResourceContainer>& resource_container)
    : font_view_(resource_container->GetFont("default")) {}

void BattleAnnounce::SetClearLineAnnounce(const int line_num, const int combo,
                                          const bool is_tspin,
                                          const bool is_btb) {
  clear_line_announce_.clear();

  if (is_tspin && line_num == 3) {
    clear_line_announce_.push_back("T-Spin Triple!");
  } else if (is_tspin && line_num == 2) {
    clear_line_announce_.push_back("T-Spin Double!");
  } else if (is_tspin && line_num == 1) {
    clear_line_announce_.push_back("T-Spin Single!");
  } else if (line_num == 4) {
    clear_line_announce_.push_back("Tetris!");
  } else if (4 < line_num) {
    clear_line_announce_.push_back("Tetris+!");
  } else if (line_num == 3) {
    clear_line_announce_.push_back("Triple!");
  } else if (line_num == 2) {
    clear_line_announce_.push_back("Double!");
  } else if (line_num == 1) {
    clear_line_announce_.push_back("Single!");
  }

  if (is_btb) {
    clear_line_announce_.push_back("Back To Back!");
  }

  if (combo >= 2) {
    clear_line_announce_.push_back(nostd::format("{} Combo!", combo));
  }

  clear_line_start_time_ = counter_;
}

void BattleAnnounce::Update() { ++counter_; }

void BattleAnnounce::Draw(const float x, const float y) const {
  // if (tetris_field_ptr_->IsGameOver()) {
  //   // ゲームオーバー時は表示しない.
  //   return;
  // }

  // クリアラインアナウンス表示.
  if (!clear_line_announce_.empty() &&
      counter_ < clear_line_start_time_ + animation_duration_) {
    const float alpha =
        (counter_ - clear_line_start_time_) % 40 < 20 ? 0.0f : 1.0f;
    for (size_t i = 0; i < clear_line_announce_.size(); ++i) {
      font_view_.DrawAlpha(x,
                           y - 350.f * game_const::kResolutionEx +
                               i * 40.f * game_const::kResolutionEx,
                           RenderAnchor::Center, clear_line_announce_[i],
                           game_const::kResolutionEx, alpha);
    }
  }
}

}  // namespace mytetris
