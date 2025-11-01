//! @file input_bridge_keyboard.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "i_input_bridge.h"
#include "key_event_handler.h"

namespace mytetris {

class InputBridgeKeyBoard final : public IInputBridge {
 public:
  InputBridgeKeyBoard(
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr);

  bool IsHoldRequested() const override;

  bool IsHardDropRequested() const override;

  int GetSoftDropCount() const override;

  bool IsRotateCWRequested() const override;

  bool IsRotateCCWRequested() const override;

  int GetLeftMoveCount() const override;

  int GetRightMoveCount() const override;

 private:
  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
};

}  // namespace mytetris
