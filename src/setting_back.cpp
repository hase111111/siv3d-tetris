//! @file setting_back.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "setting_back.h"

#include "game_const.h"
#include "my_assert.h"

namespace mytetris {

SettingBack::SettingBack(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : wall_texture_(resource_container_ptr->GetTexture("wall.png")),
      font_view_40_(resource_container_ptr->GetFont("default")) {
  // nullptr É`ÉFÉbÉN.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
}

void SettingBack::Draw() const {
  // âÊñ ÇògÇ«ÇÈÇÊÇ§Ç…ï`âÊ.
  const float wall_ex{2.f};
  const float wall_size{40.f};

  const int screen_width = game_const::kResolutionX;
  const int screen_height = game_const::kResolutionY;

  // è„â∫ÇÃòg.
  for (int x = 0; x < screen_width / wall_size + 1; ++x) {
    wall_texture_.DrawRotated(wall_size * x, 0, RenderAnchor::TopLeft, wall_ex,
                              0.0f);
    wall_texture_.DrawRotated(wall_size * x - wall_size,
                              -wall_size + screen_height, RenderAnchor::TopLeft,
                              wall_ex, 0.0f);
  }

  // ç∂âEÇÃòg.
  for (int y = 0; y < screen_height / wall_size + 1; ++y) {
    wall_texture_.DrawRotated(0, wall_size * y, RenderAnchor::TopLeft, wall_ex,
                              0.0f);
    wall_texture_.DrawRotated(-wall_size + screen_width,
                              wall_size * y - wall_size, RenderAnchor::TopLeft,
                              wall_ex, 0.0f);
  }

  // ç∂è„Ç…"Setting"ÇÃï∂éöÇï`âÊ.
  font_view_40_.Draw(60.f, 60.f, RenderAnchor::TopLeft, "Setting",
                     game_const::kResolutionEx);
}

}  // namespace mytetris
