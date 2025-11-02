#pragma once

#include <array>
#include <sstream>
#include <string>

#include "tetris_feild.h"

namespace mytetris {

using EvTetrisField =
    std::array<std::array<bool, TetrisField::kWidth>, TetrisField::kHeight>;

std::array<int, TetrisField::kWidth - 2> GetHoleCountsPerColumn(
    const EvTetrisField& field);

//! @brief 高さの平均値を計算する.
int GetHeightSum(const EvTetrisField& field);

//! @brief 高さの差の平均値を計算する.
int GetHeightDifferenceSum(const EvTetrisField& field);

//! @brief 高さの差の平均値を計算する.
int GetHeightDifferenceSquareSum(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field);

int GetHighestColumnHeight(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field);

int GetClearedLineCount(const std::array<std::array<bool, TetrisField::kWidth>,
                                         TetrisField::kHeight>& field);

inline std::string ToString(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field,
    bool useWide) {
  std::ostringstream oss;

  for (int y = 0; y < TetrisField::kHeight; ++y) {
    for (int x = 0; x < TetrisField::kWidth; ++x) {
      if (field[y][x]) {
        oss << (useWide ? "■" : "#");
      } else {
        oss << (useWide ? "　" : "_");
      }
    }
    oss << '\n';
  }

  return oss.str();
}

}  // namespace mytetris
