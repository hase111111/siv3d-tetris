
//! @file description_field_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "description_field_renderer.h"

namespace mytetris {

DescriptionFieldRenderer::DescriptionFieldRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : font_view_(resource_container_ptr->GetFont("small")),
      wall_texture_(resource_container_ptr->GetTexture("wall.png")) {}

void DescriptionFieldRenderer::Draw(const int render_x,
                                    const int render_y) const {
  const float wall_size{40.f};
  const float wall_ex{2.f};
  const float box_size_x{wall_size * 10.f};
  const float box_size_y{wall_size * 23.f};

  // ÉtÉåÅ[ÉÄ.
  for (int x = 0; x < box_size_x / wall_size; ++x) {
    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f, RenderAnchor::TopLeft,
                              wall_ex, 0.0f);

    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f + box_size_y,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }

  for (int y = 0; y < box_size_y / wall_size + 1; ++y) {
    wall_texture_.DrawRotated(render_x - wall_size / 2.f,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
    wall_texture_.DrawRotated(render_x - wall_size / 2.f + box_size_x,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }

  // ï∂éö.
  font_view_.Draw(render_x + wall_size * 3 / 4.0f,
                  render_y + wall_size * 3 / 4.0f, RenderAnchor::TopLeft,
                  "Controls:");
  font_view_.Draw(render_x + wall_size, render_y + wall_size * 2.f,
                  RenderAnchor::TopLeft, GetString());
}

std::string DescriptionFieldRenderer::GetString() const {
  return std::string(
      "Move Left: Left Arrow\n"
      "Move Right: Right Arrow\n"
      "Soft Drop: Down Arrow\n"
      "Hard Drop: Up Arrow\n"
      "Rotate Clockwise: D\n"
      "Rotate Inverse: A\n"
      "Hold: W\n"
      "\n"
      "Back to Menu: Z\n"
      "Pause: P\n"
      "Reset: R\n"
      "End Game: Esc\n"
      "\n");
}

}  // namespace mytetris
