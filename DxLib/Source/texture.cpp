
//! @file texture.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "texture.h"

#include <DxLib.h>

#include <format>

#include "dxlib_assert.h"
#include "texture_view.h"

namespace mytetris {

int Texture::count_{0};

Texture::Texture(const std::string& file_name)
    : handle_(DxLib::LoadGraph(file_name.c_str())) {
  ASSERT(handle_ >= 0, std::format("Failed to load texture: {} (handle: {})",
                                   file_name, handle_));
  // 1フレーム間に大量のテクスチャのロードが発生することを防ぐため，
  // ロードした数をカウントする
  ++count_;
}

Texture::Texture(const int raw_handle) : handle_(raw_handle) {
  ASSERT(handle_ >= 0,
         std::format("Failed to load texture, handle: {}", handle_));
}

Texture::~Texture() { DxLib::DeleteGraph(handle_); }

int Texture::GetWidth() const {
  int width = 0, height = 0;
  if (DxLib::GetGraphSize(handle_, &width, &height) >= 0) {
    return width;
  }
  return 0;
}

int Texture::GetHeight() const {
  int width = 0, height = 0;
  if (DxLib::GetGraphSize(handle_, &width, &height) >= 0) {
    return height;
  }
  return 0;
}

void Texture::Draw(float x, float y, RenderAnchor anchor) const {
  DrawRotated(x, y, anchor, 1.0f, 0.0f);
}

void Texture::DrawRotated(float x, float y, RenderAnchor anchor, float ex,
                          float angle) const {
  const auto [render_x, render_y] = GetRenderPos(anchor);

  DxLib::DrawRotaGraphF(x + render_x * ex, y + render_y * ex, ex, angle,
                        GetRawHandle(), TRUE);
}

TextureView Texture::GetView() const { return TextureView{*this}; }

std::tuple<int, int> Texture::GetRenderPos(RenderAnchor anchor) const {
  const int width = GetWidth();
  const int height = GetHeight();
  switch (anchor) {
    case RenderAnchor::TopLeft: {
      return {width / 2, height / 2};
    }
    case RenderAnchor::TopRight: {
      return {-width / 2, height / 2};
    }
    case RenderAnchor::BottomLeft: {
      return {width / 2, -height / 2};
    }
    case RenderAnchor::BottomRight: {
      return {-width / 2, -height / 2};
    }
    case RenderAnchor::Center: {
      return {0, 0};
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      return {0, 0};
    }
  }
}

std::vector<std::unique_ptr<Texture>> LoadDivideGraph(
    const std::string path, const int x_num, const int y_num, const int all_num,
    const int x_size, const int y_size) {
  int* buffer = new int[all_num];

  DxLib::LoadDivGraph(path.c_str(), all_num, x_num, y_num, x_size, y_size,
                      buffer);

  std::vector<std::unique_ptr<Texture>> ret;

  for (int i = 0; i < all_num; ++i) {
    ret.push_back(std::move(std::make_unique<Texture>(buffer[i])));
  }

  return ret;
}

}  // namespace mytetris
