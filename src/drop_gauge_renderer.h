
//! @file drop_gauge_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

class DropGaugeRenderer final {
 public:
  DropGaugeRenderer();
  ~DropGaugeRenderer() = default;

  // ドロップゲージの描画を行う.
  void Draw(float render_x, float render_y, float drop_percent,
            float fix_percent, float move_percent) const;

 private:
  const float gauge_length_;
  const float gauge_thickness_;
};

}  // namespace mytetris
