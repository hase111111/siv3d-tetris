//! @file fade_effect.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "fade_effect.h"

#include "game_const.h"
#include "render_util.h"

namespace mytetris {

FadeEffect::FadeEffect(const int fade_time) : fade_time_(fade_time) {
  // 最初はフェード完了状態にする.
  counter_ = fade_time_ + 1;
}

bool FadeEffect::Update() {
  if (counter_ >= fade_time_) {
    return false;
  }

  counter_++;

  if (counter_ == fade_time_) {
    callback_();
  }

  return true;
}

void FadeEffect::Start(const FadeType fade_type,
                       const std::function<void()>& callback) {
  fade_type_ = fade_type;
  callback_ = callback;
  counter_ = 0;
}

void FadeEffect::Draw() const {
  if (fade_type_ == FadeType::kFadeOut) {
    DrawRectAlpha(0.f, 0.f, static_cast<float>(game_const::kResolutionX),
                  static_cast<float>(game_const::kResolutionY), 0x00000000,
                  true, counter_ / static_cast<float>(fade_time_));
  } else {
    DrawRectAlpha(0.f, 0.f, static_cast<float>(game_const::kResolutionX),
                  static_cast<float>(game_const::kResolutionY), 0x00000000,
                  true,
                  (fade_time_ - counter_) / static_cast<float>(fade_time_));
  }
}

}  // namespace mytetris
