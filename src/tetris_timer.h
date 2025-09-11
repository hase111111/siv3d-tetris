
//! @file tetris_timer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

namespace mytetris {

class TetrisTimer final {
 public:
  TetrisTimer() = default;
  ~TetrisTimer() = default;

  void Update();

  std::string GetTimeString() const;

  inline int GetTime() const { return cnt; }

 private:
  int cnt{0};
};

}  // namespace mytetris
