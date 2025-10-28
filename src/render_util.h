//! @file render_util.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

//! @brief 矩形を描画する.
//! @param left 左上のx座標.
//! @param top 左上のy座標.
//! @param right 右下のx座標.
//! @param bottom 右下のy座標.
//! @param color 描画色 (16進数で，0xRRGGBB形式).
//! @param fill 塗りつぶす場合は true，枠線のみの場合は false.
void DrawRect(float left, float top, float right, float bottom,
              unsigned int color, bool fill);

//! @brief 矩形を描画する (アルファ値付き).
//! @param left 左上のx座標.
//! @param top 左上のy座標.
//! @param right 右下のx座標.
//! @param bottom 右下のy座標.
//! @param color 描画色 (16進数で，0xRRGGBB形式).
//! @param fill 塗りつぶす場合は true，枠線のみの場合は false.
//! @param alpha アルファ値 (0.0f 〜 1.0f).
void DrawRectAlpha(float left, float top, float right, float bottom,
                   unsigned int color, bool fill, float alpha);

void DrawLine(float x1, float y1, float x2, float y2, unsigned int color,
              float thickness);

void DrawLineAlpha(float x1, float y1, float x2, float y2, unsigned int color,
                   float thickness, float alpha);

}  // namespace mytetris
