
//! @file next_tetromino.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <vector>

#include "tetromino_type.h"

namespace mytetris {

class NextTetromino final {
 public:
  NextTetromino();
  ~NextTetromino() = default;

  TetrominoType GetNext() const;

  std::vector<TetrominoType> GetNextList() const;

  void Next();

 private:
  std::vector<TetrominoType> MakeNextTetromino();

  const std::vector<TetrominoType> tetrominos_{
      TetrominoType::kI, TetrominoType::kJ, TetrominoType::kL,
      TetrominoType::kO, TetrominoType::kS, TetrominoType::kT,
      TetrominoType::kZ};

  std::vector<TetrominoType> next_;
};

}  // namespace mytetris