//! @file key_group.h
//! @brief
//!	Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

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
