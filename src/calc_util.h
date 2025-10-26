#pragma once

#include <cmath>
#include <string>

namespace mytetris {

//! @brief �󂯎�����������w�肵�������Ŏl�̌ܓ����ĕ�����ɕϊ�����.
inline std::string RoundToString(const float value, const int decimal_places) {
  const int multiplier = static_cast<int>(std::pow(10.0f, decimal_places));
  const int rounded_value = static_cast<int>(std::round(value * multiplier));

  // �����_�ȉ��̒l��0���߂���.
  const int lower_val = rounded_value % multiplier;
  const int zero_num =
      decimal_places - static_cast<int>(std::to_string(lower_val).length());
  const std::string lower_str =
      std::string(zero_num, '0') + std::to_string(lower_val);
  return std::to_string(rounded_value / multiplier) + "." + lower_str;
}

}  // namespace mytetris
