
//! @file drop_gauge.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "drop_gauge_renderer.h"

#include "game_const.h"
#include "render_util.h"

namespace mytetris {

DropGaugeRenderer::DropGaugeRenderer()
    : gauge_length_(158.f * game_const::kResolutionEx),
      gauge_thickness_(10.f * game_const::kResolutionEx) {}

void DropGaugeRenderer::Draw(const float render_x, const float render_y,
                             const float drop_percent, const float fix_percent,
                             const float move_percent) const {
  const float left_x = render_x - gauge_length_ / 2.f;
  const float right_x = render_x + gauge_length_ / 2.f;
  const float dist = 3.0f;

  // —‰º‚ÌƒQ[ƒW.
  DrawRect(left_x, render_y - gauge_thickness_ / 2.f, right_x,
           render_y + gauge_thickness_ / 2.f, 0xFF50FF50, false);
  DrawRect(left_x + 2.0f, render_y - gauge_thickness_ / 2.f + 2.0f,
           left_x + 2.0f + (gauge_length_ - 4.0f) * drop_percent,
           render_y + gauge_thickness_ / 2.f - 2.0f, 0xFF50FF50, true);

  // ŒÅ’è‚ÌƒQ[ƒW.
  DrawRect(left_x, render_y + gauge_thickness_ / 2.f + dist, right_x,
           render_y + gauge_thickness_ / 2.f + dist + gauge_thickness_,
           0xFFFF5050, false);
  DrawRect(left_x + 2.0f, render_y + gauge_thickness_ / 2.f + dist + 2.0f,
           left_x + 2.0f + (gauge_length_ - 4.0f) * fix_percent,
           render_y + gauge_thickness_ / 2.f + dist + gauge_thickness_ - 2.0f,
           0xFFFF5050, true);

  // ˆÚ“®‚ÌƒQ[ƒW.
  DrawRect(left_x, render_y + gauge_thickness_ * 3 / 2 + dist * 2, right_x,
           render_y + gauge_thickness_ * 3 / 2 + dist * 2 + gauge_thickness_,
           0xFFFFFF50, false);
  DrawRect(
      left_x + 2.0f, render_y + gauge_thickness_ * 3 / 2 + dist * 2 + 2.0f,
      left_x + 2.0f + (gauge_length_ - 4.0f) * move_percent,
      render_y + gauge_thickness_ * 3 / 2 + dist * 2 + gauge_thickness_ - 2.0f,
      0xFFFFFF50, true);
}

}  // namespace mytetris
