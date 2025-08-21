
//! @file tetromino_render_util.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetromino_render_util.h"

namespace mytetris {

std::map<TetrominoColor, TextureView> GetBlockTextureMap(
    const std::shared_ptr<const ResourceContainer> resource) {
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

void DrawTetromino(const Tetromino& tetromino, const TextureView& texture,
                   const float render_x, const float render_y,
                   const float alpha, const float block_size) {
  const auto shape = tetromino.GetShape();
  const auto tex_width = texture.GetWidth();
  const float ex = block_size / tex_width;
  for (int y = 0; y < shape.size(); ++y) {
    for (int x = 0; x < shape[0].size(); ++x) {
      if (!shape[y][x]) continue;
      const auto color = tetromino.GetColor();
      texture.DrawRotatedAlpha(render_x + x * block_size,
                               render_y + y * block_size, RenderAnchor::Center,
                               ex, 0.f, alpha);
    }
  }
}

}  // namespace mytetris
