//! @file tetris_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_renderer.h"

#include <cmath>

#include "game_const.h"
#include "my_assert.h"
#include "render_util.h"
#include "tetris_field_effect.h"
#include "tetromino_render_util.h"

namespace mytetris {

TetrisRenderer::TetrisRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr,
    const std::shared_ptr<const Tetromino>& tetromino_ptr,
    const std::shared_ptr<const ITetrisFieldEffect>& tetris_field_effect_ptr,
    const std::shared_ptr<const TetrisUpdater>& tetris_updater_ptr,
    const float block_size, bool ghost_tetromino_enabled)
    : resource_container_ptr_(resource_container_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetromino_ptr_(tetromino_ptr),
      tetris_field_effect_ptr_(tetris_field_effect_ptr),
      tetris_updater_ptr_(tetris_updater_ptr),
      block_size_(block_size),
      ghost_tetromino_enabled_(ghost_tetromino_enabled),
      block_textures_(GetBlockTextureMap(resource_container_ptr)),
      broken_block_renderer_(resource_container_ptr),
      font_view_(resource_container_ptr->GetFont("default")),
      font_view_small_(resource_container_ptr->GetFont("small")) {
  // 引数のチェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetromino_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_effect_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_updater_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_effect_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_updater_ptr_);
}

void TetrisRenderer::Update() {
  ++counter_;
  broken_block_renderer_.Update();

  const auto cleared_lines = tetris_updater_ptr_->GetClearedLines();
  SetClearLines(cleared_lines);
}

void TetrisRenderer::Draw(const float render_x, const float render_y) const {
  const float render_x_ =
      render_x - block_size_ * (tetris_field_ptr_->GetWidth() / 2.f - 0.5f);
  const float render_y_ =
      render_y - block_size_ * (tetris_field_ptr_->GetHeight() / 2.f - 0.5f);
  // shared_ptr では渡せない関数のために, コピーを作成.
  const Tetromino tetromino_copy = *tetromino_ptr_;

  // ピンチ時の描画.
  if (tetris_updater_ptr_->IsPinch() && !tetris_updater_ptr_->IsGameOver()) {
    const float x_size = block_size_ * (tetris_field_ptr_->GetWidth() - 2);
    const float y_size = block_size_ * (tetris_field_ptr_->GetHeight() - 2);
    DrawRectAlpha(render_x - x_size / 2.f, render_y_ - y_size / 2.f,
                  render_x + x_size / 2.f, render_y + y_size / 2.f, 0x00FF0000,
                  true, 0.3f * std::powf(std::sinf(counter_ / 15.f), 2.f));
  }

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

    const float ex = block_size_ / it->second.GetWidth();

    const auto [diff_x, diff_y] = tetris_field_effect_ptr_->GetDiff(x_, y_);
    it->second.DrawRotatedAlpha(render_x_ + x_ * block_size_ + diff_x,
                                render_y_ + y_ * block_size_ + diff_y,
                                RenderAnchor::Center,
                                ex * game_const::kResolutionEx, 0.f,
                                tetris_field_effect_ptr_->GetAlpha(x_, y_));
  }

  // テトリミノの描画.
  const auto [tetromino_pos_x, tetromino_pos_y] =
      tetris_updater_ptr_->GetPosition();
  DrawTetromino(tetromino_copy, block_textures_.at(tetromino_ptr_->GetColor()),
                render_x_ + tetromino_pos_x * block_size_,
                render_y_ + tetromino_pos_y * block_size_, 1.f, block_size_);

  const auto [hard_drop_x, hard_drop_y] =
      tetris_field_ptr_->GetHardDropPosition(tetromino_copy, tetromino_pos_x,
                                             tetromino_pos_y);

  // ハードドロップ位置の描画.
  if (ghost_tetromino_enabled_) {
    if (hard_drop_x != tetromino_pos_x || hard_drop_y != tetromino_pos_y) {
      DrawTetromino(tetromino_copy,
                    block_textures_.at(tetromino_ptr_->GetColor()),
                    render_x_ + hard_drop_x * block_size_,
                    render_y_ + hard_drop_y * block_size_, 0.5f, block_size_);
    }
  }

  // ゲームオーバー時の描画.
  if (tetris_updater_ptr_->IsGameOver()) {
    const float x_size = block_size_ * (tetris_field_ptr_->GetWidth() - 2);
    const float y_size = block_size_ * (tetris_field_ptr_->GetHeight() - 2);
    DrawRectAlpha(render_x - x_size / 2.f, render_y_ - y_size / 2.f,
                  render_x + x_size / 2.f, render_y + y_size / 2.f, 0x00000000,
                  true, 0.5f);

    const std::string game_over_text = "GAME OVER";
    font_view_.Draw(static_cast<float>(render_x),
                    render_y - 25.f * game_const::kResolutionEx,
                    RenderAnchor::Center, game_over_text,
                    game_const::kResolutionEx);

    const std::string retry_text = "Press R to Retry";
    font_view_small_.Draw(static_cast<float>(render_x),
                          render_y + 25.f * game_const::kResolutionEx,
                          RenderAnchor::Center, retry_text,
                          game_const::kResolutionEx);
  }

  // 消去ラインの描画.
  broken_block_renderer_.Draw(render_x_, render_y_);
}

void TetrisRenderer::SetClearLines(
    const std::vector<std::tuple<int, std::vector<TetrominoColor>>>&
        clear_lines) {
  // 消去ラインの描画.
  for (const auto& [line_y, colors] : clear_lines) {
    for (int x = 0; x < colors.size(); ++x) {
      broken_block_renderer_.SetBrokenBlocks(
          (x + 1) * block_size_, line_y * block_size_, colors.at(x), x < 6);
    }
  }
}

void TetrisRenderer::DrawGrid(const float render_x,
                              const float render_y) const {
  const float render_x_ =
      static_cast<float>(render_x) -
      block_size_ * (tetris_field_ptr_->GetWidth() / 2.f - 0.5f);
  const float render_y_ =
      static_cast<float>(render_y) -
      block_size_ * (tetris_field_ptr_->GetHeight() / 2.f - 0.5f);
  const unsigned int grid_color = 0xFFFFFFFF;   // グリッドの色(暗めの灰色).
  const unsigned int limit_color = 0xFFFF0000;  // フィールド外枠の色(青色).
  const float alpha = 0.5f;                     // グリッド線の透明度.
  const int thickness = 1;                      // 線の太さ.

  // 横線の描画.
  for (int y = 0; y <= tetris_field_ptr_->GetHeight() - 2; ++y) {
    const float y_pos = render_y_ + y * block_size_ + block_size_ / 2.0f;
    const unsigned int color = (y == 5) ? limit_color : grid_color;
    DrawLineAlpha(
        render_x_ + block_size_ / 2.0f, y_pos,
        render_x_ + (tetris_field_ptr_->GetWidth() - 1.5f) * block_size_, y_pos,
        color, thickness, alpha);
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
