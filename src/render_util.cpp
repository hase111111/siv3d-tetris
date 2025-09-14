
//! @file render_util.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "render_util.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

namespace mytetris {

#if defined DXLIB_COMPILE

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

void DrawRectAlpha(float left, float top, float right, float bottom,
                   unsigned int color, bool fill, float alpha) {
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 255));
  if (fill) {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, TRUE);
  } else {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, FALSE);
  }
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawLine(const float x1, const float y1, const float x2, const float y2,
              const unsigned int color, const float thickness) {
  DrawLineAA(x1, y1, x2, y2, color, thickness);
}

void DrawLineAlpha(float x1, float y1, float x2, float y2, unsigned int color,
                   float thickness, float alpha) {
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 255));
  DrawLineAA(x1, y1, x2, y2, color, thickness);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

#elif defined SIV3D_COMPILE

static s3d::ColorF ColorFromUint32(const unsigned int color,
                                   const float alpha) {
  const int b = color & 0xFF;
  const int g = (color >> 8) & 0xFF;
  const int r = (color >> 16) & 0xFF;
  return s3d::ColorF(r / 255.0, g / 255.0, b / 255.0, alpha);
}

void DrawRect(const float left, const float top, const float right,
              const float bottom, const unsigned int color, const bool fill) {
  const s3d::Rect rect(static_cast<int32>(left), static_cast<int32>(top),
                       static_cast<int32>(right - left),
                       static_cast<int32>(bottom - top));

  if (fill) {
    rect.draw(ColorFromUint32(color, 1.0));
  } else {
    rect.drawFrame(1.0, ColorFromUint32(color, 1.0));
  }
}

void DrawRectAlpha(float left, float top, float right, float bottom,
                   unsigned int color, bool fill, float alpha) {
  const s3d::Rect rect(static_cast<int32>(left), static_cast<int32>(top),
                       static_cast<int32>(right - left),
                       static_cast<int32>(bottom - top));

  if (fill) {
    rect.draw(ColorFromUint32(color, alpha));
  } else {
    rect.drawFrame(1.0, ColorFromUint32(color, alpha));
  }
}

void DrawLine(const float x1, const float y1, const float x2, const float y2,
              const unsigned int color, const float thickness) {
  s3d::Line(x1, y1, x2, y2).draw(thickness, ColorFromUint32(color, 1.0));
}

void DrawLineAlpha(float x1, float y1, float x2, float y2, unsigned int color,
                   float thickness, float alpha) {
  s3d::Line(x1, y1, x2, y2).draw(thickness, ColorFromUint32(color, alpha));
}

#endif  // defined DXLIB_COMPILE

}  // namespace mytetris
