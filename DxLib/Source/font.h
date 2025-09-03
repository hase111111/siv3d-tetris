
//! @file font.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace mytetris {

class FontView;

enum class RenderAnchor : int {
  TopLeft,
  TopRight,
  BottomLeft,
  BottomRight,
  Center
};

class Font final {
 public:
  Font() = delete;
  Font(const std::string &file_name);
  Font(int raw_handle);
  Font(const Font &) = delete;
  Font &operator=(const Font &) = delete;
  Font(Font &&) = default;
  Font &operator=(Font &&) = default;
  ~Font();

  inline int GetRawHandle() const { return handle_; }

  void Draw(float x, float y, RenderAnchor anchor, std::string str) const;

  [[nodiscard]] inline static int GetCount() { return count_; }

  FontView GetView() const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

  const int handle_;
  static int count_;
};

}  // namespace mytetris
