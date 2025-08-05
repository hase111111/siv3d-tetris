
//! @file tetromino.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetromino.h"

#include "dxlib_assert.h"

namespace mytetris {

static bool IsRectangleShape(const std::vector<std::vector<bool>>& shape) {
  if (shape.empty()) {
    return false;
  }

  const int width = static_cast<int>(shape[0].size());
  for (const auto& row : shape) {
    if (static_cast<int>(row.size()) != width) {
      return false;
    }
  }
  return true;
}

Tetromino::Tetromino(const std::vector<std::vector<bool>> shape,
                     TetrominoColor color)
    : shape_(shape), color_(color) {
  ASSERT(IsRectangleShape(shape), "The shape must be a rectangle.");
}

std::vector<std::vector<bool>> Tetromino::GetShape() const {
  const int rotation_index = rotation_index_ % 4;
  std::vector<std::vector<bool>> rotated_shape = shape_;

  for (int i = 0; i < rotation_index; ++i) {
    rotated_shape = GetLeftRotatedShape(rotated_shape);
  }

  return rotated_shape;
}

std::vector<std::vector<bool>> Tetromino::GetLeftRotatedShape(
    const std::vector<std::vector<bool>>& shape) const {
  std::vector<std::vector<bool>> rotated_shape;
  const int height = static_cast<int>(shape.size());
  const int width = static_cast<int>(shape[0].size());
  rotated_shape.resize(width, std::vector<bool>(height, false));

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      rotated_shape[static_cast<size_t>(width - j - 1)][i] = shape[i][j];
    }
  }

  return rotated_shape;
}

}  // namespace mytetris
