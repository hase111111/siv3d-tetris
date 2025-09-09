
//! @file tetris_announce.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_announce.h"

#include <format>

#include "my_assert.h"

namespace mytetris {

TetrisAnnounce::TetrisAnnounce(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr)
    : tetris_level_ptr_(tetris_level_ptr),
      tetris_timer_ptr_(tetris_timer_ptr),
      font_view_(resource_container_ptr->GetFont("default")) {
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr);
}

void TetrisAnnounce::Update() {
  ++counter_;

  switch (game_mode_) {
    case TetrisGameMode::kEndless: {
      // なにもアナウンスはしない.
      break;
    }
    case TetrisGameMode::kSprint: {
      for (int i = 1; i <= 3; ++i) {
        if (tetris_level_ptr_->GetTotalClearLines() >= i * 10 &&
            total_clear_lines_ < i * 10) {
          announce_text_ =
              std::format("{} / 40", tetris_level_ptr_->GetTotalClearLines());
          start_time_ = counter_;
        }
      }
      break;
    }
    case TetrisGameMode::kUltra: {
      break;
    }
    case TetrisGameMode::kMarathon: {
      for (int i = 1; i <= 19; ++i) {
        if (tetris_level_ptr_->GetTotalClearLines() >= i * 10 &&
            total_clear_lines_ < i * 10) {
          announce_text_ =
              std::format("{} / 40", tetris_level_ptr_->GetTotalClearLines());
          start_time_ = counter_;
        }
      }
      break;
    }
    case TetrisGameMode::kUeda:
      break;
    case TetrisGameMode::kPentris:
      break;
    case TetrisGameMode::kTrick:
      break;
    case TetrisGameMode::kPractice:
      break;
    default:
      break;
  }

  total_clear_lines_ = tetris_level_ptr_->GetTotalClearLines();
}

void TetrisAnnounce::Draw(const int x, const int y) const {
  if (counter_ < start_time_ + animation_duration_) {
    font_view_.DrawAlpha(x, y, RenderAnchor::Center, announce_text_, 1.f);
  }
}

}  // namespace mytetris
