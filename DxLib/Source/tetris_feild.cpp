
//! @file tetris_field.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_feild.h"

namespace mytetris {

TetrisField::TetrisField() : field_(InitializeField()) {}

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
  // ���� tetromino ���t�B�[���h�O�ɂ���ꍇ�ł�,
  // �t�B�[���h���ɂ��镪�������Z�b�g����.
  // Wall�͏㏑�����Ȃ�.
  const auto shape = tetromino.GetShape();
  const int height = static_cast<int>(shape.size());
  const int width = static_cast<int>(shape[0].size());

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (shape[y][x]) {
        const int field_x = tetromino_x + x;
        const int field_y = tetromino_y + y;

        // �t�B�[���h�O�͖���.
        if (field_x < 0 || field_x >= kWidth || field_y < 0 ||
            field_y >= kHeight) {
          continue;
        }

        // Wall�͏㏑�����Ȃ�.
        if (field_[field_y][field_x] == TetrominoColor::kWall) {
          continue;
        }

        field_[field_y][field_x] = tetromino.GetColor();
      }
    }
  }
}

void TetrisField::ClearLines() {
  // �񂪂�����Ă��邩�`�F�b�N���C������Ă�����폜���ď�ɋl�߂�.
  for (int y = kHeight - 2; y >= 0; --y) {  // �ŉ��i�͕ǂȂ̂ŏ��O
    bool is_full_line = true;
    for (int x = 1; x < kWidth - 1; ++x) {  // ���[�͕ǂȂ̂ŏ��O
      if (field_[y][x] == TetrominoColor::kNone) {
        is_full_line = false;
        break;
      }
    }
    if (is_full_line) {
      // �s���폜���ď�ɋl�߂�.
      for (int clear_y = y; clear_y > 0; --clear_y) {
        for (int x = 1; x < kWidth - 1; ++x) {
          field_[clear_y][x] = field_[static_cast<size_t>(clear_y) - 1][x];
        }
      }
      // ��[�̍s�͕ǂŖ��߂�.
      for (int x = 1; x < kWidth - 1; ++x) {
        field_[0][x] = TetrominoColor::kNone;
      }

      // �s���폜�����̂ōēx�`�F�b�N���邽�߂� y ��i�߂�.
      ++y;  // �s���폜�����̂� y ��i�߂�.
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

  // ����ɂȂ�悤�� kWall ��z�u.
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
