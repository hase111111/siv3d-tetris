
//! @file key_event_handler.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>

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

//! @brief DxLibのキーボード入力を取得するクラス．
class KeyEventHandler final {
 public:
  KeyEventHandler();

  //! @brief キー入力を更新する．
  //! これを毎フレーム実行しないと，キー入力を取得できない．
  void Update();

  //! @brief keyCodeのキーが押されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 押されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int GetPressingCount(KeyHandle key_code) const;

  //! @brief keyCodeのキーが離されているフレーム数を取得する．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @return 離されているフレーム数．異常な key_code が渡された場合は-1を返す．
  int GetReleasingCount(KeyHandle key_code) const;

 private:
  static const int kKeyNum = 256;  //!< DxLibにおけるキー総数．

  //! @brief keyCodeが有効なキー番号か返す．
  //! @param[in] keyCode どのキーを調べたいか，
  //! 例えばZキーだったら，KEY_INPUT_Z となる．
  //! @retval true 有効なキー番号である．
  //! @retval false 無効なキー番号である．
  bool IsAvailableCode(const int key_code) const;

  std::array<int, kKeyNum> key_pressing_counter_;   //!< 押されカウンタ．
  std::array<int, kKeyNum> key_releasing_counter_;  //!< 離されカウンタ．
};

}  // namespace mytetris
