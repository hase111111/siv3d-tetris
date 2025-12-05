#pragma once

#include <sstream>
#include <string>

namespace mytetris {

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

//! @brief グローバルなログ出力オブジェクト.
//! Print << "message"; のように使用する.
static LogPrintInternal Print;

}  // namespace mytetris
