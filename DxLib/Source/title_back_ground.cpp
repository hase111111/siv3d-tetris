
//! @file title_back_ground.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_back_ground.h"

#include "dxlib_assert.h"

namespace mytetris {

TitleBackGround::TitleBackGround(int window_size_x, int window_size_y)
    : title_texture_("dat/img/title.png"),
      window_size_x_(window_size_x),
      window_size_y_(window_size_y) {
  ASSERT(title_texture_.IsValid(), "Failed to load title texture.");
}

void TitleBackGround::Draw() const {
  title_texture_.DrawRotated(window_size_x_ / 2.f, window_size_y_ * 5.f / 12.f,
                             RenderAnchor::Center, 2.0, 0.0);
}

}  // namespace mytetris
