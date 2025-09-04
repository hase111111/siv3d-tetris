
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
  Texture(int raw_handle);
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

  [[nodiscard]] inline static int GetCount() { return count_; }

  TextureView GetView() const;

 private:
  std::tuple<int, int> GetRenderPos(RenderAnchor anchor) const;

  const int handle_;
  static int count_;
};

std::vector<std::unique_ptr<Texture>> LoadDivideGraph(const std::string path,
                                                      int x_num, int y_num,
                                                      int all_num, int x_size,
                                                      int y_size);

}  // namespace mytetris