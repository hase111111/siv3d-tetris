
//! @file next_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "next_renderer.h"

#include "tetromino_render_util.h"

namespace mytetris {

NextRenderer::NextRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const NextTetromino>& next_tetromino_ptr)
    : block_textures_(GetBlockTextureMap(resource_container_ptr)),
      next_tetromino_ptr_(next_tetromino_ptr) {}

void NextRenderer::Draw(const float render_x, const float render_y) const {
  int cnt{};
  const auto next = next_tetromino_ptr_->GetNextList();
  for (const auto& tetromino : next) {
    ++cnt;
    DrawTetromino(tetromino, block_textures_.at(tetromino.GetColor()), render_x,
                  render_y + (next.size() - cnt) * block_size_ * 4, 1.f,
                  block_size_);
  }
}

}  // namespace mytetris
