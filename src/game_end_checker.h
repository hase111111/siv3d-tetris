
//! @file game_end_checker.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "tetris_game_mode.h"
#include "tetris_level.h"
#include "tetris_timer.h"

namespace mytetris {

class GameEndChecker {
 public:
  GameEndChecker(const std::shared_ptr<TetrisLevel>& tetris_level_ptr,
                 const std::shared_ptr<TetrisTimer>& tetris_timer_ptr);
  ~GameEndChecker() = default;

  bool IsGameEnd() const;

  inline void SetGameMode(const TetrisGameMode game_mode) {
    game_mode_ = game_mode;
    SetLimits();
  }

 private:
  void SetLimits();

  const std::shared_ptr<TetrisLevel> tetris_level_ptr_;
  const std::shared_ptr<TetrisTimer> tetris_timer_ptr_;

  int time_limit_seconds_{0};
  int clear_lines_limit_{0};
  TetrisGameMode game_mode_{TetrisGameMode::kEndless};
};

}  // namespace mytetris
