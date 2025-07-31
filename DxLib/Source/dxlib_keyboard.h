
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
};

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
  int getPressingCount(KeyHandle key_code) const;

  //! @brief keyCode�̃L�[��������Ă���t���[�������擾����D
  //! @param[in] keyCode �ǂ̃L�[�𒲂ׂ������C
  //! �Ⴆ��Z�L�[��������CKEY_INPUT_Z �ƂȂ�D
  //! @return ������Ă���t���[�����D�ُ�� key_code ���n���ꂽ�ꍇ��-1��Ԃ��D
  int getReleasingCount(KeyHandle key_code) const;

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
