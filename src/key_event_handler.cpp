#include "key_event_handler.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

#include "my_assert.h"
#include "touch_pad_addon.h"

namespace mytetris {

KeyEventHandler::KeyEventHandler(
    const std::shared_ptr<KeyConfigData>& key_config_data_ptr)
    : key_config_data_ptr_(key_config_data_ptr) {
  // nullptr チェック．
  DEBUG_ASSERT_NOT_NULL_PTR(key_config_data_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_config_data_ptr_);

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
    case KeyHandle::kLShift:
      return s3d::KeyLShift;
    case KeyHandle::kRShift:
      return s3d::KeyRShift;
    case KeyHandle::kLControl:
      return s3d::KeyLControl;
    case KeyHandle::kRControl:
      return s3d::KeyRControl;
    case KeyHandle::kLAlt:
      return s3d::KeyLAlt;
    case KeyHandle::kRAlt:
      return s3d::KeyRAlt;
    case KeyHandle::kEscape:
      return s3d::KeyEscape;
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
    case KeyHandle::kDelete:
      return s3d::KeyDelete;
    case KeyHandle::kMinus:
      return s3d::KeyMinus;
    case KeyHandle::kPrevTrack:
      return s3d::KeyPreviousTrack;
    case KeyHandle::kYen:
      return s3d::KeyYen_JIS;
    case KeyHandle::kAt:
      return s3d::KeyGraveAccent;
    case KeyHandle::kLBracket:
      return s3d::KeyLBracket;
    case KeyHandle::kRBracket:
      return s3d::KeyRBracket;
    case KeyHandle::kSemicolon:
      return s3d::KeySemicolon_JIS;
    case KeyHandle::kColon:
      return s3d::KeyColon_JIS;
    case KeyHandle::kComma:
      return s3d::KeyComma;
    case KeyHandle::kPeriod:
      return s3d::KeyPeriod;
    case KeyHandle::kSlash:
      return s3d::KeySlash;
    case KeyHandle::kEnter:
      return s3d::KeyEnter;
    case KeyHandle::k0:
      return s3d::Key0;
    case KeyHandle::k1:
      return s3d::Key1;
    case KeyHandle::k2:
      return s3d::Key2;
    case KeyHandle::k3:
      return s3d::Key3;
    case KeyHandle::k4:
      return s3d::Key4;
    case KeyHandle::k5:
      return s3d::Key5;
    case KeyHandle::k6:
      return s3d::Key6;
    case KeyHandle::k7:
      return s3d::Key7;
    case KeyHandle::k8:
      return s3d::Key8;
    case KeyHandle::k9:
      return s3d::Key9;
    case KeyHandle::kTab:
      return s3d::KeyTab;
    case KeyHandle::kBack:
      return s3d::KeyBackspace;
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

int KeyEventHandler::GetPressingCount(const KeyGroup group) const {
  const auto key_code = key_config_data_ptr_->Map(group);
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  // TouchPadアドオンを取得する.
  if (const int cnt = TouchPadAddon::pressedCount(group); 0 < cnt) {
    return cnt;
  }

  return key_pressing_counter_[cast_code];
}

int KeyEventHandler::GetReleasingCount(const KeyGroup group) const {
  const auto key_code = key_config_data_ptr_->Map(group);
  const int cast_code = static_cast<int>(key_code);
  if (!IsAvailableCode(cast_code)) {
    return -1;
  }

  return key_releasing_counter_[cast_code];
}

std::optional<KeyHandle> KeyEventHandler::GetInputKeyHandle() const {
  // 全入力をチェックして, 押されているキーのうち，
  // 最初に見つけたキーのKeyHandleを返す．
  for (const auto& handle : key_list) {
    const auto cast_code = static_cast<int>(handle);
    if (!IsAvailableCode(cast_code)) {
      continue;
    }
    if (key_pressing_counter_[cast_code] > 0) {
      return handle;
    }
  }

  return std::nullopt;
}

bool KeyEventHandler::IsAvailableCode(const int key_code) const {
  if (!(0 <= key_code && key_code < kKeyNum)) {
    return false;
  }

  return true;
}

}  // namespace mytetris
