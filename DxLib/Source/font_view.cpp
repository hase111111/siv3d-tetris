
//! @file font_view.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "font_view.h"

#include <DxLib.h>

#include "my_assert.h"

namespace mytetris {

FontView::FontView(const Font& font) : handle_(font.GetRawHandle()) {}

bool FontView::IsValid() const { return handle_ >= 0; }

void FontView::Draw(float x, float y, RenderAnchor anchor,
                    std::string str) const {
  DrawFormatStringFToHandle(x, y, 0xFFFFFFFF, handle_, str.c_str());
}

std::tuple<int, int> FontView::GetRenderPos(RenderAnchor anchor) const {
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
