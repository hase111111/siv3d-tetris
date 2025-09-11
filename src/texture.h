
//! @file texture.h
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

class TextureView;

class Texture final {
 public:
  Texture() = delete;
  Texture(const std::string &file_name);

#if defined DXLIB_COMPILE
  Texture(int raw_handle);
#endif  // defined DXLIB_COMPILE

  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;
  Texture(Texture &&) = default;
  Texture &operator=(Texture &&) = default;
  ~Texture();

  //! @todo friend ä÷êîÇ…Ç∑Ç◊Ç´
#if defined DXLIB_COMPILE
  inline int GetRawHandle() const { return handle_; }
#elif defined SIV3D_COMPILE
  inline const std::string &GetRawHandle() const { return handle_; }
#endif  // defined DXLIB_COMPILE

  int GetWidth() const;

  int GetHeight() const;

  void Draw(float x, float y, RenderAnchor anchor) const;

  void DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                   float angle) const;

  [[nodiscard]] inline static int GetCount() { return count_; }

  TextureView GetView() const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

#if defined DXLIB_COMPILE
  const int handle_;
#elif defined SIV3D_COMPILE
  const std::string handle_;
#endif  // defined DXLIB_COMPILE

  static int count_;
};

#if defined DXLIB_COMPILE
std::vector<std::unique_ptr<Texture>> LoadDivideGraph(const std::string path,
                                                      int x_num, int y_num,
                                                      int all_num, int x_size,
                                                      int y_size);
#endif

}  // namespace mytetris
