
//! @file my_format.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>

namespace mytetris {

// format ä÷êî
template <typename T>
inline void my_format_one(std::ostringstream &oss, const T &value) {
  oss << value;
}

template <typename... Args>
inline std::string format(std::string_view fmt, Args &&...args) {
  std::ostringstream oss;
  size_t pos = 0;
  [[maybe_unused]] auto insert_arg = [&](auto &&arg) {
    auto next_pos = fmt.find("{}", pos);
    if (next_pos == std::string_view::npos) {
      throw std::runtime_error("my format error");
    }
    oss << fmt.substr(pos, next_pos - pos);
    my_format_one(oss, arg);
    pos = next_pos + 2;
  };
  (insert_arg(args), ...);
  oss << fmt.substr(pos);
  return oss.str();
}

}  // namespace mytetris
