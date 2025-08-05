
//! @file tetris_input_handler.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_input_handler.h"

#include "dxlib_assert.h"

namespace mytetris {

TetrisInputHandler::TetrisInputHandler(
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr,
    const std::shared_ptr<const Tetromino>& tetromino_ptr)
    : dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr) {
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr_);
  ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  ASSERT_NOT_NULL_PTR(tetromino_ptr_);
}

std::tuple<int, int> TetrisInputHandler::UpdatePosition(const int x,
                                                        const int y) const {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kLeft) == 1) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, x - 1, y)) {
      return std::make_tuple(x - 1, y);
    }
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kRight) == 1) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, x + 1, y)) {
      return std::make_tuple(x + 1, y);
    }
  }
  return std::make_tuple(x, y);
}

}  // namespace mytetris
