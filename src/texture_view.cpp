
//! @file texture_view.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "texture_view.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

#include "my_assert.h"

namespace mytetris {

TextureView::TextureView(const Texture& texture)
    : handle_(texture.GetRawHandle()) {}

bool TextureView::IsValid() const {
#if defined DXLIB_COMPILE
  return handle_ >= 0;
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  return true;
#endif  // defined DXLIB_COMPILE
}

#if defined DXLIB_COMPILE
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

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

int TextureView::GetWidth() const {
  s3d::String path{handle_.begin(), handle_.end()};
  return s3d::TextureAsset(path).width();
}

int TextureView::GetHeight() const {
  s3d::String path{handle_.begin(), handle_.end()};
  return s3d::TextureAsset(path).height();
}

#endif  // defined DXLIB_COMPILE

void TextureView::Draw(float x, float y, RenderAnchor anchor) const {
  DrawRotated(x, y, anchor, 1.0f, 0.0f);
}

void TextureView::DrawAlpha(float x, float y, RenderAnchor anchor,
                            float alpha) const {
#if defined DXLIB_COMPILE
  const int alpha_ = static_cast<int>(alpha * 255);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
  Draw(x, y, anchor);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  const s3d::String path{handle_.begin(), handle_.end()};
  const auto [render_x, render_y] = GetRenderPos(anchor);

  s3d::TextureAsset(path).drawAt(s3d::Vec2(x + render_x, y + render_y),
                                 ColorF{1.0, static_cast<double>(alpha)});
#endif  // defined DXLIB_COMPILE
}

void TextureView::DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                              float angle) const {
  if (!IsValid()) {
    return;
  }
  const auto [render_x, render_y] = GetRenderPos(anchor);

#if defined DXLIB_COMPILE
  DxLib::DrawRotaGraphF(x + render_x * ex, y + render_y * ex, ex, angle,
                        handle_, TRUE);
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  s3d::String path{handle_.begin(), handle_.end()};
  s3d::TextureAsset(path)
      .resized(GetWidth() * ex, GetHeight() * ex)
      .rotated(s3d::Math::ToRadians(angle))
      .drawAt(s3d::Vec2(x + render_x * ex, y + render_y * ex));
#endif  // defined DXLIB_COMPILE
}

void TextureView::DrawRotatedAlpha(float x, float y, RenderAnchor anchor,
                                   float ex, float angle, float alpha) const {
#if defined DXLIB_COMPILE
  const int alpha_ = static_cast<int>(alpha * 255);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
  DrawRotated(x, y, anchor, ex, angle);
  DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  const s3d::String path{handle_.begin(), handle_.end()};
  const auto [render_x, render_y] = GetRenderPos(anchor);

  s3d::TextureAsset(path)
      .resized(GetWidth() * ex, GetHeight() * ex)
      .rotated(s3d::Math::ToRadians(angle))
      .drawAt(s3d::Vec2(x + render_x * ex, y + render_y * ex),
              ColorF{1.0, static_cast<double>(alpha)});
#endif
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
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return {0, 0};
    }
  }
}
}  // namespace mytetris
