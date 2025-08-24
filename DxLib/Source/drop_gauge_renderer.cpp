
//! @file drop_gauge.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "drop_gauge_renderer.h"

#include "render_util.h"

namespace mytetris {

void DropGaugeRenderer::Draw(const float render_x, const float render_y) const {
  const float left_x = render_x - gauge_length / 2.f;
  const float right_x = render_x + gauge_length / 2.f;

  // —‰º‚ÌƒQ[ƒW.
  DrawRect(left_x, render_y - gauge_thickness / 2.f, right_x,
           render_y + gauge_thickness / 2.f, 0xFFFFFFFF, false);
  DrawRect(left_x + 2.0f, render_y - gauge_thickness / 2.f + 2.0f,
           left_x + 2.0f + (gauge_length - 4.0f) * drop_percent,
           render_y + gauge_thickness / 2.f - 2.0f, 0xFFFFFFFF, true);

  // ˆÚ“®‚ÌƒQ[ƒW.
  DrawRect(left_x, render_y + gauge_thickness / 2.f + 5.0f, right_x,
           render_y + gauge_thickness / 2.f + 5.0f + gauge_thickness,
           0xFFFF00FF, false);
  DrawRect(left_x + 2.0f, render_y + gauge_thickness / 2.f + 5.0f + 2.0f,
           left_x + 2.0f + (gauge_length - 4.0f) * move_percent,
           render_y + gauge_thickness / 2.f + 5.0f + gauge_thickness - 2.0f,
           0xFFFF00FF, true);
}

}  // namespace mytetris
