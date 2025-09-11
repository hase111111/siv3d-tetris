
//! @file scene_change_parameter.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <any>
#include <map>
#include <string>

#include "my_assert.h"

namespace mytetris {

// �p�����[�^�Ƃ��ė��p�ł��邩�m�F����R���Z�v�g.
// �Q�ƂłȂ��C�|�C���^�ł��Ȃ��C�f�t�H���g�R���X�g���N�^�����݂�����̂ł��邱��.
template <typename T>
concept IsParameter = !std::is_reference_v<T> && !std::is_pointer_v<T> &&
                      std::is_default_constructible_v<T>;

class SceneChangeParameter final {
 public:
  SceneChangeParameter() = default;
  ~SceneChangeParameter() = default;

  //! @brief �w�肵���L�[�����݂��邩�m�F����D
  //! @param[in] key �L�[�D
  bool HasParameter(const std::string& key) const {
    return parameters_.find(key) != parameters_.end();
  }

  //! @brief �p�����[�^��ݒ肷��D
  //! @param[in] key �L�[�D
  //! @param[in] value �l�D
  template <IsParameter T>
  void SetParameter(const std::string& key, T value) {
    parameters_[key] = value;
  }

  //! @brief �p�����[�^���擾����D
  //! @param[in] key �L�[�D
  //! @return �p�����[�^�D
  template <IsParameter T>
  T GetParameter(const std::string& key) const {
    auto it = parameters_.find(key);

    DEBUG_ASSERT(it != parameters_.end(), "Parameter not found. Key is " + key);

    T result = T{};

    try {
      result = std::any_cast<T>(it->second);
    } catch (const std::bad_any_cast& e) {
      DEBUG_ASSERT(
          false,
          "The type of the parameter associated with the specified key is "
          "different from the type specified in the template. :" +
              std::string(e.what()));
    }

    return result;
  }

  //! @brief �p�����[�^��S�č폜����D
  void Reset();

 private:
  std::map<std::string, std::any> parameters_;
};

}  // namespace mytetris
