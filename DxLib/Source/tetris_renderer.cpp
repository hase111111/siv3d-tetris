
//! @file tetris_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_renderer.h"

#include "dxlib_assert.h"

namespace mytetris {

TetrisRenderer::TetrisRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr,
    const std::shared_ptr<const Tetromino>& tetromino_ptr)
    : resource_container_ptr_(resource_container_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      block_textures_(InitializeBlockTextures(resource_container_ptr)) {}

void TetrisRenderer::Draw(const int render_x, const int render_y,
                          const int tetromino_pos_x,
                          const int tetromino_pos_y) const {
  const float render_x_ =
      static_cast<float>(render_x) -
      block_size_ * (tetris_field_ptr_->GetWidth() / 2.f - 0.5f);
  const float render_y_ =
      static_cast<float>(render_y) -
      block_size_ * (tetris_field_ptr_->GetHeight() / 2.f - 0.5f);

  // フィールドの描画.
  for (const auto& [x_, y_, tetromino] : *tetris_field_ptr_) {
    if (tetromino == TetrominoColor::kNone) {
      continue;
    }
    auto it = block_textures_.find(tetromino);
    if (it == block_textures_.end()) {
      ASSERT_MUST_NOT_REACH_HERE();
      continue;
    }
    const TextureView& texture = it->second;
    texture.DrawRotated(render_x_ + x_ * block_size_,
                        render_y_ + y_ * block_size_, RenderAnchor::Center, 2.f,
                        0.f);
  }

  // テトリミノの描画.
  DrawTetromino(*tetromino_ptr_, render_x_, render_y_, tetromino_pos_x,
                tetromino_pos_y, 1.f);

  const auto [hard_drop_x, hard_drop_y] =
      tetris_field_ptr_->GetHardDropPosition(*tetromino_ptr_, tetromino_pos_x,
                                             tetromino_pos_y);

  // ハードドロップ位置の描画.
  if (hard_drop_x != tetromino_pos_x || hard_drop_y != tetromino_pos_y) {
    DrawTetromino(*tetromino_ptr_, render_x_, render_y_, hard_drop_x,
                  hard_drop_y, 0.5f);
  }
}

std::map<TetrominoColor, TextureView> TetrisRenderer::InitializeBlockTextures(
    const std::shared_ptr<const ResourceContainer> resource) const {
  using enum TetrominoColor;
  std::map<TetrominoColor, TextureView> block_textures;
  block_textures.emplace(kZ, resource->GetTexture("block_0.png"));
  block_textures.emplace(kS, resource->GetTexture("block_1.png"));
  block_textures.emplace(kJ, resource->GetTexture("block_2.png"));
  block_textures.emplace(kL, resource->GetTexture("block_3.png"));
  block_textures.emplace(kI, resource->GetTexture("block_4.png"));
  block_textures.emplace(kO, resource->GetTexture("block_5.png"));
  block_textures.emplace(kT, resource->GetTexture("block_6.png"));
  block_textures.emplace(kJammer, resource->GetTexture("block_7.png"));
  block_textures.emplace(kWall, resource->GetTexture("wall.png"));
  return block_textures;
}

void TetrisRenderer::DrawTetromino(const Tetromino& tetromino,
                                   const float render_x, const float render_y,
                                   const int tetromino_pos_x,
                                   const int tetromino_pos_y,
                                   const float alpha) const {
  const auto shape = tetromino.GetShape();
  const float offset_x = tetromino_pos_x * block_size_;
  const float offset_y = tetromino_pos_y * block_size_;
  for (int y = 0; y < shape.size(); ++y) {
    for (int x = 0; x < shape[0].size(); ++x) {
      if (!shape[y][x]) continue;
      const auto color = tetromino.GetColor();
      const auto it = block_textures_.find(color);
      if (it == block_textures_.end()) {
        ASSERT_MUST_NOT_REACH_HERE();
        continue;
      }
      const TextureView& texture = it->second;
      texture.DrawRotatedAlpha(render_x + offset_x + x * block_size_,
                               render_y + offset_y + y * block_size_,
                               RenderAnchor::Center, 2.f, 0.f, alpha);
    }
  }
}

}  // namespace mytetris
