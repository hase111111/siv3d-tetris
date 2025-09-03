
//! @file font.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "font.h"

#include <DxLib.h>

#include <format>

#include "font_view.h"
#include "my_assert.h"

namespace mytetris {

int Font::count_{0};

Font::Font(const std::string& file_name)
    : handle_(DxLib::LoadFontDataToHandle(file_name.c_str())) {
  ASSERT(handle_ >= 0, std::format("Failed to load font: {} (handle: {})",
                                   file_name, handle_));
  // 1フレーム間に大量のテクスチャのロードが発生することを防ぐため，
  // ロードした数をカウントする
  ++count_;
}

Font::Font(const int raw_handle) : handle_(raw_handle) {
  ASSERT(handle_ >= 0, std::format("Failed to load font, handle: {}", handle_));
}

Font::~Font() { DxLib::DeleteGraph(handle_); }

void Font::Draw(float x, float y, RenderAnchor anchor, std::string str) const {
  DrawFormatStringFToHandle(x, y, 0xFFFFFFFF, handle_, str.c_str());
}

FontView Font::GetView() const { return FontView{*this}; }

std::tuple<int, int> Font::GetRenderPos(RenderAnchor anchor) const {
  const int width = 0;
  const int height = 0;
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
