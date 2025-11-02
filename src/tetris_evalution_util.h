#pragma once

#include <array>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "tetris_feild.h"

namespace mytetris {

using EvTetrisField =
    std::array<std::array<bool, TetrisField::kWidth>, TetrisField::kHeight>;

using EvShape = std::vector<std::vector<bool>>;

std::array<int, TetrisField::kWidth - 2> GetHoleCountsPerColumn(
    const EvTetrisField& field);

std::optional<EvTetrisField> PlaceTetromino(const EvTetrisField& field,
                                            const EvShape& shape, int x);

std::tuple<int, EvTetrisField> DeleteFullLines(const EvTetrisField& field);

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
        oss << (useWide ? "a" : "#");
      } else {
        oss << (useWide ? "b" : "_");
      }
    }
    oss << '\n';
  }

  return oss.str();
}

}  // namespace mytetris
