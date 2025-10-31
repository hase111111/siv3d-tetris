//! @file game_end_checker_nothing.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "i_game_end_checker.h"

namespace mytetris {

class GameEndCheckerNothing final : public IGameEndChecker {
 public:
  GameEndCheckerNothing() = default;
  ~GameEndCheckerNothing() = default;

  bool IsGameEnd() const override;

  void SetGameMode(const TetrisGameMode game_mode) override;
};

}  // namespace mytetris
