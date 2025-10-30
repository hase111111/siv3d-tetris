//! @file hold_tetromino.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "hold_renderer.h"

#include "game_const.h"
#include "my_assert.h"
#include "render_util.h"
#include "tetromino_render_util.h"

namespace mytetris {

HoldRenderer::HoldRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const HoldTetromino>& hold_tetromino_ptr)
    : block_textures_(GetBlockTextureMap(resource_container_ptr)),
      wall_texture_(resource_container_ptr->GetTexture("wall.png")),
      hold_tetromino_ptr_(hold_tetromino_ptr),
      font_view_(resource_container_ptr->GetFont("small")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(hold_tetromino_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(hold_tetromino_ptr_);
}

void HoldRenderer::Draw(const float render_x, const float render_y) const {
  const float wall_size{40.f * game_const::kResolutionEx};
  const float wall_ex{2.f * game_const::kResolutionEx};
  const float box_size{wall_size * 5.f};

  if (hold_tetromino_ptr_->IsHold()) {
    const auto hold_tetromino =
        hold_tetromino_ptr_->GetHoldTetromino().GetResetRotation();
    const float block_size = wall_size / 1.5f;
    DrawTetrominoCenter(hold_tetromino,
                        block_textures_.at(hold_tetromino.GetColor()),
                        render_x + box_size / 2.f,
                        render_y + wall_size + box_size / 2.f, 1.f, block_size);
  }

  // 文字.
  font_view_.Draw(render_x + wall_size * 3 / 4.0f,
                  render_y + wall_size * 3 / 4.0f, RenderAnchor::TopLeft,
                  "Hold", game_const::kResolutionEx);

  // フレーム.
  if (!hold_tetromino_ptr_->CanHold()) {
    DrawRectAlpha(render_x + wall_size / 2.f, render_y + wall_size * 1.5f,
                  render_x + wall_size * 4.5f, render_y + wall_size * 5.5f,
                  0xFF8080, true, 0.3f);
  }

  DrawRect(render_x + wall_size / 2.f, render_y + wall_size * 1.5f,
           render_x + wall_size * 4.5f, render_y + wall_size * 5.5f, 0xFFFFFF,
           false);

  for (int x = 0; x < box_size / wall_size; ++x) {
    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f, RenderAnchor::TopLeft,
                              wall_ex, 0.0f);

    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f + box_size + wall_size,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }

  for (int y = 0; y < box_size / wall_size + 2; ++y) {
    wall_texture_.DrawRotated(render_x - wall_size / 2.f,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
    wall_texture_.DrawRotated(render_x - wall_size / 2.f + box_size,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }
}

}  // namespace mytetris
