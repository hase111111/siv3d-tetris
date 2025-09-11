
//! @file key_event_handler.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "key_event_handler.h"

#include <DxLib.h>

namespace mytetris {

KeyEventHandler::KeyEventHandler() {
  for (int i = 0; i < kKeyNum; i++) {
    key_releasing_counter_[i] = 0;
    key_pressing_counter_[i] = 0;
  }
}

void KeyEventHandler::Update() {
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

int KeyEventHandler::GetPressingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  return key_pressing_counter_[cast_code];
}

int KeyEventHandler::GetReleasingCount(const KeyHandle key_code) const {
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  return key_releasing_counter_[cast_code];
}

bool KeyEventHandler::IsAnyKeyPressed() const {
  for (int i = 0; i < kKeyNum; i++) {
    if (key_pressing_counter_[i] > 0) {
      return true;
    }
  }

  return false;
}

bool KeyEventHandler::IsAvailableCode(const int key_code) const {
  if (!(0 <= key_code && key_code < kKeyNum)) {
    return false;
  }

  return true;
}

}  // namespace mytetris
