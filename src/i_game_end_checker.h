//! @file i_game_end_checker.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "tetris_game_mode.h"

namespace mytetris {

class IGameEndChecker {
 public:
  virtual ~IGameEndChecker() = default;

  virtual bool IsGameEnd() const = 0;

  virtual void SetGameMode(const TetrisGameMode game_mode) = 0;
};

}  // namespace mytetris
