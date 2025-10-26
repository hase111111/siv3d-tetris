
//! @file tetris_updater.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_updater.h"

#include "my_assert.h"

namespace mytetris {

TetrisUpdater::TetrisUpdater(
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<TetrisField>& tetris_field_ptr,
    const std::shared_ptr<Tetromino>& tetromino_ptr,
    const std::shared_ptr<NextTetromino>& next_tetromino_ptr,
    const std::shared_ptr<HoldTetromino>& hold_tetromino_ptr,
    const std::shared_ptr<TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<DropCount>& drop_count_ptr,
    const std::shared_ptr<ScoreCalculator>& score_calculator_ptr,
    const std::shared_ptr<GameEndChecker>& game_end_checker_ptr,
    const std::shared_ptr<TetrisFieldEffect>& tetris_field_effect_ptr)
    : key_event_handler_ptr_(key_event_handler_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      next_tetromino_ptr_(next_tetromino_ptr),
      hold_tetromino_ptr_(hold_tetromino_ptr),
      tetris_level_ptr_(tetris_level_ptr),
      drop_count_ptr_(drop_count_ptr),
      score_calculator_ptr_(score_calculator_ptr),
      game_end_checker_ptr_(game_end_checker_ptr),
      tetris_field_effect_ptr_(tetris_field_effect_ptr),
      rotate_checker_{tetris_field_ptr} {
  // nullptr �`�F�b�N.
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetromino_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(next_tetromino_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(hold_tetromino_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(score_calculator_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(game_end_checker_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_effect_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(next_tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(hold_tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(score_calculator_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_end_checker_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_effect_ptr_);

  SetInitialTetrominoPosition();
}

void TetrisUpdater::Update() {
  if (tetris_field_ptr_->IsGameOver() || game_end_checker_ptr_->IsGameEnd()) {
    // �Q�[���I�[�o�[���͍X�V���Ȃ�.
    if (tetris_field_ptr_->IsGameOver() && !is_game_over_animation_finished_) {
      is_game_over_animation_finished_ = true;

      // ���ׂẴ��C�����N���A���C���֓o�^����.
      clear_lines_ = tetris_field_ptr_->GetAllLines();

      // �F��ς���.
      tetris_field_ptr_->SetDeathColor();
    } else {
      clear_lines_.clear();
    }

    return;
  }

  clear_lines_.clear();

  if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                         tetromino_y_ + 1)) {
    ++drop_count_;
  } else {
    drop_count_ = 0;  // �n�ʂɂ��Ă���̂ŗ����J�E���g�����Z�b�g.
  }

  UpdateTetrominoPosition();

  RotateTetromino();

  if (hold_tetromino_ptr_->CanHold() &&
      key_event_handler_ptr_->GetPressingCount(KeyGroup::kHold) == 1) {
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
  tetromino_y_ = 1;
}

void TetrisUpdater::UpdateTetrominoPosition() {
  const int max_ = drop_count_ptr_->GetCount(tetris_level_ptr_->GetLevel());
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    // �n�[�h�h���b�v, validPosition �� false �ɂȂ�܂ŉ��ɗ��Ƃ�.
    int cnt{0};
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
      ++cnt;
    }

    if (cnt != 0) {
      last_move_is_spin = false;
    }

    // �n�[�h�h���b�v�������X�R�A�����Z.
    score_calculator_ptr_->AddDropScore(cnt, true);

    // �t�B�[���h�ɃZ�b�g����.
    SetTetromino();

    drop_count_ = 0;  // �����J�E���g�����Z�b�g.

  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) % 5 ==
             1) {
    // �\�t�g�h���b�v, �w�肵���t���[����1�񉺂ɗ��Ƃ�.
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      drop_count_ = 0;
      ++tetromino_y_;
      last_move_is_spin = false;

      // �\�t�g�h���b�v�������X�R�A�����Z.
      score_calculator_ptr_->AddDropScore(1, false);
    }
  } else if (max_ != 0 && drop_count_ % max_ == 0) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  } else if (max_ == 0) {
    // ���x�����������ė����J�E���g��0�̏ꍇ, ���t���[�����ɗ��Ƃ�.
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  }

  if (int cnt_l = key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft);
      cnt_l == 1 || (cnt_l > horizontal_interval_ &&
                     (cnt_l - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ - 1,
                                           tetromino_y_)) {
      --tetromino_x_;  // ���Ɉړ�.
      last_move_is_spin = false;

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
  } else if (int cnt_r =
                 key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight);
             cnt_r == 1 ||
             (cnt_r > horizontal_interval_ &&
              (cnt_r - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ + 1,
                                           tetromino_y_)) {
      ++tetromino_x_;  // �E�Ɉړ�.
      last_move_is_spin = false;

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

  // �e�g���~�m���t�B�[���h�ɌŒ�.
  tetris_field_ptr_->SetTetromino(*tetromino_ptr_, tetromino_x_, tetromino_y_);

  // ���C���N���A����.
  clear_lines_ = tetris_field_ptr_->ClearLines();

  if (clear_lines_.size() > 0) {
    // ���C�����N���A�����ꍇ�X�R�A�����Z.
    score_calculator_ptr_->AddScore(
        static_cast<int>(clear_lines_.size()),
        tetromino_ptr_->GetColor() == TetrominoColor::kT && last_move_is_spin &&
            tetris_field_ptr_->IsOccupiedCorners(tetromino_x_, tetromino_y_,
                                                 true),
        tetris_field_ptr_->IsEmpty());
  } else {
    // ���C�����N���A���Ă��Ȃ��ꍇ�R���{�����Z�b�g.
    score_calculator_ptr_->ResetCombo();
  }

  tetromino_ptr_->Reshape(next_tetromino_ptr_->GetNext());
  next_tetromino_ptr_->Next();
  last_move_is_spin = false;

  SetInitialTetrominoPosition();

  hold_tetromino_ptr_->SetCanHold(true);

  fix_count_ = 0;
  move_count_ = 0;

  // �G�t�F�N�g�����Z�b�g.
  tetris_field_effect_ptr_->Reset();
}

void TetrisUpdater::RotateTetromino() {
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCCW) == 1) {
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
      last_move_is_spin = true;

      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // �n�ʂɂ��Ă���ꍇ, �ݒu�܂ł̃J�E���g�����Z�b�g.
        drop_count_ = 0;
        fix_count_ = 0;
        ++move_count_;
      }
    }
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCW) ==
             1) {
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
      last_move_is_spin = true;

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
