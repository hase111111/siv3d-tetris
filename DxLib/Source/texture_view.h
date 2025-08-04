
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

  inline int GetRawHandle() const { return handle_; }

  int GetWidth() const;

  int GetHeight() const;

  void Draw(float x, float y, RenderAnchor anchor) const;

  void DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                   float angle) const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

  const int handle_;
};

}  // namespace mytetris
