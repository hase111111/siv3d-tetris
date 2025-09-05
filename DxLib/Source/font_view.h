
//! @file font_view.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <tuple>

#include "font.h"

namespace mytetris {

class FontView final {
 public:
  FontView() = delete;
  FontView(const Font& font);
  FontView(const FontView&) = default;
  FontView(FontView&&) noexcept = default;

  bool IsValid() const;

  inline int GetRawHandle() const { return handle_; }

  void Draw(float x, float y, RenderAnchor anchor,
            const std::string& str) const;

  void DrawAlpha(float x, float y, RenderAnchor anchor, const std::string& str,
                 float alpha) const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor, int width,
                                    int height) const;

  const int handle_;
  const int font_size_;
};

}  // namespace mytetris
