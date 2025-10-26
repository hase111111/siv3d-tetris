
//! @file hold_tetromino.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <optional>

#include "tetromino.h"

namespace mytetris {

class HoldTetromino {
 public:
  HoldTetromino(const bool allow_hold) : allow_hold_(allow_hold) {}

  bool IsHold() const { return hold_tetromino_.has_value(); }

  void Hold(const Tetromino& tetromino) { hold_tetromino_ = tetromino; }

  Tetromino GetHoldTetromino() const { return *hold_tetromino_; }

  bool CanHold() const { return allow_hold_ && can_hold_; }

  void SetCanHold(bool can_hold) { can_hold_ = can_hold; }

 private:
  std::optional<Tetromino> hold_tetromino_{std::nullopt};
  const bool allow_hold_;
  bool can_hold_{true};
};

}  // namespace mytetris
