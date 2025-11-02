#include "tetris_evalution_util.h"

#include <algorithm>

namespace mytetris {

std::optional<
    std::array<std::array<bool, TetrisField::kWidth>, TetrisField::kHeight>>
PlaceTetromino(const std::array<std::array<bool, TetrisField::kWidth>,
                                TetrisField::kHeight>& field,
               const std::vector<std::vector<bool>>& shape, int x) {
  auto result = field;

  const int shapeHeight = static_cast<int>(shape.size());
  const int shapeWidth = static_cast<int>(shape[0].size());

  // 壁にめり込んでいるならアウト
  if (x < 0 || x + shapeWidth > TetrisField::kWidth) {
    return std::nullopt;
  }

  // 下に向かって落下
  int dropY = 0;
  bool placed = false;

  for (int y = 0; y <= TetrisField::kHeight - shapeHeight; ++y) {
    bool collision = false;

    // shape と field の衝突判定
    for (int dy = 0; dy < shapeHeight && !collision; ++dy) {
      for (int dx = 0; dx < shapeWidth; ++dx) {
        if (!shape[dy][dx]) continue;

        int fx = x + dx;
        int fy = y + dy;

        // フィールド外 or 衝突
        if (fy >= TetrisField::kHeight || fx < 0 || fx >= TetrisField::kWidth ||
            field[fy][fx]) {
          collision = true;
          break;
        }
      }
    }

    if (collision) {
      // 一つ上で止める
      dropY = y - 1;
      placed = true;
      break;
    }
  }

  // 最後まで落ちても衝突しなかったら一番下で止まる
  if (!placed) {
    dropY = TetrisField::kHeight - shapeHeight;
  }

  // もし最初から衝突してたらnullopt
  if (dropY < 0) return std::nullopt;

  // 設置処理（上書き）
  for (int dy = 0; dy < shapeHeight; ++dy) {
    for (int dx = 0; dx < shapeWidth; ++dx) {
      if (!shape[dy][dx]) continue;

      int fx = x + dx;
      int fy = dropY + dy;

      // 壁・床はもともと true なので上書きされない
      if (result[fy][fx]) return std::nullopt;  // めり込み
      result[fy][fx] = true;
    }
  }

  return result;
}

std::array<int, TetrisField::kWidth - 2> mytetris::GetHoleCountsPerColumn(
    const EvTetrisField& field) {
  std::array<int, TetrisField::kWidth - 2> hole_counts{};

  for (size_t x{1}; x < TetrisField::kWidth - 1; ++x) {
    bool block_found = false;
    int top_y = 0;
    for (int y = 0; y < TetrisField::kHeight; ++y) {
      if (!block_found && field[y][x]) {
        block_found = true;
        top_y = y;
      } else if (block_found && !field[y][x]) {
        // ブロックの下にある空白＝穴.
        // hole_counts[x - 1] += abs(top_y - y);
        ++hole_counts[x - 1];
      }
    }
  }

  for (auto&& count : hole_counts) {
    count = count * (count + 1) / 2;  // 三角数に変換.
  }

  return hole_counts;
}

std::tuple<int, EvTetrisField> DeleteFullLines(const EvTetrisField& field) {
  // 横一列が埋まっている行を削除し, 上から詰める.
  // ただし，床と壁は削除しない.
  EvTetrisField result = field;
  int cleared_line_count{0};

  // ClearLines の実装を参考に.
  for (int y = TetrisField::kHeight - 2; y >= 0;
       --y) {  // 最下段は壁なので除外.
    bool is_full_line = true;
    for (int x = 1; x < TetrisField::kWidth - 1; ++x) {  // 両端は壁なので除外.
      if (!result[y][x]) {
        is_full_line = false;
        break;
      }
    }
    if (is_full_line) {
      ++cleared_line_count;

      // 行を削除して上に詰める.
      for (int clear_y = y; clear_y > 0; --clear_y) {
        for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
          result[clear_y][x] = result[static_cast<size_t>(clear_y) - 1][x];
        }
      }
      // 上端の行は壁で埋める.
      for (int x = 1; x < TetrisField::kWidth - 1; ++x) {
        result[0][x] = false;
      }
      // 行を削除したので再度チェックするために y を進める.
      ++y;  // 行を削除したので y を進める.
    }
  }

  return {cleared_line_count, result};
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
  for (size_t x = 0; x < TetrisField::kWidth - 3; ++x) {
    result += std::abs(heights[x] - heights[x + 1]);
  }
  return result;
}

int GetHeightDifferenceSquareSum(const EvTetrisField& field) {
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
  for (size_t x = 0; x < TetrisField::kWidth - 3; ++x) {
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
