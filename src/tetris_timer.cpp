
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
  const std::string seconds_str = seconds < 10 ? nostd::format("0{}", seconds)
                                               : nostd::format("{}", seconds);
  const int milliseconds = (cnt % 60) * (1000 / 60);
  const std::string milliseconds_str =
      milliseconds < 100
          ? (milliseconds < 10 ? nostd::format("00{}", milliseconds)
                               : nostd::format("0{}", milliseconds))
          : nostd::format("{}", milliseconds);

  return nostd::format("{}:{}:{}", minutes, seconds_str, milliseconds_str);
}

}  // namespace mytetris
