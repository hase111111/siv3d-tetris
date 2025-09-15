
//! @file key_event_handler.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "key_event_handler.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

namespace mytetris {

KeyEventHandler::KeyEventHandler() {
  for (int i = 0; i < kKeyNum; i++) {
    key_releasing_counter_[i] = 0;
    key_pressing_counter_[i] = 0;
  }
}

#if defined DXLIB_COMPILE
void KeyEventHandler::Update() {
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
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

static s3d::Input ToInput(const KeyHandle handle) {
  switch (handle) {
    case KeyHandle::kEscape:
      return s3d::KeyEscape;
    case KeyHandle::kA:
      return s3d::KeyA;
    case KeyHandle::kB:
      return s3d::KeyB;
    case KeyHandle::kC:
      return s3d::KeyC;
    case KeyHandle::kD:
      return s3d::KeyD;
    case KeyHandle::kE:
      return s3d::KeyE;
    case KeyHandle::kF:
      return s3d::KeyF;
    case KeyHandle::kG:
      return s3d::KeyG;
    case KeyHandle::kH:
      return s3d::KeyH;
    case KeyHandle::kI:
      return s3d::KeyI;
    case KeyHandle::kJ:
      return s3d::KeyJ;
    case KeyHandle::kK:
      return s3d::KeyK;
    case KeyHandle::kL:
      return s3d::KeyL;
    case KeyHandle::kM:
      return s3d::KeyM;
    case KeyHandle::kN:
      return s3d::KeyN;
    case KeyHandle::kO:
      return s3d::KeyO;
    case KeyHandle::kP:
      return s3d::KeyP;
    case KeyHandle::kQ:
      return s3d::KeyQ;
    case KeyHandle::kR:
      return s3d::KeyR;
    case KeyHandle::kS:
      return s3d::KeyS;
    case KeyHandle::kT:
      return s3d::KeyT;
    case KeyHandle::kU:
      return s3d::KeyU;
    case KeyHandle::kV:
      return s3d::KeyV;
    case KeyHandle::kW:
      return s3d::KeyW;
    case KeyHandle::kX:
      return s3d::KeyX;
    case KeyHandle::kY:
      return s3d::KeyY;
    case KeyHandle::kZ:
      return s3d::KeyZ;
    case KeyHandle::kSpace:
      return s3d::KeySpace;
    case KeyHandle::kLeft:
      return s3d::KeyLeft;
    case KeyHandle::kRight:
      return s3d::KeyRight;
    case KeyHandle::kUp:
      return s3d::KeyUp;
    case KeyHandle::kDown:
      return s3d::KeyDown;
    default:
      // ここには来ないはず．
      //! @todo C++の仕様上ここに来てしまう.
      return s3d::KeyEscape;
  }
}

void KeyEventHandler::Update() {
  for (int i = 0; i < kKeyNum; ++i) {
    const KeyHandle handle = static_cast<KeyHandle>(i);
    const s3d::Input& input = ToInput(handle);
    if (input.pressed()) {
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

#endif

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

bool KeyEventHandler::IsAvailableCode(const int key_code) const {
  if (!(0 <= key_code && key_code < kKeyNum)) {
    return false;
  }

  return true;
}

}  // namespace mytetris
