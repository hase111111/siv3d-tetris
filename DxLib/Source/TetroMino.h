
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

  std::vector<std::vector<bool>> GetShape() const;

  inline TetrominoColor GetColor() const { return color_; }

  inline void LeftRotate() { rotation_index_ += 1; }
  inline void RightRotate() { rotation_index_ += 3; }

 private:
  std::vector<std::vector<bool>> GetLeftRotatedShape(
      const std::vector<std::vector<bool>>& shape) const;

  const std::vector<std::vector<bool>> shape_;
  const TetrominoColor color_;
  int rotation_index_{0};
};

}  // namespace mytetris
