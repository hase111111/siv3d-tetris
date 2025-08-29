
//! @file tetris_updater.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_updater.h"

#include "dxlib_assert.h"

namespace mytetris {

TetrisUpdater::TetrisUpdater(
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<TetrisField>& tetris_field_ptr,
    const std::shared_ptr<Tetromino>& tetromino_ptr,
    const std::shared_ptr<NextTetromino>& next_tetromino_ptr,
    const std::shared_ptr<HoldTetromino>& hold_tetromino_ptr)
    : key_event_handler_ptr_(key_event_handler_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      next_tetromino_ptr_(next_tetromino_ptr),
      hold_tetromino_ptr_(hold_tetromino_ptr),
      rotate_checker_{tetris_field_ptr} {
  ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
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
      key_event_handler_ptr_->GetPressingCount(KeyHandle::kW) == 1) {
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

  // �e�g���~�m�����ɗ�������t�B�[���h�ɃZ�b�g����.
  if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                          tetromino_y_ + 1)) {
    ++fix_count_;
    if (fix_count_ >= fix_count_max_ || move_count_ >= move_count_max_) {
      SetTetromino();
    }
  } else {
    fix_count_ = 0;  // ���ɗ����Ă��Ȃ��̂ŃJ�E���g�����Z�b�g.
  }
}

void TetrisUpdater::SetInitialTetrominoPosition() {
  const auto shape = tetromino_ptr_->GetShape();
  const auto x = (tetris_field_ptr_->GetWidth() - shape.size()) / 2;
  tetromino_x_ = static_cast<int>(x);
  tetromino_y_ = 2;
}

void TetrisUpdater::UpdateTetrominoPosition() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    // �n�[�h�h���b�v, validPosition �� false �ɂȂ�܂ŉ��ɗ��Ƃ�.
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
    }

    // �t�B�[���h�ɃZ�b�g����.
    SetTetromino();

    drop_count_ = 0;  // �����J�E���g�����Z�b�g.

  } else if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kDown) % 5 ==
             1) {
    // �\�t�g�h���b�v, �w�肵���t���[����1�񉺂ɗ��Ƃ�.
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

  if (int cnt = key_event_handler_ptr_->GetPressingCount(KeyHandle::kLeft);
      cnt == 1 || (cnt > horizontal_interval_ &&
                   (cnt - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ - 1,
                                           tetromino_y_)) {
      --tetromino_x_;  // ���Ɉړ�.

      // �n�ʂɂ��Ă���ꍇ,
      // ���E�ɓ��������ƂŐݒu�܂ł̃N�[���^�C����L�΂����Ƃ��ł���.
      // �������C�ړ��񐔂������ꍇ, �����I�ɐݒu������.
      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // ���E�ɓ������̂ŃJ�E���g�����Z�b�g.
        fix_count_ = 0;

        // �ړ��񐔂��J�E���g.
        ++move_count_;
      }
    }
  } else if (int cnt =
                 key_event_handler_ptr_->GetPressingCount(KeyHandle::kRight);
             cnt == 1 ||
             (cnt > horizontal_interval_ &&
              (cnt - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ + 1,
                                           tetromino_y_)) {
      ++tetromino_x_;  // �E�Ɉړ�.

      // �n�ʂɂ��Ă���ꍇ,
      // ���E�ɓ��������ƂŐݒu�܂ł̃N�[���^�C����L�΂����Ƃ��ł���.
      // �������C�ړ��񐔂������ꍇ, �����I�ɐݒu������.
      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // ���E�ɓ������̂ŃJ�E���g�����Z�b�g.
        fix_count_ = 0;

        // �ړ��񐔂��J�E���g.
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

  tetromino_ptr_->Reshape(next_tetromino_ptr_->GetNext());
  next_tetromino_ptr_->Next();

  SetInitialTetrominoPosition();

  hold_tetromino_ptr_->SetCanHold(true);

  fix_count_ = 0;
  move_count_ = 0;
}

void TetrisUpdater::RotateTetromino() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kA) == 1) {
    // ����].

    // ��]�ł��邩�`�F�b�N����. �\�ȏꍇ�̓I�t�Z�b�g���擾����.
    const auto result = rotate_checker_.CheckRotation(
        *tetromino_ptr_, tetromino_x_, tetromino_y_, true);

    if (result.has_value()) {
      // �I�t�Z�b�g���ʒu�����炵�ĉ�]������.
      const auto& [offset_x, offset_y] = result.value();

      tetromino_ptr_->LeftRotate();
      tetromino_x_ += offset_x;
      tetromino_y_ += offset_y;

      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // �n�ʂɂ��Ă���ꍇ, �ݒu�܂ł̃J�E���g�����Z�b�g.
        drop_count_ = 0;
        fix_count_ = 0;
        ++move_count_;
      }
    }
  } else if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kD) == 1) {
    // �E��].
    const auto result = rotate_checker_.CheckRotation(
        *tetromino_ptr_, tetromino_x_, tetromino_y_, false);

    // ��]�ł��邩�`�F�b�N����. �\�ȏꍇ�̓I�t�Z�b�g���擾����.
    if (result.has_value()) {
      // �I�t�Z�b�g���ʒu�����炵�ĉ�]������.
      const auto& [offset_x, offset_y] = result.value();

      tetromino_ptr_->RightRotate();
      tetromino_x_ += offset_x;
      tetromino_y_ += offset_y;

      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // �n�ʂɂ��Ă���ꍇ, �ݒu�܂ł̃J�E���g�����Z�b�g.
        fix_count_ = 0;
        ++move_count_;
        drop_count_ = 0;
      }
    }
  }
}

bool TetrisUpdater::CheckRotationCollision(const bool is_left,
                                           const int offset_x,
                                           const int offset_y) const {
  return tetris_field_ptr_->IsValidPosition(
      is_left ? tetromino_ptr_->GetRotatedLeft()
              : tetromino_ptr_->GetRotatedRight(),
      tetromino_x_ + offset_x, tetromino_y_ + offset_y);
}

}  // namespace mytetris
