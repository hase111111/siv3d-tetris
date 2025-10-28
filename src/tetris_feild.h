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

  //! @brief Tetris �t�B�[���h�̕���Ԃ�.
  //! @return �t�B�[���h�̕�(������, �ǂ��܂�).
  int GetWidth() const { return kWidth; }

  //! @brief Tetris �t�B�[���h�̍�����Ԃ�.
  //! @return �t�B�[���h�̍���(������, �����܂�).
  int GetHeight() const { return kHeight; }

  bool IsGameOver() const;

  bool IsPinch() const;

  bool IsEmpty() const;

  //! @brief T-spin ����p�Ɏw�肵���}�X��4�������܂��Ă��邩��Ԃ�.
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

  //! @brief �e�g���~�m���n�[�h�h���b�v�����Ƃ��̈ʒu��Ԃ�.
  //! @param tetromino �e�g���~�m�̌`��.
  //! @param tetromino_x �e�g���~�m�� x ���W.
  //! @param tetromino_y �e�g���~�m�� y ���W.
  //! @return �n�[�h�h���b�v��̃e�g���~�m�� (x, y) ���W.
  std::tuple<int, int> GetHardDropPosition(const Tetromino& tetromino,
                                           int tetromino_x,
                                           int tetromino_y) const;

  //! @brief �e�g���~�m���w�肵���ʒu�ɒu���邩��Ԃ�.
  //! @param tetromino �e�g���~�m�̌`��.
  //! @param tetromino_x �e�g���~�m�� x ���W.
  //! @param tetromino_y �e�g���~�m�� y ���W.
  //! @return �u����ꍇ�� true, �u���Ȃ��ꍇ�� false.
  bool IsValidPosition(const Tetromino& tetromino, int tetromino_x,
                       int tetromino_y) const;

  //! @brief �e�g���~�m���w�肵���ʒu�ɃZ�b�g����.
  //! @param tetromino �e�g���~�m�̌`��.
  //! @param tetromino_x �e�g���~�m�� x ���W.
  //! @param tetromino_y �e�g���~�m�� y ���W.
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
