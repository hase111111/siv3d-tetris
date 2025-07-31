
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

void DxLibKeyboard::update() {
  char now_key_status[kKeyNum];
  GetHitKeyStateAll(now_key_status);  // ���̃L�[�̓��͏�Ԃ��擾�D

  for (int i = 0; i < kKeyNum; ++i) {
    if (now_key_status[i] != 0) {
      // i�Ԃ̃L�[��������Ă�����D

      if (key_releasing_counter_[i] > 0) {
        // ������J�E���^��0���傫����΁D
        key_releasing_counter_[i] = 0;  // 0�ɖ߂��D
      }

      key_pressing_counter_[i]++;  // ������J�E���^�𑝂₷�D
    } else {
      // i�Ԃ̃L�[��������Ă�����D
      if (key_pressing_counter_[i] > 0) {
        // ������J�E���^��0���傫����΁D
        key_pressing_counter_[i] = 0;  // 0�ɖ߂��D
      }

      key_releasing_counter_[i]++;  // ������J�E���^�𑝂₷�D
    }
  }
}

int DxLibKeyboard::getPressingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!isAvailableCode(cast_code)) {
    return -1;
  }

  return key_pressing_counter_[cast_code];
}

int DxLibKeyboard::getReleasingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!isAvailableCode(cast_code)) {
    return -1;
  }

  return key_releasing_counter_[cast_code];
}

bool DxLibKeyboard::isAnyKeyPressed() const {
  for (int i = 0; i < kKeyNum; i++) {
    if (key_pressing_counter_[i] > 0) {
      return true;
    }
  }

  return false;
}

bool DxLibKeyboard::isAvailableCode(const int key_code) const {
  if (!(0 <= key_code && key_code < kKeyNum)) {
    return false;
  }

  return true;
}

// DxLib �̃L�[�R�[�h�̒�`���ω����Ă��Ȃ����m�F����D
static_assert(KEY_INPUT_ESCAPE == 0x01, "KEY_INPUT_ESCAPE is not 0x01.");
static_assert(KEY_INPUT_SPACE == 0x39, "KEY_INPUT_SPACE is not 0x39.");
static_assert(KEY_INPUT_Z == 0x2c, "KEY_INPUT_Z is not 0x2c.");
static_assert(KEY_INPUT_X == 0x2d, "KEY_INPUT_X is not 0x2d.");

}  // namespace mytetris
