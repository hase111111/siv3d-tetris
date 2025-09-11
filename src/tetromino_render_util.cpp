
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
  block_textures.emplace(kOther1, resource->GetTexture("block_8.png"));
  block_textures.emplace(kOther2, resource->GetTexture("block_9.png"));
  block_textures.emplace(kOther3, resource->GetTexture("block_10.png"));
  block_textures.emplace(kOther4, resource->GetTexture("block_11.png"));
  block_textures.emplace(kOther5, resource->GetTexture("block_12.png"));
  block_textures.emplace(kOther6, resource->GetTexture("block_13.png"));
  block_textures.emplace(kOther7, resource->GetTexture("block_14.png"));
  block_textures.emplace(kOther8, resource->GetTexture("block_15.png"));
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
      texture.DrawRotatedAlpha(render_x + x * block_size,
                               render_y + y * block_size, RenderAnchor::Center,
                               ex, 0.f, alpha);
    }
  }
}

void DrawTetrominoCenter(const Tetromino& tetromino, const TextureView& texture,
                         float render_x, float render_y, float alpha,
                         float block_size) {
  const auto shape = tetromino.GetShape();
  const int height = static_cast<int>(shape.size());
  const int width = static_cast<int>(shape[0].size());
  render_x -= (width * block_size) / 2.f - block_size / 2.f;
  render_y -= (height * block_size) / 2.f - block_size / 2.f;
  const auto tex_width = texture.GetWidth();
  const float ex = block_size / tex_width;
  for (int y = 0; y < shape.size(); ++y) {
    for (int x = 0; x < shape[0].size(); ++x) {
      if (!shape[y][x]) continue;
      texture.DrawRotatedAlpha(render_x + x * block_size,
                               render_y + y * block_size, RenderAnchor::Center,
                               ex, 0.f, alpha);
    }
  }
}

}  // namespace mytetris
