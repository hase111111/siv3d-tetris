//! @file input_bridge_simple_cpu.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "hold_tetromino.h"
#include "i_input_bridge.h"
#include "next_tetromino.h"
#include "tetris_feild.h"
#include "tetris_updater.h"
#include "tetromino.h"

namespace mytetris {

class InputBridgeSimpleCPU final : public IInputBridge {
 public:
  InputBridgeSimpleCPU(
      const std::shared_ptr<TetrisField>& tetris_field_ptr,
      const std::shared_ptr<Tetromino>& tetromino_ptr,
      const std::shared_ptr<NextTetromino>& next_tetromino_ptr,
      const std::shared_ptr<HoldTetromino>& hold_tetromino_ptr);

  void Update(int x, int y) override;

  bool IsHoldRequested() const override;

  bool IsHardDropRequested() const override;

  int GetSoftDropCount() const override;

  bool IsRotateCWRequested() const override;

  bool IsRotateCCWRequested() const override;

  int GetLeftMoveCount() const override;

  int GetRightMoveCount() const override;

 private:
  const std::shared_ptr<TetrisField> tetris_field_ptr_;
  const std::shared_ptr<Tetromino> tetromino_ptr_;
  const std::shared_ptr<NextTetromino> next_tetromino_ptr_;
  const std::shared_ptr<HoldTetromino> hold_tetromino_ptr_;
  const int control_frame{5};

  int counter_{0};
  int tetromino_x_{0}, tetromino_y_{0};
  int target_x_{7};
  int target_rotation_index_{3};
};

}  // namespace mytetris
