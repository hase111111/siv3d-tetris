
#pragma once

#include <array>

namespace mytetris {

//! @brief DxLib�̃L�[�{�[�h���͂��擾����N���X�D
class DxLibKeyboard final {
 public:
  DxLibKeyboard();

  //! @brief �L�[���͂��X�V����D
  //! ����𖈃t���[�����s���Ȃ��ƁC�L�[���͂��擾�ł��Ȃ��D
  void update();

  //! @brief keyCode�̃L�[��������Ă���t���[�������擾����D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @return ������Ă���t���[�����D�ُ�� key_code ���n���ꂽ�ꍇ��-1��Ԃ��D
  int getPressingCount(const int key_code) const;

  //! @brief keyCode�̃L�[��������Ă���t���[�������擾����D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @return ������Ă���t���[�����D�ُ�� key_code ���n���ꂽ�ꍇ��-1��Ԃ��D
  int getReleasingCount(const int key_code) const;

  //! @brief �ǂꂩ�̃L�[��������Ă��邩�Ԃ��D
  //! @retval true �ǂꂩ�̃L�[��������Ă���D
  //! @retval false �ǂ��������Ă��Ȃ��D
  bool isAnyKeyPressed() const;

 private:
  static const int kKeyNum = 256;  //!< DxLib�ɂ�����L�[�����D

  //! @brief keyCode���L���ȃL�[�ԍ����Ԃ��D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @retval true �L���ȃL�[�ԍ��ł���D
  //! @retval false �����ȃL�[�ԍ��ł���D
  bool isAvailableCode(const int key_code) const;

  std::array<int, kKeyNum> key_pressing_counter_;  //!< ������J�E���^�D
  std::array<int, kKeyNum> key_releasing_counter_;  //!< ������J�E���^�D
};

}  // namespace mytetris
