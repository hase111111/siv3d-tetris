//! @file input_bridge_keyboard.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "input_bridge_simple_cpu.h"

#include "my_assert.h"

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
  tetromino_x_ = x;
  tetromino_y_ = y;

  ++counter_;
}

bool InputBridgeSimpleCPU::IsHoldRequested() const {
  //
  return false;
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

}  // namespace mytetris
