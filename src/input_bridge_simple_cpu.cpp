//! @file input_bridge_keyboard.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "input_bridge_simple_cpu.h"

#include <array>
#include <optional>

#include "log_print.h"
#include "my_assert.h"
#include "tetris_evalution_util.h"

namespace mytetris {

InputBridgeSimpleCPU::InputBridgeSimpleCPU(
    const std::shared_ptr<TetrisField>& tetris_field_ptr,
    const std::shared_ptr<Tetromino>& tetromino_ptr,
    const std::shared_ptr<NextTetromino>& next_tetromino_ptr,
    const std::shared_ptr<HoldTetromino>& hold_tetromino_ptr)
    : tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      next_tetromino_ptr_(next_tetromino_ptr),
      hold_tetromino_ptr_(hold_tetromino_ptr) {}

void InputBridgeSimpleCPU::Update(const int x, const int y) {
  ++counter_;

  tetromino_x_ = x;
  tetromino_y_ = y;

  const auto current_field = tetris_field_ptr_->GetOccupancyField();
  if (current_field != last_field_) {
    // フィールドが変化したらターゲットを更新.
    last_field_ = current_field;
    UpdateTarget();
  }
}

bool InputBridgeSimpleCPU::IsHoldRequested() const {
  return hold_requested_ && hold_tetromino_ptr_->CanHold();
}

bool InputBridgeSimpleCPU::IsHardDropRequested() const {
  if (counter_ % control_frame != control_frame - 1) {
    return false;
  }

  if (target_x_ == tetromino_x_ &&
      tetromino_ptr_->GetRotationIndex() == target_rotation_index_) {
    return true;
  }
  return false;
}

int InputBridgeSimpleCPU::GetSoftDropCount() const {
  //
  return 0;
}

bool InputBridgeSimpleCPU::IsRotateCWRequested() const {
  if (counter_ % control_frame != control_frame / 2) {
    return false;
  }

  if (tetromino_ptr_->GetRotationIndex() != target_rotation_index_) {
    return true;
  } else {
    return false;
  }
}

bool InputBridgeSimpleCPU::IsRotateCCWRequested() const {
  //
  return false;
}

int InputBridgeSimpleCPU::GetLeftMoveCount() const {
  if (counter_ % control_frame != control_frame - 1) {
    return 0;
  }

  if (target_x_ < tetromino_x_) {
    return 1;
  }
  return 0;
}

int InputBridgeSimpleCPU::GetRightMoveCount() const {
  if (counter_ % control_frame != control_frame - 1) {
    return 0;
  }

  if (tetromino_x_ < target_x_) {
    return 1;
  }
  return 0;
}

void InputBridgeSimpleCPU::UpdateTarget() {
  using Shape = std::vector<std::vector<bool>>;

  const auto tetromino_shape = GetTetrominoShapes(*tetromino_ptr_);

  const auto [best_x, best_rotation_index, best_score] =
      GetBestPlacement(tetromino_shape);

  if (hold_tetromino_ptr_->CanHold()) {
    // ホールド可能ならばホールドした場合も評価.
    if (!hold_tetromino_ptr_->IsHold()) {
      // 未だホールドしていない場合,ホールドして次のテトリミノを置く場合を評価.
      const auto next_tetromino = next_tetromino_ptr_->GetNext();
      const auto next_tetromino_shape = GetTetrominoShapes(next_tetromino);
      const auto [hold_best_x, hold_best_rotation_index, hold_best_score] =
          GetBestPlacement(next_tetromino_shape);
      if (hold_best_score > best_score) {
        // ホールドした方が良い場合.
        hold_requested_ = true;
        target_x_ = hold_best_x;
        target_rotation_index_ = hold_best_rotation_index;
      } else {
        // ホールドしない方が良い場合.
        hold_requested_ = false;
        target_x_ = best_x;
        target_rotation_index_ = best_rotation_index;
      }
    } else {
      // 既にホールドしている場合,ホールドした場合としない場合を評価.
      const auto hold_tetromino = hold_tetromino_ptr_->GetHoldTetromino();
      const auto hold_tetromino_shape = GetTetrominoShapes(hold_tetromino);
      const auto [hold_best_x, hold_best_rotation_index, hold_best_score] =
          GetBestPlacement(hold_tetromino_shape);
      if (hold_best_score > best_score) {
        // ホールドした方が良い場合.
        hold_requested_ = true;
        target_x_ = hold_best_x;
        target_rotation_index_ = hold_best_rotation_index;
      } else {
        // ホールドしない方が良い場合.
        hold_requested_ = false;
        target_x_ = best_x;
        target_rotation_index_ = best_rotation_index;
      }
    }
  } else {
    // ホールド不可ならそのまま決定.
    hold_requested_ = false;
    target_x_ = best_x;
    target_rotation_index_ = best_rotation_index;
  }
}

std::array<std::vector<std::vector<bool>>, 4>
InputBridgeSimpleCPU::GetTetrominoShapes(const Tetromino& tetromino) const {
  return {
      tetromino.GetResetRotation().GetShape(),
      tetromino.GetResetRotation().GetRotatedRight().GetShape(),
      tetromino.GetResetRotation()
          .GetRotatedRight()
          .GetRotatedRight()
          .GetShape(),
      tetromino.GetResetRotation().GetRotatedLeft().GetShape(),
  };
}

std::tuple<int, int, int> InputBridgeSimpleCPU::GetBestPlacement(
    const std::array<std::vector<std::vector<bool>>, 4>& tetromino_shape)
    const {
  int best_score = std::numeric_limits<int>::min();
  int x = 0;
  int index = 0;

  for (int i{-2}; i <= TetrisField::kWidth + 2; ++i) {
    for (int rotation_index{0}; rotation_index < 4; ++rotation_index) {
      const auto& shape = tetromino_shape[rotation_index];
      const auto placed_field_opt = PlaceTetromino(last_field_, shape, i);
      if (!placed_field_opt.has_value()) {
        continue;
      }
      const auto [deleted_line_count, field] =
          DeleteFullLines(placed_field_opt.value());
      const int score =
          CalculateFieldEvaluationValue(field, deleted_line_count);
      if (score > best_score) {
        best_score = score;
        x = i;
        index = rotation_index;
      }
    }
  }

  return {x, index, best_score};
}

int InputBridgeSimpleCPU::CalculateFieldEvaluationValue(
    const std::array<std::array<bool, TetrisField::kWidth>,
                     TetrisField::kHeight>& field,
    const int line) const {
  const auto hole = GetHoleCountsPerColumn(field);
  const auto height_diff_sum = GetHeightDifferenceSquareSum(field);

  int score = 0;

  score += line * 1;

  for (const auto& count : hole) {
    score -= count * 100;
  }

  score -= height_diff_sum * 10;

  return static_cast<int>(score);
}

}  // namespace mytetris
