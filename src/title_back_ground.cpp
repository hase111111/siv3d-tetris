
//! @file title_back_ground.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_back_ground.h"

namespace mytetris {

TitleBackGround::TitleBackGround(
    int window_size_x, int window_size_y,
    const std::shared_ptr<const ResourceContainer>& container)
    : title_texture_(container->GetTexture("title.png")),
      wall_texture_(container->GetTexture("wall.png")),
      window_size_x_(window_size_x),
      window_size_y_(window_size_y) {}

void TitleBackGround::Draw() const {
  title_texture_.DrawRotated(window_size_x_ / 2.f, window_size_y_ * 4.f / 12.f,
                             RenderAnchor::Center, 2.0, 0.0);

  const int wall_num =
      (wall_texture_.GetHeight() != 0)
          ? (window_size_y_ /
             static_cast<int>(wall_texture_.GetHeight() * wall_ex_))
          : 0;

  for (int i = 0; i < wall_num; ++i) {
    const float i_ = static_cast<float>(i);
    wall_texture_.DrawRotated(0.f, i_ * wall_texture_.GetHeight() * wall_ex_,
                              RenderAnchor::TopLeft, wall_ex_, 0.f);
    wall_texture_.DrawRotated(static_cast<float>(window_size_x_),
                              i_ * wall_texture_.GetHeight() * wall_ex_,
                              RenderAnchor::TopRight, wall_ex_, 0.f);
  }
}

}  // namespace mytetris
