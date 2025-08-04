
//! @file tetromino.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <vector>

#include "tetromino_color.h"

namespace mytetris {

class Tetromino final {
 public:
  Tetromino(const std::vector<std::vector<bool>> shape, TetrominoColor color);

  inline std::vector<std::vector<bool>> GetShape() const { return shape_; }

  inline TetrominoColor GetColor() const { return color_; }

 private:
  const std::vector<std::vector<bool>> shape_;
  const TetrominoColor color_;
};

}  // namespace mytetris
