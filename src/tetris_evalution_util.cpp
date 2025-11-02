#include "tetris_evalution_util.h"

#include <algorithm>

namespace mytetris {

std::array<int, TetrisField::kWidth - 2> mytetris::GetHoleCountsPerColumn(
    const EvTetrisField& field) {
  std::array<int, TetrisField::kWidth - 2> hole_counts{};

  for (size_t x{1}; x < TetrisField::kWidth - 1; ++x) {
    bool block_found = false;
    int top_y = 0;
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (field[y][x]) {
        block_found = true;
        top_y = y;
      } else {
        if (block_found) {
          // ブロックの下にある空白＝穴.
          hole_counts[x - 1] += abs(top_y - y);
        }
      }
    }
  }

  return hole_counts;
}

int GetHeightSum(const EvTetrisField& field) {
  int result{};

  // 各列の高さを合計.
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (field[y][x]) {
        result += (TetrisField::kHeight - y);
        break;
      }
    }
  }

  return result;
}

int GetHeightDifferenceSum(const EvTetrisField& field) {
  int result{};
  std::array<int, TetrisField::kWidth - 2> heights{};
  // 各列の高さを取得.
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (field[y][x]) {
        heights[x - 1] = TetrisField::kHeight - y;
        break;
      }
    }
  }
  // 隣接する列の高さの差を合計.
  for (int x = 0; x < TetrisField::kWidth - 1; ++x) {
    result += std::abs(heights[x] - heights[x + 1]);
  }
  return result;
}

int GetHeightDifferenceSquareSum(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field) {
  int result{};
  std::array<int, TetrisField::kWidth - 2> heights{};
  // 各列の高さを取得.
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (field[y][x]) {
        heights[x - 1] = TetrisField::kHeight - y;
        break;
      }
    }
  }
  // 隣接する列の高さの差の二乗を合計
  for (int x = 0; x < TetrisField::kWidth - 3; ++x) {
    int diff = heights[x] - heights[x + 1];
    result += diff * diff;
  }
  return result;
}

int GetHighestColumnHeight(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field) {
  int highest_height = 0;
  for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (field[y][x]) {
        int column_height = TetrisField::kHeight - y;
        highest_height = std::max(highest_height, column_height);
        break;
      }
    }
  }
  return highest_height;
}

int GetClearedLineCount(const std::array<std::array<bool, TetrisField::kWidth>,
                                         TetrisField::kHeight>& field) {
  int cleared_line_count = 0;
  for (int y = 0; y < TetrisField::kHeight - 1; ++y) {
    bool is_cleared = true;
    for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
      if (!field[y][x]) {
        is_cleared = false;
        break;
      }
    }
    if (is_cleared) {
      cleared_line_count++;
    }
  }
  return cleared_line_count;
}

}  // namespace mytetris
