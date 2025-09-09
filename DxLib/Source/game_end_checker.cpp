
//! @file game_end_checker.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "game_end_checker.h"

namespace mytetris {

GameEndChecker::GameEndChecker(
    const std::shared_ptr<TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<TetrisTimer>& tetris_timer_ptr)
    : tetris_level_ptr_(tetris_level_ptr),
      tetris_timer_ptr_(tetris_timer_ptr) {}

bool GameEndChecker::IsGameEnd() const {
  switch (game_mode_) {
    case TetrisGameMode::kEndless:
    case TetrisGameMode::kPractice: {
      return false;
    }
    case TetrisGameMode::kSprint:
    case TetrisGameMode::kMarathon: {
      if (tetris_level_ptr_->GetTotalClearLines() >= clear_lines_limit_) {
        return true;
      }
      return false;
    }
    case TetrisGameMode::kUltra: {
      if (tetris_timer_ptr_->GetTime() >= time_limit_seconds_) {
        return true;
      }
      return false;
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

  return false;
}

void GameEndChecker::SetLimits() {
  switch (game_mode_) {
    case TetrisGameMode::kEndless:
    case TetrisGameMode::kPractice: {
      // Ç»Ç…Ç‡ê›íËÇµÇ»Ç¢.
      break;
    }
    case TetrisGameMode::kSprint: {
      clear_lines_limit_ = 40;
      break;
    }
    case TetrisGameMode::kUltra: {
      time_limit_seconds_ = 180 * 60 + 1;
      break;
    }
    case TetrisGameMode::kMarathon: {
      clear_lines_limit_ = 200;
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
}

}  // namespace mytetris
