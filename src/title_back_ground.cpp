//! @file title_back_ground.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_back_ground.h"

#include "game_const.h"
#include "my_assert.h"

namespace mytetris {

TitleBackGround::TitleBackGround(
    const std::shared_ptr<const ResourceContainer>& container)
    : title_texture_(container->GetTexture("title.png")),
      wall_texture_(container->GetTexture("wall.png")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(container);
}

void TitleBackGround::Draw() const {
  title_texture_.DrawRotated(
      game_const::kResolutionXF / 2.f, game_const::kResolutionYF / 3.f,
      RenderAnchor::Center, 2.0 * game_const::kResolutionEx, 0.0);

  const int wall_num =
      (wall_texture_.GetHeight() != 0)
          ? static_cast<int>(game_const::kResolutionYF /
                             wall_texture_.GetHeight() * wall_ex_ *
                             game_const::kResolutionEx)
          : 0;

  for (int i{0}; i < wall_num; ++i) {
    const float i_ = static_cast<float>(i);
    wall_texture_.DrawRotated(
        0.f,
        i_ * wall_texture_.GetHeight() * wall_ex_ * game_const::kResolutionEx,
        RenderAnchor::TopLeft, wall_ex_ * game_const::kResolutionEx, 0.f);
    wall_texture_.DrawRotated(
        static_cast<float>(game_const::kResolutionXF),
        i_ * wall_texture_.GetHeight() * wall_ex_ * game_const::kResolutionEx,
        RenderAnchor::TopRight, wall_ex_ * game_const::kResolutionEx, 0.f);
  }
}

}  // namespace mytetris
