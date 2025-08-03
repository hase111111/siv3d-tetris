
//! @file texture.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace mytetris {

enum class RenderAnchor : int {
  TopLeft,
  TopRight,
  BottomLeft,
  BottomRight,
  Center
};

class Texture final {
 public:
  Texture() = delete;
  Texture(const std::string &file_name);
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;
  Texture(Texture &&) = default;
  Texture &operator=(Texture &&) = default;
  ~Texture();

  inline int GetRawHandle() const { return handle_; }

  int GetWidth() const;

  int GetHeight() const;

  void Draw(float x, float y, RenderAnchor anchor) const;

  void DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                   float angle) const;

  [[nodiscard]]
  inline static int GetCount() {
    return count_;
  }

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

  const std::string file_name_;
  const int handle_;
  static int count_;
};

}  // namespace mytetris