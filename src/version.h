#pragma once

#include <string>

namespace mytetris {

inline constexpr int kVersionMajor = 1;
inline constexpr int kVersionMinor = 2;
inline constexpr int kVersionPatch = 1;

inline const std::string GetVersionString() {
  const std::string version_string = std::to_string(kVersionMajor) + "." +
                                     std::to_string(kVersionMinor) + "." +
                                     std::to_string(kVersionPatch);
  return version_string;
}

}  // namespace mytetris
