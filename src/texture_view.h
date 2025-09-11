
//! @file texture_view.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <tuple>

#include "texture.h"

namespace mytetris {

class TextureView final {
 public:
  TextureView() = delete;
  TextureView(const Texture& texture);
  TextureView(const TextureView&) = default;
  TextureView(TextureView&&) noexcept = default;

  bool IsValid() const;

#if defined DXLIB_COMPILE
  inline int GetRawHandle() const { return handle_; }
#elif defined SIV3D_COMPILE
  inline const std::string& GetRawHandle() const { return handle_; }
#endif  // defined DXLIB_COMPILE

  int GetWidth() const;

  int GetHeight() const;

  void Draw(float x, float y, RenderAnchor anchor) const;

  void DrawAlpha(float x, float y, RenderAnchor anchor, float alpha) const;

  void DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                   float angle) const;

  void DrawRotatedAlpha(float x, float y, RenderAnchor anchor, float ex,
                        float angle, float alpha) const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

#if defined DXLIB_COMPILE
  const int handle_;
#elif defined SIV3D_COMPILE
  const std::string handle_;
#endif  // defined DXLIB_COMPILE
};

}  // namespace mytetris
