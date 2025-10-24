
//! @file key_event_handler.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>

#include "key_handle.h"

namespace mytetris {

//! @brief DxLib�̃L�[�{�[�h���͂��擾����N���X�D
class KeyEventHandler final {
 public:
  KeyEventHandler();

  //! @brief �L�[���͂��X�V����D
  //! ����𖈃t���[�����s���Ȃ��ƁC�L�[���͂��擾�ł��Ȃ��D
  void Update();

  //! @brief keyCode�̃L�[��������Ă���t���[�������擾����D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @return ������Ă���t���[�����D�ُ�� key_code ���n���ꂽ�ꍇ��-1��Ԃ��D
  int GetPressingCount(KeyHandle key_code) const;

  //! @brief keyCode�̃L�[��������Ă���t���[�������擾����D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @return ������Ă���t���[�����D�ُ�� key_code ���n���ꂽ�ꍇ��-1��Ԃ��D
  int GetReleasingCount(KeyHandle key_code) const;

 private:
  static const int kKeyNum = 256;  //!< DxLib�ɂ�����L�[�����D

  //! @brief keyCode���L���ȃL�[�ԍ����Ԃ��D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @retval true �L���ȃL�[�ԍ��ł���D
  //! @retval false �����ȃL�[�ԍ��ł���D
  bool IsAvailableCode(const int key_code) const;

  std::array<int, kKeyNum> key_pressing_counter_;   //!< ������J�E���^�D
  std::array<int, kKeyNum> key_releasing_counter_;  //!< ������J�E���^�D
};

}  // namespace mytetris
