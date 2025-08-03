
//! @file texture.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "texture.h"

#include <DxLib.h>

#include "dxlib_assert.h"

namespace mytetris {

int Texture::count_{0};

Texture::Texture(const std::string& file_name)
    : file_name_(file_name), handle_(DxLib::LoadGraph(file_name.c_str())) {
  // 1フレーム間に大量のテクスチャのロードが発生することを防ぐため，
  // ロードした数をカウントする
  ++count_;
}

Texture::~Texture() {
  // テクスチャのハンドルが有効な場合は解放する
  DxLib::DeleteGraph(handle_);
}

bool Texture::IsValid() const { return handle_ >= 0; }

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
  if (!IsValid()) {
    return;
  }

  const auto [render_x, render_y] = GetRenderPos(anchor);

  DxLib::DrawRotaGraphF(x + render_x * ex, y + render_y * ex, ex, angle,
                        handle_, TRUE);
}

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

}  // namespace mytetris
