
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

#if defined DXLIB_COMPILE
  FontView(const Font& font);
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  FontView(const Font& font, int font_size);
#endif  // defined DXLIB_COMPILE

  FontView(const FontView&) = default;
  FontView(FontView&&) noexcept = default;

  bool IsValid() const;

#if defined DXLIB_COMPILE
  inline int GetRawHandle() const { return handle_; }
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  inline const std::string& GetRawHandle() const { return handle_; }
#endif  // defined DXLIB_COMPILE

  void Draw(float x, float y, RenderAnchor anchor,
            const std::string& str) const;

  void DrawAlpha(float x, float y, RenderAnchor anchor, const std::string& str,
                 float alpha) const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor, int width,
                                    int height) const;

#if defined DXLIB_COMPILE
  const int handle_;
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  const std::string handle_;
#endif  // defined DXLIB_COMPILE

  const int font_size_;
};

}  // namespace mytetris
