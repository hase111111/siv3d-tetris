#include "tetris_level.h"

//! @file tetris_level.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

namespace mytetris {

TetrisLevel::TetrisLevel() : max_level_(20) {}

int TetrisLevel::GetLevel() const {
  int level = total_clear_lines_ / 10 + 1;
  return level > max_level_ ? max_level_ : level;
}

}  // namespace mytetris
