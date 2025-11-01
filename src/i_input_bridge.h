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

  //! @brief �z�[���h���삪�s��ꂽ���ǂ������擾����.
  virtual bool IsHoldRequested() const = 0;

  //! @brief �n�[�h�h���b�v���삪�s��ꂽ���ǂ������擾����.
  virtual bool IsHardDropRequested() const = 0;

  //! @brief �\�t�g�h���b�v���삪�s��ꂽ���ǂ������擾����.
  virtual int GetSoftDropCount() const = 0;

  //! @brief ���v����]���삪�s��ꂽ���ǂ������擾����.
  virtual bool IsRotateCWRequested() const = 0;

  //! @brief �����v����]���삪�s��ꂽ���ǂ������擾����.
  virtual bool IsRotateCCWRequested() const = 0;

  //! @brief ���ړ����삪�s��ꂽ���ǂ������擾����.
  virtual int GetLeftMoveCount() const = 0;

  //! @brief �E�ړ����삪�s��ꂽ���ǂ������擾����.
  virtual int GetRightMoveCount() const = 0;
};

}  // namespace mytetris
