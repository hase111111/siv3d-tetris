
//! @file tetris_updater.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_updater.h"

#include "dxlib_assert.h"

namespace mytetris {

TetrisUpdater::TetrisUpdater(
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

void TetrisUpdater::Update() {
  const int kDownCount = 60;

  ++count_;

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    // ハードドロップ, validPosition が false になるまで下に落とす.
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kDown) % 20 ==
             1) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      count_ = 0;
      ++tetromino_y_;
    }
  } else if (count_ % kDownCount == 0) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  }

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kLeft) == 1) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ - 1,
                                           tetromino_y_)) {
      --tetromino_x_;
    }
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kRight) == 1) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ + 1,
                                           tetromino_y_)) {
      ++tetromino_x_;
    }
  }
}

}  // namespace mytetris
