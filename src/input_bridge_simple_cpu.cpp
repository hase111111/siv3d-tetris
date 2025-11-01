//! @file input_bridge_keyboard.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "input_bridge_simple_cpu.h"

#include "my_assert.h"

namespace mytetris {

InputBridgeSimpleCPU::InputBridgeSimpleCPU() {}

bool InputBridgeSimpleCPU::IsHoldRequested() const {
  //
  return false;
}

bool InputBridgeSimpleCPU::IsHardDropRequested() const {
  //
  return false;
}

int InputBridgeSimpleCPU::GetSoftDropCount() const {
  //
  return 0;
}

bool InputBridgeSimpleCPU::IsRotateCWRequested() const {
  //
  return true;
}

bool InputBridgeSimpleCPU::IsRotateCCWRequested() const {
  //
  return false;
}

int InputBridgeSimpleCPU::GetLeftMoveCount() const {
  //
  return 0;
}

int InputBridgeSimpleCPU::GetRightMoveCount() const {
  //
  return 0;
}

}  // namespace mytetris
