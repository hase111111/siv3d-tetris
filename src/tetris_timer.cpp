
//! @file tetris_timer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_timer.h"

#include <format>

namespace mytetris {

void TetrisTimer::Update() { ++cnt; }

std::string TetrisTimer::GetTimeString() const {
  int total_seconds = cnt / 60;
  int minutes = total_seconds / 60;
  int seconds = total_seconds % 60;
  int milliseconds = (cnt % 60) * (1000 / 60);

  return std::format("{:02}:{:02}.{:03}", minutes, seconds, milliseconds);
}

}  // namespace mytetris
