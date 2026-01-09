#pragma once

#include <string>

namespace mytetris {

//! @brief ゲームのメジャーバージョン.
inline constexpr int kVersionMajor = 1;

//! @brief ゲームのマイナーバージョン.
inline constexpr int kVersionMinor = 4;

//! @brief ゲームのパッチバージョン.
inline constexpr int kVersionPatch = 0;

//! @brief ゲームのバージョン文字列を取得する.
//! @return 形式は "1.2.1" のようになる.
inline const std::string GetVersionString() {
  const std::string version_string = std::to_string(kVersionMajor) + "." +
                                     std::to_string(kVersionMinor) + "." +
                                     std::to_string(kVersionPatch);
  return version_string;
}

}  // namespace mytetris
