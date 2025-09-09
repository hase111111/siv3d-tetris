
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

// パラメータとして利用できるか確認するコンセプト.
// 参照でなく，ポインタでもなく，デフォルトコンストラクタが存在するものであること.
template <typename T>
concept IsParameter = !std::is_reference_v<T> && !std::is_pointer_v<T> &&
                      std::is_default_constructible_v<T>;

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

  //! @brief パラメータを全て削除する．
  void Reset();

 private:
  std::map<std::string, std::any> parameters_;
};

}  // namespace mytetris
