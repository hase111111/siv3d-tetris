
//! @file font.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "font.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined DXLIB_COMPILE

#include "font_view.h"
#include "my_assert.h"
#include "my_format.h"

namespace mytetris {

int Font::count_{0};

#if defined DXLIB_COMPILE

Font::Font(const std::string& file_name)
    : handle_(DxLib::LoadFontDataToHandle(file_name.c_str(), 1)),
      font_size_(GetFontSizeToHandle(handle_)) {
  ASSERT(handle_ >= 0, std::format("Failed to load font: {} (handle: {})",
                                   file_name, handle_));
  // 1フレーム間に大量のテクスチャのロードが発生することを防ぐため，
  // ロードした数をカウントする
  ++count_;
}

Font::Font(const int raw_handle)
    : handle_(raw_handle), font_size_(GetFontSizeToHandle(handle_)) {
  ASSERT(handle_ >= 0, std::format("Failed to load font, handle: {}", handle_));
}

Font::~Font() { DxLib::DeleteGraph(handle_); }

void Font::Draw(float x, float y, RenderAnchor anchor, std::string str) const {
  const int width = GetDrawStringWidthToHandle(
      str.c_str(), static_cast<int>(str.size()), handle_);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  DrawFormatStringFToHandle(x + dx, y + dy, 0xFFFFFFFF, handle_, str.c_str());
}

FontView Font::GetView() const { return FontView{*this}; }

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

Font::Font(const std::string& file_name, const int font_size)
    : handle_(file_name.c_str()), font_size_(font_size) {
  const s3d::String path{file_name.begin(), file_name.end()};
  const std::string key_str = format("{}_{}", file_name, font_size);
  const s3d::String key{key_str.begin(), key_str.end()};
  s3d::FontAsset::Register(key, FontMethod::MSDF, font_size, path);
}

Font::~Font() {
  s3d::String path{handle_.begin(), handle_.end()};
  s3d::FontAsset::Unregister(path);
}

void Font::Draw(float x, float y, RenderAnchor anchor, std::string str) const {
  const s3d::String path{handle_.begin(), handle_.end()};
  const std::string key_str = format("{}_{}", handle_, font_size_);
  const s3d::String key{key_str.begin(), key_str.end()};
  const s3d::String s{str.begin(), str.end()};
  const int width = static_cast<int>(s3d::FontAsset(key)(s).region().w);
  const auto [dx, dy] = GetRenderPos(anchor, width, font_size_);
  s3d::FontAsset(key)(s).draw(s3d::Vec2(x + dx, y + dy), s3d::Palette::White);
}

FontView Font::GetView() const { return FontView{*this, font_size_}; }

#endif  // defined DXLIB_COMPILE

std::tuple<int, int> Font::GetRenderPos(RenderAnchor anchor, int width,
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
