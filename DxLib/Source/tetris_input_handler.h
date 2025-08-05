
//! @file tetris_input_handler.h
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

class TetrisInputHandler final {
 public:
  TetrisInputHandler(
      const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
      const std::shared_ptr<const TetrisField>& tetris_field_ptr,
      const std::shared_ptr<const Tetromino>& tetromino_ptr);
  ~TetrisInputHandler() = default;

  std::tuple<int, int> UpdatePosition(int x, int y) const;

 private:
  const std::shared_ptr<const DxLibKeyboard> dxlib_keyboard_ptr_;
  const std::shared_ptr<const TetrisField> tetris_field_ptr_;
  const std::shared_ptr<const Tetromino> tetromino_ptr_;
};

}  // namespace mytetris