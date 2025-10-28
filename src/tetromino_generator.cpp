//! @file tetromino_generator.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetromino_generator.h"

#include <vector>

#include "my_assert.h"
#include "tetromino_color.h"

namespace mytetris {

Tetromino TetrominoGenerator::Generate(const TetrominoType type) const {
  switch (type) {
    case TetrominoType::kI: {
      return Tetromino{{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
                       TetrominoColor::kI,
                       RotationType::kI};
    }
    case TetrominoType::kL: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kL,
                       RotationType::kNormal};
    }
    case TetrominoType::kJ: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kJ,
                       RotationType::kNormal};
    }
    case TetrominoType::kO: {
      return Tetromino{{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
                       TetrominoColor::kO,
                       RotationType::kNone};
    }
    case TetrominoType::kS: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kS,
                       RotationType::kNormal};
    }
    case TetrominoType::kZ: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 1, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kZ,
                       RotationType::kNormal};
    }
    case TetrominoType::kT: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kT,
                       RotationType::kNormal};
    }
    case TetrominoType::kYama: {
      return Tetromino{{{0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1}},
                       TetrominoColor::kOther1,
                       RotationType::kNormal};
    }
    case TetrominoType::kDa: {
      return Tetromino{{{1, 1, 1, 1, 1},
                        {1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1},
                        {1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1}},
                       TetrominoColor::kOther2,
                       RotationType::kNormal};
    }
    case TetrominoType::kMiniI: {
      return Tetromino{{{0, 0, 0}, {1, 1, 1}, {0, 0, 0}},
                       TetrominoColor::kOther3,
                       RotationType::kNormal};
    }
    case TetrominoType::kSilentT: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther8,
                       RotationType::kNormal};
    }
    case TetrominoType::kOneByTwo: {
      return Tetromino{
          {{1, 1}}, TetrominoColor::kOther4, RotationType::kNormal};
    }
    case TetrominoType::kOneByOne: {
      return Tetromino{{{1}}, TetrominoColor::kOther5, RotationType::kNone};
    }
    case TetrominoType::kPentrisI: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kI,
                       RotationType::kI};
    }
    case TetrominoType::kPentrisL: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kL,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisLDash: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther3,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisJ: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kJ,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisJDash: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther4,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisOL: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kO,
                       RotationType::kNone};
    }
    case TetrominoType::kPentrisOR: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther6,
                       RotationType::kNone};
    }
    case TetrominoType::kPentrisS: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kS,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisSDash: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 1},
                        {0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther2,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisZ: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kZ,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisZDash: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {1, 1, 1, 0, 0},
                        {0, 0, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther1,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisTL: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther7,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisTR: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther7,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisTCenter: {
      return Tetromino{{{0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kT,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisOu: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 1, 0, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther2,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisCorner: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kOther7,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisCross: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 1, 1, 1, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kJammer,
                       RotationType::kNormal};
    }
    case TetrominoType::kPentrisStep: {
      return Tetromino{{{0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 0, 1, 1, 0},
                        {0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0}},
                       TetrominoColor::kJammer,
                       RotationType::kNormal};
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return Tetromino{{{0}}, TetrominoColor::kNone, RotationType::kNone};
    }
  }
}

}  // namespace mytetris
