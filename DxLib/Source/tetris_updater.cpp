
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
    const std::shared_ptr<TetrisField>& tetris_field_ptr,
    const std::shared_ptr<Tetromino>& tetromino_ptr,
    const std::shared_ptr<NextTetromino>& next_tetromino_ptr)
    : dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      next_tetromino_ptr_(next_tetromino_ptr) {
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr_);
  ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  ASSERT_NOT_NULL_PTR(tetromino_ptr_);

  SetInitialTetrominoPosition();
}

void TetrisUpdater::Update() {
  ++count_;

  UpdateTetrominoPosition();

  RotateTetromino();

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    SetTetromino();
  }
}

void TetrisUpdater::SetInitialTetrominoPosition() {
  const auto shape = tetromino_ptr_->GetShape();
  const auto x = (tetris_field_ptr_->GetWidth() - shape.size()) / 2;
  tetromino_x_ = static_cast<int>(x);
  tetromino_y_ = 2;
}

void TetrisUpdater::UpdateTetrominoPosition() {
  const int kDownCount = 60;
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    // ハードドロップ, validPosition が false になるまで下に落とす.
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kDown) % 5 == 1) {
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

void TetrisUpdater::SetTetromino() {
  if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                          tetromino_y_)) {
    return;
  }

  tetris_field_ptr_->SetTetromino(*tetromino_ptr_, tetromino_x_, tetromino_y_);
  tetris_field_ptr_->ClearLines();

  *tetromino_ptr_ = next_tetromino_ptr_->GetNext();
  next_tetromino_ptr_->Next();

  SetInitialTetrominoPosition();
}

void TetrisUpdater::RotateTetromino() {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kA) == 1) {
    Tetromino left_rotate_tetromino = *tetromino_ptr_;
    left_rotate_tetromino.LeftRotate();
    if (tetris_field_ptr_->IsValidPosition(left_rotate_tetromino, tetromino_x_,
                                           tetromino_y_)) {
      *tetromino_ptr_ = left_rotate_tetromino;
    }
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kD) == 1) {
    Tetromino right_rotate_tetromino = *tetromino_ptr_;
    right_rotate_tetromino.RightRotate();
    if (tetris_field_ptr_->IsValidPosition(right_rotate_tetromino, tetromino_x_,
                                           tetromino_y_)) {
      *tetromino_ptr_ = right_rotate_tetromino;
    }
  }
}

}  // namespace mytetris
