
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

  static const unsigned int kBlackColor;
  static const unsigned int kDarkGrayColor;
  static const unsigned int kGrayColor;
  static const unsigned int kLightGrayColor;
  static const unsigned int kWhiteColor;
  static const unsigned int kBrightWhiteColor;

 private:
  GameConst() = delete;
};

}  // namespace mytetris
