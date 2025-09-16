
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

#include "render_anchor.h"

namespace mytetris {

class FontView;

class Font final {
 public:
  Font() = delete;

#if defined DXLIB_COMPILE
  Font(const std::string &file_name);
  Font(int raw_handle);
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  Font(const std::string &file_name, int font_size);
#endif  // defined DXLIB_COMPILE

  Font(const Font &) = delete;
  Font &operator=(const Font &) = delete;
  Font(Font &&) = default;
  ~Font();

#if defined DXLIB_COMPILE
  inline int GetRawHandle() const { return handle_; }
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  inline const std::string &GetRawHandle() const { return handle_; }
#endif  // defined DXLIB_COMPILE

  void Draw(float x, float y, RenderAnchor anchor, std::string str) const;

  [[nodiscard]] inline static int GetCount() { return count_; }

  FontView GetView() const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor, int width,
                                    int height) const;

#if defined DXLIB_COMPILE
  const int handle_;
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  const std::string handle_;
#endif  // defined DXLIB_COMPILE

  const int font_size_;
  static int count_;
};

}  // namespace mytetris
