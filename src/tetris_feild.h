//! @file tetris_field.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <tuple>
#include <vector>

#include "tetromino.h"
#include "tetromino_color.h"

namespace mytetris {

class TetrisField final {
 public:
  static constexpr int kWidth = 12;
  static constexpr int kHeight = 27;
  using FieldType = std::array<std::array<TetrominoColor, kWidth>, kHeight>;

  TetrisField();

  //! @brief Tetris フィールドの幅を返す.
  //! @return フィールドの幅(ただし, 壁を含む).
  int GetWidth() const { return kWidth; }

  //! @brief Tetris フィールドの高さを返す.
  //! @return フィールドの高さ(ただし, 床を含む).
  int GetHeight() const { return kHeight; }

  bool IsGameOver() const;

  bool IsPinch() const;

  bool IsEmpty() const;

  //! @brief T-spin 判定用に指定したマスの4隅が埋まっているかを返す.
  bool IsOccupiedCorners(int tetromino_x, int tetromino_y,
                         bool allow_wall) const;

  class Iterator {
   public:
    using value_type = std::tuple<int, int, TetrominoColor>;
    using reference = value_type;
    using pointer = void;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    Iterator(const FieldType& field, int index = 0)
        : field_(field), index_(index) {}

    reference operator*() const {
      int y = index_ / kWidth;
      int x = index_ % kWidth;
      return {x, y, field_[y][x]};
    }

    Iterator& operator++() {
      ++index_;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return index_ != other.index_;
    }

   private:
    const FieldType& field_;
    int index_;
    static constexpr int kWidth = 12;
  };

  Iterator begin() const { return Iterator(field_, 0); }
  Iterator end() const { return Iterator(field_, kWidth * kHeight); }

  //! @brief テトリミノをハードドロップしたときの位置を返す.
  //! @param tetromino テトリミノの形状.
  //! @param tetromino_x テトリミノの x 座標.
  //! @param tetromino_y テトリミノの y 座標.
  //! @return ハードドロップ後のテトリミノの (x, y) 座標.
  std::tuple<int, int> GetHardDropPosition(const Tetromino& tetromino,
                                           int tetromino_x,
                                           int tetromino_y) const;

  //! @brief テトリミノを指定した位置に置けるかを返す.
  //! @param tetromino テトリミノの形状.
  //! @param tetromino_x テトリミノの x 座標.
  //! @param tetromino_y テトリミノの y 座標.
  //! @return 置ける場合は true, 置けない場合は false.
  bool IsValidPosition(const Tetromino& tetromino, int tetromino_x,
                       int tetromino_y) const;

  //! @brief テトリミノを指定した位置にセットする.
  //! @param tetromino テトリミノの形状.
  //! @param tetromino_x テトリミノの x 座標.
  //! @param tetromino_y テトリミノの y 座標.
  void SetTetromino(const Tetromino& tetromino, int tetromino_x,
                    int tetromino_y);

  std::vector<std::tuple<int, std::vector<TetrominoColor>>> ClearLines();

  std::vector<std::tuple<int, std::vector<TetrominoColor>>> GetAllLines() const;

  void SetDeathColor();

 private:
  FieldType InitializeField() const;

  FieldType field_{};
};

}  // namespace mytetris
