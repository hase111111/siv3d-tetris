
//! @file next_tetromino.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "next_tetromino.h"

#include <algorithm>
#include <random>

#include "dxlib_assert.h"

namespace mytetris {

NextTetromino::NextTetromino() : next_{MakeNextTetromino()} {}

TetrominoType NextTetromino::GetNext() const {
  ASSERT(!next_.empty(), "No next tetromino available.");
  return next_.back();
}

std::vector<TetrominoType> NextTetromino::GetNextList() const {
  // ��납��7�̃e�g���~�m��Ԃ�, ����Ȃ���ΐ擪���疄�߂�.
  if (next_.size() >= 7) {
    return std::vector<TetrominoType>(next_.end() - 7, next_.end());
  } else {
    return next_;
  }
}

void NextTetromino::Next() {
  next_.pop_back();
  if (next_.size() < 7) {
    // 7�����Ȃ�V�����e�g���~�m��ǉ�����
    std::vector<TetrominoType> new_tetrominos = MakeNextTetromino();
    next_.insert(next_.begin(), new_tetrominos.begin(), new_tetrominos.end());
  }
}

std::vector<TetrominoType> NextTetromino::MakeNextTetromino() {
  std::vector<TetrominoType> tetrominos = tetrominos_;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(tetrominos.begin(), tetrominos.end(), engine);
  return tetrominos;
}

}  // namespace mytetris