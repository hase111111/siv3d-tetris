
#pragma once

namespace mytetris {

class GameConst {
 public:
  static constexpr int kResolutionX = 960;
  static constexpr int kResolutionY = 540;

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
