//! @file game_end_checker_for_battle.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "i_game_end_checker.h"
#include "tetris_feild.h"

namespace mytetris {

class GameEndCheckerForBattle final : public IGameEndChecker {
 public:
  GameEndCheckerForBattle(const std::shared_ptr<TetrisField>& enemy_field);
  ~GameEndCheckerForBattle() = default;

  bool IsGameEnd() const override;

  void SetGameMode(const TetrisGameMode) override;

 private:
  const std::shared_ptr<TetrisField> enemy_field_ptr_;
};

}  // namespace mytetris
