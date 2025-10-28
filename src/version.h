//! @file version.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

namespace mytetris {

//! @brief �Q�[���̃��W���[�o�[�W����.
inline constexpr int kVersionMajor = 1;

//! @brief �Q�[���̃}�C�i�[�o�[�W����.
inline constexpr int kVersionMinor = 2;

//! @brief �Q�[���̃p�b�`�o�[�W����.
inline constexpr int kVersionPatch = 1;

//! @brief �Q�[���̃o�[�W������������擾����.
//! @return �`���� "1.2.1" �̂悤�ɂȂ�.
inline const std::string GetVersionString() {
  const std::string version_string = std::to_string(kVersionMajor) + "." +
                                     std::to_string(kVersionMinor) + "." +
                                     std::to_string(kVersionPatch);
  return version_string;
}

}  // namespace mytetris
