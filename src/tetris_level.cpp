#include "tetris_level.h"

//! @file tetris_level.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

namespace mytetris {

TetrisLevel::TetrisLevel() : max_level_(20) {}

int TetrisLevel::GetLevel() const {
  if (game_mode_ == TetrisGameMode::kPractice) {
    // Practice ƒ‚[ƒh‚Å‚ÍƒŒƒxƒ‹‚Íí‚É 0 ‚Æ‚·‚é.
    return 0;
  }

  int level = total_clear_lines_ / 10 + 1;
  return level > max_level_ ? max_level_ : level;
}

}  // namespace mytetris
