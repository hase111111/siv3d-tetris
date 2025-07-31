
//! @file scene_change_parameter.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <map>
#include <string>
#include <variant>

#include "dxlib_assert.h"

namespace mytetris {

// �p�����[�^�Ƃ��ė��p�ł��邩�m�F����R���Z�v�g
template <typename T>
concept IsParameter = std::is_same_v<T, int> || std::is_same_v<T, double> ||
                      std::is_same_v<T, std::string>;

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

    ASSERT(it != parameters_.end(), "Parameter not found. Key is " + key);

    return std::get<T>(it->second);
  }

  //! @brief �p�����[�^��S�č폜����D
  void Reset();

 private:
  std::map<std::string, std::variant<int, double, std::string>> parameters_;
};

}  // namespace mytetris
