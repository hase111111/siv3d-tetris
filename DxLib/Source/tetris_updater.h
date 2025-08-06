
//! @file tetris_updater.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <tuple>

#include "dxlib_keyboard.h"
#include "tetris_feild.h"
#include "tetromino.h"

namespace mytetris {

class TetrisUpdater final {
 public:
  TetrisUpdater(const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
                const std::shared_ptr<const TetrisField>& tetris_field_ptr,
                const std::shared_ptr<const Tetromino>& tetromino_ptr);
  ~TetrisUpdater() = default;

  void Update();

  std::tuple<int, int> GetPosition() const {
    return std::make_tuple(tetromino_x_, tetromino_y_);
  }

 private:
  const std::shared_ptr<const DxLibKeyboard> dxlib_keyboard_ptr_;
  const std::shared_ptr<const TetrisField> tetris_field_ptr_;
  const std::shared_ptr<const Tetromino> tetromino_ptr_;

  int tetromino_x_{0}, tetromino_y_{0};
  int count_{0};
};

}  // namespace mytetris