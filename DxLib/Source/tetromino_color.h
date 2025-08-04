
//! @file tetromino_color.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

enum class TetrominoColor : int {
  kNone = 0,
  kI = 1,
  kJ = 2,
  kL = 3,
  kO = 4,
  kS = 5,
  kZ = 6,
  kT = 7,
  kWall = 8,
  kJammer = 9,
};

}  // namespace mytetris
