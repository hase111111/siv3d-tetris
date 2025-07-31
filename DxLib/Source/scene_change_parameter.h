
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

// パラメータとして利用できるか確認するコンセプト
template <typename T>
concept IsParameter = std::is_same_v<T, int> || std::is_same_v<T, double> ||
                      std::is_same_v<T, std::string>;

class SceneChangeParameter final {
 public:
  SceneChangeParameter() = default;
  ~SceneChangeParameter() = default;

  //! @brief 指定したキーが存在するか確認する．
  //! @param[in] key キー．
  bool HasParameter(const std::string& key) const {
    return parameters_.find(key) != parameters_.end();
  }

  //! @brief パラメータを設定する．
  //! @param[in] key キー．
  //! @param[in] value 値．
  template <IsParameter T>
  void SetParameter(const std::string& key, T value) {
    parameters_[key] = value;
  }

  //! @brief パラメータを取得する．
  //! @param[in] key キー．
  //! @return パラメータ．
  template <IsParameter T>
  T GetParameter(const std::string& key) const {
    auto it = parameters_.find(key);

    ASSERT(it != parameters_.end(), "Parameter not found. Key is " + key);

    return std::get<T>(it->second);
  }

  //! @brief パラメータを全て削除する．
  void Reset();

 private:
  std::map<std::string, std::variant<int, double, std::string>> parameters_;
};

}  // namespace mytetris
