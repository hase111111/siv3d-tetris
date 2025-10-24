//! @file key_handle.h
//! @brief
//!	Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

enum class KeyHandle : int {
  kEscape = 0x01,
  kA = 0x1E,
  kB = 0x30,
  kC = 0x2E,
  kD = 0x20,
  kE = 0x12,
  kF = 0x21,
  kG = 0x22,
  kH = 0x23,
  kI = 0x17,
  kJ = 0x24,
  kK = 0x25,
  kL = 0x26,
  kM = 0x32,
  kN = 0x31,
  kO = 0x18,
  kP = 0x19,
  kQ = 0x10,
  kR = 0x13,
  kS = 0x1F,
  kT = 0x14,
  kU = 0x16,
  kV = 0x2F,
  kW = 0x11,
  kX = 0x2D,
  kY = 0x15,
  kZ = 0x2C,
  kSpace = 0x039,
  kLeft = 0xCB,
  kRight = 0xCD,
  kUp = 0xC8,
  kDown = 0xD0,
};

}  // namespace mytetris
