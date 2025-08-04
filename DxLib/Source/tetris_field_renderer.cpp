
//! @file tetris_field_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_field_renderer.h"

namespace mytetris {

TetrisFieldRenderer::TetrisFieldRenderer(
    const std::shared_ptr<const ResourceContainer> resource_container_ptr)
    : resource_container_ptr_(resource_container_ptr),
      block_textures_(InitializeBlockTextures(resource_container_ptr)) {}

void TetrisFieldRenderer::Draw(const TetrisField& tetris_field, const int x,
                               const int y) const {
  const float block_size = 40.f;
  for (const auto& [x_, y_, tetromino] : tetris_field) {
    if (tetromino == Tetromino::kNone) {
      continue;
    }
    auto it = block_textures_.find(tetromino);
    if (it == block_textures_.end()) {
      continue;  // Skip if the tetromino texture is not found
    }
    const TextureView& texture = it->second;
    texture.DrawRotated(x + x_ * block_size, y + y_ * block_size,
                        RenderAnchor::Center, 2.f, 0.f);
  }
}

std::map<Tetromino, TextureView> TetrisFieldRenderer::InitializeBlockTextures(
    const std::shared_ptr<const ResourceContainer> resource) const {
  using enum Tetromino;
  std::map<Tetromino, TextureView> block_textures;
  block_textures.emplace(kZ, resource->GetTexture("block_0.png"));
  block_textures.emplace(kS, resource->GetTexture("block_1.png"));
  block_textures.emplace(kL, resource->GetTexture("block_2.png"));
  block_textures.emplace(kJ, resource->GetTexture("block_3.png"));
  block_textures.emplace(kI, resource->GetTexture("block_4.png"));
  block_textures.emplace(kO, resource->GetTexture("block_5.png"));
  block_textures.emplace(kT, resource->GetTexture("block_6.png"));
  block_textures.emplace(kJammer, resource->GetTexture("block_7.png"));
  block_textures.emplace(kWall, resource->GetTexture("wall.png"));
  return block_textures;
}

}  // namespace mytetris
