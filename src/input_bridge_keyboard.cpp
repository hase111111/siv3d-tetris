//! @file input_bridge_keyboard.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "input_bridge_keyboard.h"

#include "my_assert.h"

namespace mytetris {

InputBridgeKeyBoard::InputBridgeKeyBoard(
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr)
    : key_event_handler_ptr_(key_event_handler_ptr) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
}

bool InputBridgeKeyBoard::IsHoldRequested() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kHold) == 1;
}

bool InputBridgeKeyBoard::IsHardDropRequested() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1;
}

int InputBridgeKeyBoard::GetSoftDropCount() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown);
}

bool InputBridgeKeyBoard::IsRotateCWRequested() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCW) == 1;
}

bool InputBridgeKeyBoard::IsRotateCCWRequested() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kRotateCCW) == 1;
}

int InputBridgeKeyBoard::GetLeftMoveCount() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft);
}

int InputBridgeKeyBoard::GetRightMoveCount() const {
  return key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight);
}

}  // namespace mytetris
