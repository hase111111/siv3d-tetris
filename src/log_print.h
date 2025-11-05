//! @file log_print.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <sstream>
#include <string>

namespace mytetris::internal {

class LogPrintInternal final {
 public:
  //! @brief << 演算子オーバーロード.
  template <typename T>
  LogPrintInternal& operator<<(const T& message) {
    PrintImpl(message);
    return *this;
  }

 private:
  template <typename T>
  void PrintImpl(const T& message) {
    // まず string に変換.
    std::stringstream ss;
    ss << message;
    std::string str = ss.str();
    PrintString(str);
  }

  void PrintString(const std::string str);
};

}  // namespace mytetris::internal

namespace mytetris {

static internal::LogPrintInternal Print;

}  // namespace mytetris
