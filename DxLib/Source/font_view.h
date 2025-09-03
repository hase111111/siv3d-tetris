
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

  void Draw(float x, float y, RenderAnchor anchor, std::string str) const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

  const int handle_;
};

}  // namespace mytetris
