
//! @file tetris_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_renderer.h"

#include "my_assert.h"
#include "render_util.h"
#include "tetromino_render_util.h"

namespace mytetris {

TetrisRenderer::TetrisRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr,
    const std::shared_ptr<const Tetromino>& tetromino_ptr,
    const float block_size)
    : resource_container_ptr_(resource_container_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      block_size_(block_size),
      block_textures_(GetBlockTextureMap(resource_container_ptr)) {
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetromino_ptr_);
}

void TetrisRenderer::Draw(const int render_x, const int render_y,
                          const int tetromino_pos_x,
                          const int tetromino_pos_y) const {
  const float render_x_ =
      static_cast<float>(render_x) -
      block_size_ * (tetris_field_ptr_->GetWidth() / 2.f - 0.5f);
  const float render_y_ =
      static_cast<float>(render_y) -
      block_size_ * (tetris_field_ptr_->GetHeight() / 2.f - 0.5f);
  // shared_ptr では渡せない関数のために, コピーを作成.
  const Tetromino tetromino_copy = *tetromino_ptr_;

  // グリッドの描画.
  DrawGrid(render_x, render_y);

  // フィールドの描画.
  for (const auto& [x_, y_, tetromino] : *tetris_field_ptr_) {
    if (tetromino == TetrominoColor::kNone) {
      continue;
    }
    auto it = block_textures_.find(tetromino);
    if (it == block_textures_.end()) {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      continue;
    }

    it->second.DrawRotated(render_x_ + x_ * block_size_,
                           render_y_ + y_ * block_size_, RenderAnchor::Center,
                           2.f, 0.f);
  }

  // テトリミノの描画.
  DrawTetromino(tetromino_copy, block_textures_.at(tetromino_ptr_->GetColor()),
                render_x_ + tetromino_pos_x * block_size_,
                render_y_ + tetromino_pos_y * block_size_, 1.f, block_size_);

  const auto [hard_drop_x, hard_drop_y] =
      tetris_field_ptr_->GetHardDropPosition(tetromino_copy, tetromino_pos_x,
                                             tetromino_pos_y);

  // ハードドロップ位置の描画.
  if (hard_drop_x != tetromino_pos_x || hard_drop_y != tetromino_pos_y) {
    DrawTetromino(tetromino_copy,
                  block_textures_.at(tetromino_ptr_->GetColor()),
                  render_x_ + hard_drop_x * block_size_,
                  render_y_ + hard_drop_y * block_size_, 0.5f, block_size_);
  }
}

void TetrisRenderer::DrawGrid(const int render_x, const int render_y) const {
  const float render_x_ =
      static_cast<float>(render_x) -
      block_size_ * (tetris_field_ptr_->GetWidth() / 2.f - 0.5f);
  const float render_y_ =
      static_cast<float>(render_y) -
      block_size_ * (tetris_field_ptr_->GetHeight() / 2.f - 0.5f);
  const unsigned int grid_color = 0xFFFFFFFF;  // グリッドの色(暗めの灰色).
  const float alpha = 0.5f;                    // グリッド線の透明度.
  const int thickness = 1;                     // 線の太さ.

  // 横線の描画.
  for (int y = 0; y <= tetris_field_ptr_->GetHeight() - 2; ++y) {
    const float y_pos = render_y_ + y * block_size_ + block_size_ / 2.0f;
    DrawLineAlpha(
        render_x_ + block_size_ / 2.0f, y_pos,
        render_x_ + (tetris_field_ptr_->GetWidth() - 1.5f) * block_size_, y_pos,
        grid_color, thickness, alpha);
  }

  // 縦線の描画.
  for (int x = 0; x <= tetris_field_ptr_->GetWidth() - 2; ++x) {
    const float x_pos = render_x_ + x * block_size_ + block_size_ / 2.0f;
    DrawLineAlpha(
        x_pos, render_y_, x_pos,
        render_y_ + (tetris_field_ptr_->GetHeight() - 1.5f) * block_size_,
        grid_color, thickness, alpha);
  }
}

}  // namespace mytetris
