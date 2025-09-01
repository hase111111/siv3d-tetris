
//! @file render_util.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "render_util.h"

#include <DxLib.h>

namespace mytetris {

void DrawRect(const float left, const float top, const float right,
              const float bottom, const unsigned int color, const bool fill) {
  if (fill) {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, TRUE);
  } else {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, FALSE);
  }
}

void DrawLine(const float x1, const float y1, const float x2, const float y2,
              const unsigned int color, const int thickness) {
  DrawLineAA(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2),
             static_cast<int>(y2), color, thickness);
}

void DrawLineAlpha(float x1, float y1, float x2, float y2, unsigned int color,
                   int thickness, float alpha) {
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 255));
  DrawLineAA(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2),
             static_cast<int>(y2), color, thickness);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

}  // namespace mytetris
