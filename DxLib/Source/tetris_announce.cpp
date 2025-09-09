
//! @file tetris_announce.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_announce.h"

#include <format>

#include "my_assert.h"
#include "render_util.h"

namespace mytetris {

TetrisAnnounce::TetrisAnnounce(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr,
    const std::shared_ptr<const GameEndChecker>& game_end_checker_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr)
    : tetris_level_ptr_(tetris_level_ptr),
      tetris_timer_ptr_(tetris_timer_ptr),
      game_end_checker_ptr_(game_end_checker_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      font_view_(resource_container_ptr->GetFont("default")),
      font_view_small_(resource_container_ptr->GetFont("small")) {}

void TetrisAnnounce::Update() {
  ++counter_;

  if (game_end_checker_ptr_->IsGameEnd()) {
    switch (game_mode_) {
      case TetrisGameMode::kEndless:
      case TetrisGameMode::kPractice: {
        break;
      }
      case TetrisGameMode::kSprint:
      case TetrisGameMode::kMarathon: {
        announce_text_ =
            std::format("CLEAR!\nTime {}", tetris_timer_ptr_->GetTimeString());
        announce_text_small_ = "Press R to Restart";
        break;
      }
      case TetrisGameMode::kUltra: {
        announce_text_ = std::format("Time Up!\nScore {}", 0);
        announce_text_small_ = "Press R to Restart";
        break;
      }
      case TetrisGameMode::kYamada:
        break;
      case TetrisGameMode::kPentris:
        break;
      case TetrisGameMode::kTrick:
        break;
      default:
        break;
    }
  } else {
    switch (game_mode_) {
      case TetrisGameMode::kEndless: {
        // なにもアナウンスはしない.
        break;
      }
      case TetrisGameMode::kSprint: {
        for (int i = 1; i <= 3; ++i) {
          if (tetris_level_ptr_->GetTotalClearLines() >= i * 10 &&
              total_clear_lines_ < i * 10) {
            announce_text_ = std::format("{} / 40", i * 10);
            announce_text_small_ = std::format(
                "{} lines left", 40 - tetris_level_ptr_->GetTotalClearLines());
            start_time_ = counter_;
          }
        }
        break;
      }
      case TetrisGameMode::kUltra: {
        for (int i = 1; i <= 2; ++i) {
          if (tetris_timer_ptr_->GetTime() >= 3600 * i &&
              timer_count_ < 3600 * i) {
            announce_text_ = std::format("{} minute passed!", i);
            announce_text_small_ = std::format("{} minute left", 3 - i);
            start_time_ = counter_;
          }
        }
        break;
      }
      case TetrisGameMode::kMarathon: {
        for (int i = 1; i <= 9; ++i) {
          if (tetris_level_ptr_->GetTotalClearLines() >= i * 20 &&
              total_clear_lines_ < i * 20) {
            announce_text_ = std::format("{} / 200", i * 20);
            announce_text_small_ = std::format(
                "{} lines left", 200 - tetris_level_ptr_->GetTotalClearLines());
            start_time_ = counter_;
          }
        }
        break;
      }
      case TetrisGameMode::kYamada:
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
    timer_count_ = tetris_timer_ptr_->GetTime();
  }
}

void TetrisAnnounce::Draw(const int x, const int y) const {
  if (tetris_field_ptr_->IsGameOver()) {
    return;
  }

  if (!game_end_checker_ptr_->IsGameEnd()) {
    if (counter_ < start_time_ + animation_duration_) {
      const float alpha = (counter_ - start_time_) % 40 < 20 ? 0.0f : 1.0f;

      font_view_.DrawAlpha(static_cast<float>(x), static_cast<float>(y),
                           RenderAnchor::Center, announce_text_, alpha);

      font_view_small_.DrawAlpha(
          static_cast<float>(x), static_cast<float>(y) + 50.f,
          RenderAnchor::Center, announce_text_small_, alpha);
    }
  } else {
    const float block_size = 40.f;
    const float x_size = block_size * (tetris_field_ptr_->GetWidth() - 2);
    const float y_size = block_size * (tetris_field_ptr_->GetHeight() - 2);
    DrawRectAlpha(x - x_size / 2.f, y - y_size / 2.f, x + x_size / 2.f,
                  y + y_size / 2.f, 0x00000000, true, 0.5f);

    font_view_.DrawAlpha(static_cast<float>(x), static_cast<float>(y) - 50.f,
                         RenderAnchor::Center, announce_text_, 1.0f);

    font_view_small_.DrawAlpha(
        static_cast<float>(x), static_cast<float>(y) + 50.f,
        RenderAnchor::Center, announce_text_small_, 1.0f);
  }
}

}  // namespace mytetris
