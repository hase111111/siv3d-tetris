
//! @file drop_gauge_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

class DropGaugeRenderer final {
 public:
  DropGaugeRenderer() = default;
  ~DropGaugeRenderer() = default;

  inline void SetFixPercent(const float percent) {
    fix_percent = percent < 0.0f ? 0.0f : (percent > 1.0f ? 1.0f : percent);
  }

  inline void SetDropPercent(const float percent) {
    drop_percent = percent < 0.0f ? 0.0f : (percent > 1.0f ? 1.0f : percent);
  }

  inline void SetMovePercent(const float percent) {
    move_percent = percent < 0.0f ? 0.0f : (percent > 1.0f ? 1.0f : percent);
  }

  // ドロップゲージの描画を行う.
  void Draw(float render_x, float render_y) const;

 private:
  const float gauge_length{158.0f};
  const float gauge_thickness{10.0f};
  float drop_percent{0.0f};  // ドロップゲージの割合(0.0f ~ 1.0f)
  float fix_percent{0.0f};   // 固定ゲージの割合(0.0f ~ 1.0f)
  float move_percent{0.0f};  // 移動ゲージの割合(0.0f ~ 1.0f)
};

}  // namespace mytetris
