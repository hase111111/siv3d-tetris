
//! @file game_const.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

class GameConst {
 public:
  static constexpr int kResolutionX = 1280;
  static constexpr int kResolutionY = 960;

  static constexpr char kWindowTitle[] = "Tetris";

 private:
  GameConst() = delete;
};

}  // namespace mytetris
