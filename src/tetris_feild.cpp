
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
  // �ŏ�i�Ƀu���b�N�����邩�ǂ����Ŕ���.
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
  // �ŏ�i�Ƀu���b�N�����邩�ǂ����Ŕ���.
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
  // �ǂ������đS�ċ󂩂ǂ����Ŕ���.
  for (int y = 0; y < kHeight - 1; ++y) {   // �ŉ��i�͕ǂȂ̂ŏ��O
    for (int x = 1; x < kWidth - 1; ++x) {  // ���[�͕ǂȂ̂ŏ��O
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
      // �t�B�[���h�O�͖��܂��Ă���Ƃ݂Ȃ�.
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

std::vector<std::tuple<int, std::vector<TetrominoColor>>>
TetrisField::ClearLines() {
  int cnt{kHeight - 2};
  std::vector<std::tuple<int, std::vector<TetrominoColor>>> cleared_lines;

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
      // �폜����s���L�^.
      std::vector<TetrominoColor> line;
      for (int x = 1; x < kWidth - 1; ++x) {
        line.push_back(field_[y][x]);
      }
      cleared_lines.emplace_back(cnt, line);

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

    --cnt;
  }

  return cleared_lines;
}

std::vector<std::tuple<int, std::vector<TetrominoColor>>>
TetrisField::GetAllLines() const {
  std::vector<std::tuple<int, std::vector<TetrominoColor>>> all_lines;
  for (int y = 0; y < kHeight - 1; ++y) {  // �ŉ��i�͕ǂȂ̂ŏ��O
    std::vector<TetrominoColor> line;
    for (int x = 1; x < kWidth - 1; ++x) {  // ���[�͕ǂȂ̂ŏ��O
      line.push_back(field_[y][x]);
    }
    all_lines.emplace_back(y, line);
  }
  return all_lines;
}

void TetrisField::SetDeathColor() {
  // wall �ȊO�����ׂ� Jammer �ɂ���.
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
