
//! @file tetris_level.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "tetris_game_mode.h"

namespace mytetris {

class TetrisLevel final {
 public:
  TetrisLevel();
  ~TetrisLevel() = default;

  inline void AddClearLines(const int clear_lines) {
    total_clear_lines_ += clear_lines;
  }

  int GetLevel() const;

  inline void SetGameMode(const TetrisGameMode game_mode) {
    game_mode_ = game_mode;
  }

  inline int GetTotalClearLines() const { return total_clear_lines_; }

 private:
  const int max_level_{20};

  TetrisGameMode game_mode_{};
  int total_clear_lines_{0};
};

}  // namespace mytetris
