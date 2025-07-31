
//! @file system_main.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>

#include "game_setting_record.h"

namespace mytetris {

//! @class SystemMain
//! @brief �Q�[���̏������E���C�����[�v�E�I���������s���N���X�D
class SystemMain final {
 public:
  SystemMain() = default;
  ~SystemMain() = default;

  //! @brief �Q�[���̏������������s���D
  //! ���s�����ꍇ�͑����ɏI�����邱�ƁD
  //! @return �������ɐ��������ꍇ�� true�C���s�����ꍇ�� false ��Ԃ��D
  bool initialize();

  //! @brief �Q�[���̏I���������s���D
  void finalize() const;

  //! @brief �Q�[���̃��C�����[�v�����s����D
  void main() const;

 private:
  const std::string kWindowClassName{"DxLibTetrisTHase"};

  std::shared_ptr<GameSettingRecord> game_setting_record_ptr_;
};

}  // namespace mytetris
