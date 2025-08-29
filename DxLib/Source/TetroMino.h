
//! @file tetromino.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <vector>

#include "tetromino_color.h"

namespace mytetris {

enum class RotationType : int {
  kNone,
  kNormal,
  kI,
};

class Tetromino final {
 public:
  Tetromino(const std::vector<std::vector<bool>> shape, TetrominoColor color,
            RotationType rotation_type);

  Tetromino(const std::vector<std::vector<bool>> shape, TetrominoColor color,
            RotationType rotation_type, int rotation_index);

  std::vector<std::vector<bool>> GetShape() const;

  inline TetrominoColor GetColor() const { return color_; }

  inline RotationType GetRotationType() const { return rotation_type_; }

  inline int GetRotationIndex() const { return rotation_index_ % 4; }

  inline void LeftRotate() { rotation_index_ += 3; }
  inline void RightRotate() { rotation_index_ += 1; }

  Tetromino GetRotatedLeft() const;
  Tetromino GetRotatedRight() const;

  void Reshape(const Tetromino& other);

 private:
  std::vector<std::vector<bool>> GetRightRotatedShape(
      const std::vector<std::vector<bool>>& shape) const;

  std::vector<std::vector<bool>> shape_;
  TetrominoColor color_;
  RotationType rotation_type_;
  int rotation_index_{0};
};

}  // namespace mytetris
