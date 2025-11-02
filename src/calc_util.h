#pragma once

#include <cmath>
#include <random>
#include <string>

namespace mytetris {

namespace internal {

// 乱数エンジンはヘッダで直接グローバル変数として定義すると ODR
// 問題を起こすため、 関数内 static を用いて単一インスタンスを提供する。
inline std::mt19937& GetEngine() {
  static std::random_device seed_gen;
  static std::mt19937 engine(seed_gen());
  return engine;
}

}  // namespace internal

//! @brief 受け取った小数を指定した桁数で四捨五入して文字列に変換する.
//! @param value 四捨五入する小数値.
//! @param decimal_places 小数点以下の桁数. 2ならば小数点以下2桁まで表示.
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

inline int GetRandom(int min_, int max_) {
  // min~max の一様整数乱数を返す
  if (min_ > max_) std::swap(min_, max_);
  std::uniform_int_distribution<int> dist(min_, max_);
  return dist(internal::GetEngine());
}

}  // namespace mytetris
