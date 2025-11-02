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
  void UpdateTarget();

  std::array<std::vector<std::vector<bool>>, 4> GetTetrominoShapes(
      const Tetromino& tetromino) const;

  std::tuple<int, int, int> GetBestPlacement(
      const std::array<std::vector<std::vector<bool>>, 4>& tetromino_shape)
      const;

  //! @brief フィールドの評価値を計算する.
  int CalculateFieldEvaluationValue(
      const std::array<std::array<bool, TetrisField::kWidth>,
                       TetrisField::kHeight>& field) const;

  const std::shared_ptr<TetrisField> tetris_field_ptr_;
  const std::shared_ptr<Tetromino> tetromino_ptr_;
  const std::shared_ptr<NextTetromino> next_tetromino_ptr_;
  const std::shared_ptr<HoldTetromino> hold_tetromino_ptr_;
  const int control_frame{1};

  std::array<std::array<bool, TetrisField::kWidth>, TetrisField::kHeight>
      last_field_{};
  int counter_{0};
  int tetromino_x_{0}, tetromino_y_{0};
  int target_x_{5};
  int target_rotation_index_{0};
  bool hold_requested_{false};
};

}  // namespace mytetris
