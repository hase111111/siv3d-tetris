
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
    const std::shared_ptr<NextTetromino>& next_tetromino_ptr,
    const std::shared_ptr<HoldTetromino>& hold_tetromino_ptr)
    : dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      next_tetromino_ptr_(next_tetromino_ptr),
      hold_tetromino_ptr_(hold_tetromino_ptr) {
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr_);
  ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  ASSERT_NOT_NULL_PTR(tetromino_ptr_);
  ASSERT_NOT_NULL_PTR(next_tetromino_ptr_);
  ASSERT_NOT_NULL_PTR(hold_tetromino_ptr_);

  SetInitialTetrominoPosition();
}

void TetrisUpdater::Update() {
  ++drop_count_;

  UpdateTetrominoPosition();

  RotateTetromino();

  if (hold_tetromino_ptr_->CanHold() &&
      dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kW) == 1) {
    if (!hold_tetromino_ptr_->IsHold()) {
      hold_tetromino_ptr_->Hold(*tetromino_ptr_);
      *tetromino_ptr_ = next_tetromino_ptr_->GetNext();
      next_tetromino_ptr_->Next();
      SetInitialTetrominoPosition();
    } else {
      Tetromino hold_tetromino = hold_tetromino_ptr_->GetHoldTetromino();
      hold_tetromino_ptr_->Hold(*tetromino_ptr_);
      *tetromino_ptr_ = hold_tetromino;
      SetInitialTetrominoPosition();
    }

    hold_tetromino_ptr_->SetCanHold(false);
  }

  // テトリミノが下に落ちたらフィールドにセットする.
  if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                          tetromino_y_ + 1)) {
    ++fix_count_;
    if (fix_count_ >= fix_count_max_ || move_count_ >= move_count_max_) {
      SetTetromino();
    }
  } else {
    fix_count_ = 0;  // 下に落ちていないのでカウントをリセット.
  }
}

void TetrisUpdater::SetInitialTetrominoPosition() {
  const auto shape = tetromino_ptr_->GetShape();
  const auto x = (tetris_field_ptr_->GetWidth() - shape.size()) / 2;
  tetromino_x_ = static_cast<int>(x);
  tetromino_y_ = 2;
}

void TetrisUpdater::UpdateTetrominoPosition() {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    // ハードドロップ, validPosition が false になるまで下に落とす.
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
    }

    // フィールドにセットする.
    SetTetromino();

    drop_count_ = 0;  // 落下カウントをリセット.

  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kDown) % 5 == 1) {
    // ソフトドロップ, 指定したフレームに1回下に落とす.
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      drop_count_ = 0;
      ++tetromino_y_;
    }
  } else if (drop_count_ % drop_count_max_ == 0) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  }

  if (int cnt = dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kLeft);
      cnt == 1 || (cnt > horizontal_interval_ &&
                   (cnt - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ - 1,
                                           tetromino_y_)) {
      --tetromino_x_;  // 左に移動.

      // 地面についている場合,
      // 左右に動かすことで設置までのクールタイムを伸ばすことができる.
      // ただし，移動回数が多い場合, 強制的に設置させる.
      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // 左右に動いたのでカウントをリセット.
        fix_count_ = 0;

        // 移動回数をカウント.
        ++move_count_;
      }
    }
  } else if (int cnt = dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kRight);
             cnt == 1 ||
             (cnt > horizontal_interval_ &&
              (cnt - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ + 1,
                                           tetromino_y_)) {
      ++tetromino_x_;  // 右に移動.

      // 地面についている場合,
      // 左右に動かすことで設置までのクールタイムを伸ばすことができる.
      // ただし，移動回数が多い場合, 強制的に設置させる.
      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // 左右に動いたのでカウントをリセット.
        fix_count_ = 0;

        // 移動回数をカウント.
        ++move_count_;
      }
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

  hold_tetromino_ptr_->SetCanHold(true);

  fix_count_ = 0;
  move_count_ = 0;
}

