
//! @file tetris_field.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>

namespace mytetris {

enum class Tetromino : int {
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

class TetrisField final {
  using FieldType = std::array<std::array<Tetromino, 12>, 24>;

 public:
  TetrisField();

 private:
  static constexpr int kWidth = 12;
  static constexpr int kHeight = 24;

  FieldType InitializeField() const;

  FieldType field_{};
};

}  // namespace mytetris
