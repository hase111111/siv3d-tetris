
//! @file next_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "next_renderer.h"

#include "render_util.h"
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

    if (next.size() - cnt + 1 > count_max_) {
      continue;
    }

    const int height = GetHeight(tetromino.GetShape());
    const float block_size = height > 4 ? block_size_ / 1.5f : block_size_;
    const float box_size = block_size_ * 5.0f;
    DrawTetrominoCenter(
        tetromino, block_textures_.at(tetromino.GetColor()),
        render_x + box_size / 2.f,
        render_y + (next.size() - cnt) * box_size + box_size / 2.f, 1.f,
        block_size);

    DrawRect(render_x, render_y + (next.size() - cnt) * box_size,
             render_x + box_size, render_y + (next.size() - cnt + 1) * box_size,
             0xFFFFFF, false);
  }
}

int NextRenderer::GetHeight(const std::vector<std::vector<bool>>& shape) const {
  const int height = static_cast<int>(shape[0].size());

  // 上から見て，空の行の数を数える.
  int empty_row_count = 0;
  for (int y = 0; y < height; ++y) {
    bool is_empty = true;
    for (int x = 0; x < shape.size(); ++x) {
      if (shape[x][y]) {
        is_empty = false;
        break;
      }
    }
    if (is_empty) {
      ++empty_row_count;
    } else {
      break;
    }
  }

  // 下から見て，空の行の数を数える.
  for (int y = height - 1; y >= 0; --y) {
    bool is_empty = true;
    for (int x = 0; x < shape.size(); ++x) {
      if (shape[x][y]) {
        is_empty = false;
        break;
      }
    }
    if (is_empty) {
      ++empty_row_count;
    } else {
      break;
    }
  }

  return height - empty_row_count;
}

}  // namespace mytetris
