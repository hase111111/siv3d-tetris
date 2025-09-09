
//! @file tetris_game_mode.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

namespace mytetris {

enum class TetrisGameMode : int {
  kEndless,
  kSprint,
  kUltra,
  kMarathon,
  kUeda,
  kPentris,
  kTrick,
  kPractice,
};

inline std::string ToString(const TetrisGameMode game_mode) {
  switch (game_mode) {
    case TetrisGameMode::kEndless:
      return "Endless";
    case TetrisGameMode::kSprint:
      return "Sprint";
    case TetrisGameMode::kUltra:
      return "Ultra";
    case TetrisGameMode::kMarathon:
      return "Marathon";
    case TetrisGameMode::kUeda:
      return "Ueda";
    case TetrisGameMode::kPentris:
      return "Pentris";
    case TetrisGameMode::kTrick:
      return "Trick";
    case TetrisGameMode::kPractice:
      return "Practice";
    default:
      return "Unknown";
  }
}

}  // namespace mytetris
