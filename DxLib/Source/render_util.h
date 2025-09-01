
//! @file render_util.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

void DrawRect(float left, float top, float right, float bottom,
              unsigned int color, bool fill);

void DrawLine(float x1, float y1, float x2, float y2, unsigned int color,
              int thickness);

void DrawLineAlpha(float x1, float y1, float x2, float y2, unsigned int color,
                   int thickness, float alpha);

}  // namespace mytetris
