#pragma once

#include <cmath>
#include <string>

namespace mytetris {

//! @brief 受け取った小数を指定した桁数で四捨五入して文字列に変換する.
inline std::string RoundToString(const float value, const int decimal_places) {
  const int multiplier = static_cast<int>(std::pow(10.0f, decimal_places));
  const int rounded_value = static_cast<int>(std::round(value * multiplier));

  // 小数点以下の値を0埋めする.
  const int lower_val = rounded_value % multiplier;
  const int zero_num =
      decimal_places - static_cast<int>(std::to_string(lower_val).length());
  const std::string lower_str =
      std::string(zero_num, '0') + std::to_string(lower_val);
  return std::to_string(rounded_value / multiplier) + "." + lower_str;
}

}  // namespace mytetris
