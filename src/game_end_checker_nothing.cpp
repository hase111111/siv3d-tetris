#include "game_end_checker_nothing.h"
//! @file game_end_checker_nothing.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

namespace mytetris {

bool GameEndCheckerNothing::IsGameEnd() const { return false; }

void GameEndCheckerNothing::SetGameMode(const TetrisGameMode) {}

}  // namespace mytetris
