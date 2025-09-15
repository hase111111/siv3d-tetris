
//! @file font_view.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "font_view.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

#include "my_assert.h"
#include "my_format.h"

namespace mytetris {

#if defined DXLIB_COMPILE

FontView::FontView(const Font& font)
    : handle_(font.GetRawHandle()), font_size_(GetFontSizeToHandle(handle_)) {}

bool FontView::IsValid() const { return handle_ >= 0; }

void FontView::Draw(const float x, const float y, const RenderAnchor anchor,
                    const std::string& str) const {
  const int width = GetDrawStringWidthToHandle(
      str.c_str(), static_cast<int>(str.size()), handle_);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  DrawFormatStringFToHandle(x + dx, y + dy, 0xFFFFFFFF, handle_, str.c_str());
}

void FontView::DrawAlpha(const float x, const float y,
                         const RenderAnchor anchor, const std::string& str,
                         const float alpha) const {
  const int width = GetDrawStringWidthToHandle(
      str.c_str(), static_cast<int>(str.size()), handle_);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 255));
  DrawFormatStringFToHandle(x + dx, y + dy, 0xFFFFFFFF, handle_, str.c_str());
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

FontView::FontView(const Font& font, const int font_size)
    : handle_(font.GetRawHandle()), font_size_(font_size) {}

bool FontView::IsValid() const { return true; }

void FontView::Draw(const float x, const float y, const RenderAnchor anchor,
                    const std::string& str) const {
  const s3d::String path{handle_.begin(), handle_.end()};
  const std::string key_str = format("{}_{}", handle_, font_size_);
  const s3d::String key{key_str.begin(), key_str.end()};
  s3d::String s{str.begin(), str.end()};
  const int width = static_cast<int>(s3d::FontAsset(key)(s).region().w);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  s3d::FontAsset(key)(s).draw(s3d::Vec2(x + dx, y + dy), s3d::Palette::White);
}

void FontView::DrawAlpha(const float x, const float y,
                         const RenderAnchor anchor, const std::string& str,
                         const float alpha) const {
  const s3d::String path{handle_.begin(), handle_.end()};
  const std::string key_str = format("{}_{}", handle_, font_size_);
  const s3d::String key{key_str.begin(), key_str.end()};
  s3d::String s{str.begin(), str.end()};
  const int width = static_cast<int>(s3d::FontAsset(key)(s).region().w);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  s3d::FontAsset(key)(s).draw(s3d::Vec2(x + dx, y + dy),
                              s3d::ColorF{1.0, static_cast<double>(alpha)});
}

#endif  // defined DXLIB_COMPILE

std::tuple<int, int> FontView::GetRenderPos(RenderAnchor anchor, int width,
                                            int height) const {
  switch (anchor) {
    case RenderAnchor::TopLeft: {
      return {0, 0};
    }
    case RenderAnchor::TopRight: {
      return {-width, 0};
    }
    case RenderAnchor::BottomLeft: {
      return {0, -height};
    }
    case RenderAnchor::BottomRight: {
      return {-width, -height};
    }
    case RenderAnchor::Center: {
      return {-width / 2, -height / 2};
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return {0, 0};
    }
  }
}

}  // namespace mytetris
