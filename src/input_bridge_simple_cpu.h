//! @file input_bridge_simple_cpu.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "i_input_bridge.h"

namespace mytetris {

class InputBridgeSimpleCPU final : public IInputBridge {
 public:
  InputBridgeSimpleCPU();

  bool IsHoldRequested() const override;

  bool IsHardDropRequested() const override;

  int GetSoftDropCount() const override;

  bool IsRotateCWRequested() const override;

  bool IsRotateCCWRequested() const override;

  int GetLeftMoveCount() const override;

  int GetRightMoveCount() const override;

 private:
};

}  // namespace mytetris
