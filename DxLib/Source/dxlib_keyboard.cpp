
//! @file dxlib_keyboard.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "dxlib_keyboard.h"

#include <DxLib.h>

namespace mytetris {

DxLibKeyboard::DxLibKeyboard() {
  for (int i = 0; i < kKeyNum; i++) {
    key_releasing_counter_[i] = 0;
    key_pressing_counter_[i] = 0;
  }
}

void DxLibKeyboard::Update() {
  char now_key_status[kKeyNum];
  GetHitKeyStateAll(now_key_status);  // 今のキーの入力状態を取得．

  for (int i = 0; i < kKeyNum; ++i) {
    if (now_key_status[i] != 0) {
      // i番のキーが押されていたら．

      if (key_releasing_counter_[i] > 0) {
        // 離されカウンタが0より大きければ．
        key_releasing_counter_[i] = 0;  // 0に戻す．
      }

      key_pressing_counter_[i]++;  // 押されカウンタを増やす．
    } else {
      // i番のキーが離されていたら．
      if (key_pressing_counter_[i] > 0) {
        // 押されカウンタが0より大きければ．
        key_pressing_counter_[i] = 0;  // 0に戻す．
      }

      key_releasing_counter_[i]++;  // 離されカウンタを増やす．
    }
  }
}

int DxLibKeyboard::GetPressingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  return key_pressing_counter_[cast_code];
}

int DxLibKeyboard::GetReleasingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  return key_releasing_counter_[cast_code];
}

bool DxLibKeyboard::IsAnyKeyPressed() const {
  for (int i = 0; i < kKeyNum; i++) {
    if (key_pressing_counter_[i] > 0) {
      return true;
    }
  }

  return false;
}

bool DxLibKeyboard::IsAvailableCode(const int key_code) const {
  if (!(0 <= key_code && key_code < kKeyNum)) {
    return false;
  }

  return true;
}

}  // namespace mytetris
