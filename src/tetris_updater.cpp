
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
  // nullptr チェック.
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
    // ゲームオーバー時は更新しない.
    if (tetris_field_ptr_->IsGameOver() && !is_game_over_animation_finished_) {
      is_game_over_animation_finished_ = true;

      // すべてのラインをクリアラインへ登録する.
      clear_lines_ = tetris_field_ptr_->GetAllLines();

      // 色を変える.
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
    drop_count_ = 0;  // 地面についているので落下カウントをリセット.
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
  tetromino_y_ = 1;
}

void TetrisUpdater::UpdateTetrominoPosition() {
  const int max_ = drop_count_ptr_->GetCount(tetris_level_ptr_->GetLevel());
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    // ハードドロップ, validPosition が false になるまで下に落とす.
    int cnt{0};
    while (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
      ++tetromino_y_;
      ++cnt;
    }

    if (cnt != 0) {
      last_move_is_spin = false;
    }

    // ハードドロップした分スコアを加算.
    score_calculator_ptr_->AddDropScore(cnt, true);

    // フィールドにセットする.
    SetTetromino();

    drop_count_ = 0;  // 落下カウントをリセット.

  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) % 5 ==
             1) {
    // ソフトドロップ, 指定したフレームに1回下に落とす.
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      drop_count_ = 0;
      ++tetromino_y_;
      last_move_is_spin = false;

      // ソフトドロップした分スコアを加算.
      score_calculator_ptr_->AddDropScore(1, false);
    }
  } else if (max_ != 0 && drop_count_ % max_ == 0) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                           tetromino_y_ + 1)) {
      ++tetromino_y_;
    }
  } else if (max_ == 0) {
    // レベルが高すぎて落下カウントが0の場合, 毎フレーム下に落とす.
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
      --tetromino_x_;  // 左に移動.
      last_move_is_spin = false;

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
  } else if (int cnt_r =
                 key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight);
             cnt_r == 1 ||
             (cnt_r > horizontal_interval_ &&
              (cnt_r - horizontal_interval_) % horizontal_count_ == 0)) {
    if (tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_ + 1,
                                           tetromino_y_)) {
      ++tetromino_x_;  // 右に移動.
      last_move_is_spin = false;

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

  // テトリミノをフィールドに固定.
  tetris_field_ptr_->SetTetromino(*tetromino_ptr_, tetromino_x_, tetromino_y_);

  // ラインクリア処理.
  clear_lines_ = tetris_field_ptr_->ClearLines();

  if (clear_lines_.size() > 0) {
    // ラインをクリアした場合スコアを加算.
    score_calculator_ptr_->AddScore(
        static_cast<int>(clear_lines_.size()),
        tetromino_ptr_->GetColor() == TetrominoColor::kT && last_move_is_spin &&
            tetris_field_ptr_->IsOccupiedCorners(tetromino_x_, tetromino_y_,
                                                 true),
        tetris_field_ptr_->IsEmpty());
  } else {
    // ラインをクリアしていない場合コンボをリセット.
    score_calculator_ptr_->ResetCombo();
  }

  tetromino_ptr_->Reshape(next_tetromino_ptr_->GetNext());
  next_tetromino_ptr_->Next();
  last_move_is_spin = false;

  SetInitialTetrominoPosition();

  hold_tetromino_ptr_->SetCanHold(true);

  fix_count_ = 0;
  move_count_ = 0;

  // エフェクトをリセット.
  tetris_field_effect_ptr_->Reset();
}

void TetrisUpdater::RotateTetromino() {
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCCW) == 1) {
    // 左回転.

    // 回転できるかチェックする. 可能な場合はオフセットを取得する.
    const auto result = rotate_checker_.CheckRotation(
        *tetromino_ptr_, tetromino_x_, tetromino_y_, true);

    if (result.has_value()) {
      // オフセット分位置をずらして回転させる.
      const auto& [offset_x, offset_y] = result.value();

      tetromino_ptr_->LeftRotate();
      tetromino_x_ += offset_x;
      tetromino_y_ += offset_y;
      last_move_is_spin = true;

      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // 地面についている場合, 設置までのカウントをリセット.
        drop_count_ = 0;
        fix_count_ = 0;
        ++move_count_;
      }
    }
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCW) ==
             1) {
    // 右回転.
    const auto result = rotate_checker_.CheckRotation(
        *tetromino_ptr_, tetromino_x_, tetromino_y_, false);

    // 回転できるかチェックする. 可能な場合はオフセットを取得する.
    if (result.has_value()) {
      // オフセット分位置をずらして回転させる.
      const auto& [offset_x, offset_y] = result.value();

      tetromino_ptr_->RightRotate();
      tetromino_x_ += offset_x;
      tetromino_y_ += offset_y;
      last_move_is_spin = true;

      if (!tetris_field_ptr_->IsValidPosition(*tetromino_ptr_, tetromino_x_,
                                              tetromino_y_ + 1)) {
        // 地面についている場合, 設置までのカウントをリセット.
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
