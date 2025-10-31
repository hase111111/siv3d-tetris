//! @file tetris_field_effect_nothing.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_field_effect_nothing.h"

namespace mytetris {

float TetrisFieldEffectNothing::GetAlpha(int, int) const { return 1.0f; }

std::pair<int, int> TetrisFieldEffectNothing::GetDiff(int, int) const {
  return {0, 0};
}

void TetrisFieldEffectNothing::SetActive(bool) {
  // èÌÇ…ñ≥å¯Ç»ÇÃÇ≈âΩÇ‡ÇµÇ»Ç¢.
}

}  // namespace mytetris
