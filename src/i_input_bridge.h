//! @file i_input_bridge.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

class IInputBridge {
 public:
  virtual ~IInputBridge() = default;

  virtual void Update(int, int) {};

  //! @brief ホールド操作が行われたかどうかを取得する.
  virtual bool IsHoldRequested() const = 0;

  //! @brief ハードドロップ操作が行われたかどうかを取得する.
  virtual bool IsHardDropRequested() const = 0;

  //! @brief ソフトドロップ操作が行われたかどうかを取得する.
  virtual int GetSoftDropCount() const = 0;

  //! @brief 時計回り回転操作が行われたかどうかを取得する.
  virtual bool IsRotateCWRequested() const = 0;

  //! @brief 反時計回り回転操作が行われたかどうかを取得する.
  virtual bool IsRotateCCWRequested() const = 0;

  //! @brief 左移動操作が行われたかどうかを取得する.
  virtual int GetLeftMoveCount() const = 0;

  //! @brief 右移動操作が行われたかどうかを取得する.
  virtual int GetRightMoveCount() const = 0;
};

}  // namespace mytetris
