
//! @file tetris_field.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_feild.h"

namespace mytetris {

TetrisField::TetrisField() : field_(InitializeField()) {}

std::tuple<int, int> TetrisField::GetHardDropPosition(
    const Tetromino& tetromino, int tetromino_x, int tetromino_y) const {
  int y = tetromino_y;
  while (IsValidPosition(tetromino, tetromino_x, y + 1)) {
    ++y;
  }
  return {tetromino_x, y};
}

bool TetrisField::IsValidPosition(const Tetromino& tetromino,
                                  const int tetromino_x,
                                  const int tetromino_y) const {
  const auto shape = tetromino.GetShape();
  const int height = static_cast<int>(shape.size());
  const int width = static_cast<int>(shape[0].size());
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (shape[y][x]) {
        const int field_x = tetromino_x + x;
        const int field_y = tetromino_y + y;

        if (field_x < 0 || field_x >= kWidth || field_y >= kHeight) {
          return false;
        }

        if (field_y < 0) {
          continue;
        }

        if (field_[field_y][field_x] != TetrominoColor::kNone) {
          return false;
        }
      }
    }
  }
  return true;
}

void TetrisField::SetTetromino(const Tetromino& tetromino,
                               const int tetromino_x, const int tetromino_y) {
  // 仮に tetromino がフィールド外にある場合でも,
  // フィールド内にある分だけをセットする.
  // Wallは上書きしない.
  const auto shape = tetromino.GetShape();
  const int height = static_cast<int>(shape.size());
  const int width = static_cast<int>(shape[0].size());

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (shape[y][x]) {
        const int field_x = tetromino_x + x;
        const int field_y = tetromino_y + y;

        // フィールド外は無視.
        if (field_x < 0 || field_x >= kWidth || field_y < 0 ||
            field_y >= kHeight) {
          continue;
        }

        // Wallは上書きしない.
        if (field_[field_y][field_x] == TetrominoColor::kWall) {
          continue;
        }

        field_[field_y][field_x] = tetromino.GetColor();
      }
    }
  }
}

TetrisField::FieldType TetrisField::InitializeField() const {
  FieldType field{};
  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x) {
      field[y][x] = TetrominoColor::kNone;
    }
  }

  // ∪状になるように kWall を配置.
  for (int x = 0; x < kWidth; ++x) {
    field[static_cast<size_t>(kHeight) - 1][x] = TetrominoColor::kWall;
  }
  for (int y = 0; y < kHeight; ++y) {
    field[y][0] = TetrominoColor::kWall;
    field[y][static_cast<size_t>(kWidth) - 1] = TetrominoColor::kWall;
  }
  return field;
}

}  // namespace mytetris
