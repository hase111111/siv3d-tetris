
//! @file texture_view.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "texture_view.h"

#include <DxLib.h>

#include "dxlib_assert.h"

namespace mytetris {

TextureView::TextureView(const Texture& texture)
    : handle_(texture.GetRawHandle()) {}

bool TextureView::IsValid() const { return handle_ >= 0; }

int TextureView::GetWidth() const {
  int width = 0, height = 0;
  if (DxLib::GetGraphSize(handle_, &width, &height) >= 0) {
    return width;
  }
  return 0;
}

int TextureView::GetHeight() const {
  int width = 0, height = 0;
  if (DxLib::GetGraphSize(handle_, &width, &height) >= 0) {
    return height;
  }
  return 0;
}

void TextureView::Draw(float x, float y, RenderAnchor anchor) const {
  DrawRotated(x, y, anchor, 1.0f, 0.0f);
}

void TextureView::DrawAlpha(float x, float y, RenderAnchor anchor,
                            float alpha) const {
  const int alpha_ = static_cast<int>(alpha * 255);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
  Draw(x, y, anchor);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TextureView::DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                              float angle) const {
  if (!IsValid()) {
    return;
  }
  const auto [render_x, render_y] = GetRenderPos(anchor);

  DxLib::DrawRotaGraphF(x + render_x * ex, y + render_y * ex, ex, angle,
                        handle_, TRUE);
}

void TextureView::DrawRotatedAlpha(float x, float y, RenderAnchor anchor,
                                   float ex, float angle, float alpha) const {
  const int alpha_ = static_cast<int>(alpha * 255);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
  DrawRotated(x, y, anchor, ex, angle);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

std::tuple<int, int> TextureView::GetRenderPos(RenderAnchor anchor) const {
  const int width = GetWidth();
  const int height = GetHeight();
  switch (anchor) {
    case RenderAnchor::TopLeft: {
      return {width / 2, height / 2};
    }
    case RenderAnchor::TopRight: {
      return {-width / 2, height / 2};
    }
    case RenderAnchor::BottomLeft: {
      return {width / 2, -height / 2};
    }
    case RenderAnchor::BottomRight: {
      return {-width / 2, -height / 2};
    }
    case RenderAnchor::Center: {
      return {0, 0};
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      return {0, 0};
    }
  }
}
}  // namespace mytetris