void TetrisUpdater::RotateTetromino() {
  auto activate_left = [this](int x, int y) {
    tetromino_ptr_->LeftRotate();
    tetromino_x_ += x;
    tetromino_y_ += y;
    if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                            tetromino_y_ + 1)) {
      fix_count_ = 0;
      ++move_count_;
      drop_count_ = 0;
    }
  };

  auto activate_right = [this](int x, int y) {
    tetromino_ptr_->RightRotate();
    tetromino_x_ += x;
    tetromino_y_ += y;
    if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                            tetromino_y_ + 1)) {
      fix_count_ = 0;
      ++move_count_;
      drop_count_ = 0;
    }
  };

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kA) == 1) {
    if (CheckRotationCollision(true, 0, 0)) {
      activate_left(0, 0);
      return;
    }

    if (tetromino_ptr_->GetRotationType() == RotationType::kNone) {
      return;
    }

    if (tetromino_ptr_->GetRotationType() == RotationType::kNormal) {
      // 左右に軸をずらす.
      Tetromino left = *tetromino_ptr_;
      left.LeftRotate();
      const int rot_idx = left.GetRotationIndex();
      int offset_x = 0;
      int offset_y = 0;
      if (rot_idx == 0 || rot_idx == 3) {
        offset_x = 1;
      } else {
        offset_x = -1;
      }

      if (CheckRotationCollision(true, offset_x, offset_y)) {
        activate_left(offset_x, offset_y);
        return;
      }

      // 上下に軸をずらす.
      if (rot_idx == 0 || rot_idx == 2) {
        offset_y = 1;
      } else {
        offset_y = -1;
      }

      if (CheckRotationCollision(true, offset_x, offset_y)) {
        activate_left(offset_x, offset_y);
        return;
      }

      // 元に戻して上下に２つずらす.
      if (rot_idx == 0 || rot_idx == 2) {
        offset_x = 0;
        offset_y = -2;
      } else {
        offset_x = 0;
        offset_y = +2;
      }

      if (CheckRotationCollision(true, offset_x, offset_y)) {
        activate_left(offset_x, offset_y);
        return;
      }

      // 左右に軸をずらす.
      if (rot_idx == 0 || rot_idx == 3) {
        offset_x = 1;
      } else {
        offset_x = -1;
      }

      if (CheckRotationCollision(true, offset_x, offset_y)) {
        activate_left(offset_x, offset_y);
        return;
      }
    }

  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kD) == 1) {
    if (CheckRotationCollision(false, 0, 0)) {
      activate_right(0, 0);
      return;
    }

    if (tetromino_ptr_->GetRotationType() == RotationType::kNone) {
      return;
    }

    if (tetromino_ptr_->GetRotationType() == RotationType::kNormal) {
      // 左右に軸をずらす.
      Tetromino right = *tetromino_ptr_;
      right.RightRotate();
      const int rot_idx = right.GetRotationIndex();
      int offset_x = 0;
      int offset_y = 0;
      if (rot_idx == 2 || rot_idx == 3) {
        offset_x = 1;
      } else {
        offset_x = -1;
      }

      if (CheckRotationCollision(false, offset_x, offset_y)) {
        activate_right(offset_x, offset_y);
        return;
      }

      // 上下に軸をずらす.
      if (rot_idx == 0 || rot_idx == 2) {
        offset_y = 1;
      } else {
        offset_y = -1;
      }

      if (CheckRotationCollision(false, offset_x, offset_y)) {
        activate_right(offset_x, offset_y);
        return;
      }

      // 元に戻して上下に２つずらす.
      if (rot_idx == 0 || rot_idx == 2) {
        offset_x = 0;
        offset_y = -2;
      } else {
        offset_x = 0;
        offset_y = +2;
      }

      if (CheckRotationCollision(false, offset_x, offset_y)) {
        activate_right(offset_x, offset_y);
        return;
      }

      // 左右に軸をずらす.
      if (rot_idx == 2 || rot_idx == 3) {
        offset_x = 1;
      } else {
        offset_x = -1;
      }

      if (CheckRotationCollision(false, offset_x, offset_y)) {
        activate_right(offset_x, offset_y);
        return;
      }
    }
  }
}

bool TetrisUpdater::CheckRotationCollision(const bool is_left,
                                           const int offset_x,
                                           const int offset_y) const {
  Tetromino rotate_tetromino = *tetromino_ptr_;
  if (is_left) {
    rotate_tetromino.LeftRotate();
  } else {
    rotate_tetromino.RightRotate();
  }

  return tetris_field_ptr_->IsValidPosition(
      rotate_tetromino, tetromino_x_ + offset_x, tetromino_y_ + offset_y);
}

}  // namespace mytetris
