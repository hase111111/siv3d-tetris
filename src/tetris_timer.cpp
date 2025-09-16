
//! @file tetris_timer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_timer.h"

#include "my_format.h"

namespace mytetris {

void TetrisTimer::Update() { ++cnt; }

std::string TetrisTimer::GetTimeString() const {
  const int total_seconds = cnt / 60;
  const int minutes = total_seconds / 60;
  const int seconds = total_seconds % 60;
  const int milliseconds = (cnt % 60) * (1000 / 60);

  return nostd::format("{}:{}.{}", minutes, seconds, milliseconds);
}

}  // namespace mytetris
