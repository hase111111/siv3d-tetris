
//! @file tetris_level.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

namespace mytetris {

class TetrisLevel final {
 public:
  TetrisLevel();
  ~TetrisLevel() = default;

  inline void AddClearLines(const int clear_lines) {
    total_clear_lines_ += clear_lines;
  }

  int GetLevel() const;

  inline int GetTotalClearLines() const { return total_clear_lines_; }

 private:
  int total_clear_lines_{0};
  const int max_level_{20};
};

}  // namespace mytetris
