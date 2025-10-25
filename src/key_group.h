#pragma once

namespace mytetris {

enum class KeyGroup : int {
  kLeft,
  kRight,
  kDown,
  kUp,
  kRotateCW,
  kRotateCCW,
  kHold,
  kPause,
  kDecide,
  kRestart,
  kToMenu,
  kGameEnd,
};

}  // namespace mytetris
