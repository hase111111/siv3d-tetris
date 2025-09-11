
//! @file tetromino_generator.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "tetromino.h"
#include "tetromino_type.h"

namespace mytetris {

class TetrominoGenerator final {
 public:
  TetrominoGenerator() = default;

  Tetromino Generate(const TetrominoType) const;

 private:
};

}  // namespace mytetris
