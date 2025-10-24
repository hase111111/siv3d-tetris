
//! @file tetris_field_effect.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <tuple>
#include <vector>

#include "tetris_feild.h"

namespace mytetris {

class TetrisFieldEffect final {
  template <typename T>
  using Field =
      std::array<std::array<T, TetrisField::kHeight>, TetrisField::kWidth>;

 public:
  TetrisFieldEffect() = default;

 private:
  Field<std::pair<int, int>> field_effect_{};
};

}  // namespace mytetris
