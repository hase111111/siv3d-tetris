
//! @file fade_effect.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <functional>
#include <vector>

namespace mytetris {

enum class FadeType {
  kFadeIn,
  kFadeOut,
};

class FadeEffect final {
 public:
  FadeEffect(int fade_time);
  ~FadeEffect() = default;

  bool Update();

  void Start(FadeType fade_type, const std::function<void()>& callback);

  void Draw() const;

 private:
  const int fade_time_;

  FadeType fade_type_{FadeType::kFadeIn};
  std::function<void()> callback_{[]() {}};
  int counter_{0};
};

}  // namespace mytetris
