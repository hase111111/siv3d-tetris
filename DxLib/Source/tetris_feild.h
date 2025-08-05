
//! @file tetris_field.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <tuple>

#include "tetromino.h"
#include "tetromino_color.h"

namespace mytetris {

class TetrisField final {
  using FieldType = std::array<std::array<TetrominoColor, 12>, 24>;

 public:
  TetrisField();

  int GetWidth() const { return kWidth; }
  int GetHeight() const { return kHeight; }

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

  std::tuple<int, int> GetHardDropPosition(const Tetromino& tetromino,
                                           int tetromino_x,
                                           int tetromino_y) const;

  bool IsValidPosition(const Tetromino& tetromino, int tetromino_x,
                       int tetromino_y) const;

 private:
  static constexpr int kWidth = 12;
  static constexpr int kHeight = 24;

  FieldType InitializeField() const;

  FieldType field_{};
};

}  // namespace mytetris
