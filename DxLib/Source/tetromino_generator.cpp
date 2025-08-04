
//! @file tetromino_generator.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetromino_generator.h"

#include <vector>

#include "dxlib_assert.h"
#include "tetromino_color.h"

namespace mytetris {

Tetromino TetrominoGenerator::Generate(const TetrominoType type) {
  switch (type) {
    case TetrominoType::kI: {
      return Tetromino{{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
                       TetrominoColor::kI};
    }
    case TetrominoType::kL: {
      return Tetromino{{{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kL};
    }
    case TetrominoType::kJ: {
      return Tetromino{{{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}},
                       TetrominoColor::kJ};
    }
    case TetrominoType::kO: {
      return Tetromino{{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kO};
    }
    case TetrominoType::kS: {
      return Tetromino{{{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kS};
    }
    case TetrominoType::kZ: {
      return Tetromino{{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
                       TetrominoColor::kZ};
    }
    case TetrominoType::kT: {
      return Tetromino{{{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kT};
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      return Tetromino{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kNone};
    }
  }
}

}  // namespace mytetris
