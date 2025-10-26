
//! @file tetris_field.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_feild.h"

namespace mytetris {

TetrisField::TetrisField() : field_(InitializeField()) {}

bool TetrisField::IsGameOver() const {
  const int y_ = 5;
  // 最上段にブロックがあるかどうかで判定.
  for (int y = 0; y < y_ + 1; ++y) {
    for (int x = 1; x < kWidth - 1; ++x) {
      if (field_[y][x] != TetrominoColor::kNone) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisField::IsPinch() const {
  const int y_ = 9;
  // 最上段にブロックがあるかどうかで判定.
  for (int y = 0; y < y_ + 1; ++y) {
    for (int x = 1; x < kWidth - 1; ++x) {
      if (field_[y][x] != TetrominoColor::kNone) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisField::IsEmpty() const {
  // 壁を除いて全て空かどうかで判定.
  for (int y = 0; y < kHeight - 1; ++y) {   // 最下段は壁なので除外
    for (int x = 1; x < kWidth - 1; ++x) {  // 両端は壁なので除外
      if (field_[y][x] != TetrominoColor::kNone) {
        return false;
      }
    }
  }
  return true;
}

bool TetrisField::IsOccupiedCorners(int tetromino_x, int tetromino_y,
                                    bool allow_wall) const {
  int occupied_corners = 0;
  const std::array<std::tuple<int, int>, 4> corners = {
      std::make_tuple(tetromino_x - 1, tetromino_y - 1),
      std::make_tuple(tetromino_x + 1, tetromino_y - 1),
      std::make_tuple(tetromino_x - 1, tetromino_y + 1),
      std::make_tuple(tetromino_x + 1, tetromino_y + 1),
  };
  for (const auto& [corner_x, corner_y] : corners) {
    if (corner_x < 0 || corner_x >= kWidth || corner_y < 0 ||
        corner_y >= kHeight) {
      // フィールド外は埋まっているとみなす.
      ++occupied_corners;
    } else {
      const TetrominoColor color = field_[corner_y][corner_x];
      if (color != TetrominoColor::kNone &&
          (allow_wall || color != TetrominoColor::kWall)) {
        ++occupied_corners;
      }
    }
  }

  return occupied_corners >= 3;
}

std::tuple<int, int> TetrisField::GetHardDropPosition(
    const Tetromino& tetromino, const int tetromino_x,
    const int tetromino_y) const {
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

std::vector<std::tuple<int, std::vector<TetrominoColor>>>
TetrisField::ClearLines() {
  int cnt{kHeight - 2};
  std::vector<std::tuple<int, std::vector<TetrominoColor>>> cleared_lines;

  // 列がそろっているかチェックし，そろっていたら削除して上に詰める.
  for (int y = kHeight - 2; y >= 0; --y) {  // 最下段は壁なので除外
    bool is_full_line = true;
    for (int x = 1; x < kWidth - 1; ++x) {  // 両端は壁なので除外
      if (field_[y][x] == TetrominoColor::kNone) {
        is_full_line = false;
        break;
      }
    }
    if (is_full_line) {
      // 削除する行を記録.
      std::vector<TetrominoColor> line;
      for (int x = 1; x < kWidth - 1; ++x) {
        line.push_back(field_[y][x]);
      }
      cleared_lines.emplace_back(cnt, line);

      // 行を削除して上に詰める.
      for (int clear_y = y; clear_y > 0; --clear_y) {
        for (int x = 1; x < kWidth - 1; ++x) {
          field_[clear_y][x] = field_[static_cast<size_t>(clear_y) - 1][x];
        }
      }
      // 上端の行は壁で埋める.
      for (int x = 1; x < kWidth - 1; ++x) {
        field_[0][x] = TetrominoColor::kNone;
      }

      // 行を削除したので再度チェックするために y を進める.
      ++y;  // 行を削除したので y を進める.
    }

    --cnt;
  }

  return cleared_lines;
}

std::vector<std::tuple<int, std::vector<TetrominoColor>>>
TetrisField::GetAllLines() const {
  std::vector<std::tuple<int, std::vector<TetrominoColor>>> all_lines;
  for (int y = 0; y < kHeight - 1; ++y) {  // 最下段は壁なので除外
    std::vector<TetrominoColor> line;
    for (int x = 1; x < kWidth - 1; ++x) {  // 両端は壁なので除外
      line.push_back(field_[y][x]);
    }
    all_lines.emplace_back(y, line);
  }
  return all_lines;
}

void TetrisField::SetDeathColor() {
  // wall 以外をすべて Jammer にする.
  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x) {
      if (field_[y][x] != TetrominoColor::kWall &&
          field_[y][x] != TetrominoColor::kNone) {
        field_[y][x] = TetrominoColor::kJammer;
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
