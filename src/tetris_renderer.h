//! @file tetris_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <map>
#include <memory>

#include "broken_block_renderer.h"
#include "font_view.h"
#include "i_tetris_field_effect.h"
#include "resource_container.h"
#include "tetris_feild.h"
#include "tetris_updater.h"
#include "tetromino.h"
#include "texture_view.h"

namespace mytetris {

class TetrisRenderer final {
 public:
  TetrisRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const TetrisField>& tetris_field_ptr,
      const std::shared_ptr<const Tetromino>& tetromino_ptr,
      const std::shared_ptr<const ITetrisFieldEffect>& tetris_field_effect_ptr,
      const std::shared_ptr<const TetrisUpdater>& tetris_updater_ptr,
      float block_size, bool ghost_tetromino_enabled);

  void Update();

  void Draw(float render_x, float render_y) const;

  inline int GetBlockSize() const { return static_cast<int>(block_size_); }

  float GetRenderWidth() const {
    return block_size_ * tetris_field_ptr_->GetWidth();
  }

  float GetRenderHeight() const {
    return block_size_ * tetris_field_ptr_->GetHeight();
  }

 private:
  void SetClearLines(
      const std::vector<std::tuple<int, std::vector<TetrominoColor>>>&
          clear_lines);

  void DrawGrid(float render_x, float render_y) const;

  void DrawPenaltyCount(float render_x, float render_y) const;

  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  const std::shared_ptr<const TetrisField> tetris_field_ptr_;
  const std::shared_ptr<const Tetromino> tetromino_ptr_;
  const std::shared_ptr<const ITetrisFieldEffect> tetris_field_effect_ptr_;
  const std::shared_ptr<const TetrisUpdater> tetris_updater_ptr_;
  const std::map<TetrominoColor, TextureView> block_textures_;
  const float block_size_;
  const FontView font_view_large_;
  const FontView font_view_;
  const FontView font_view_small_;
  const bool ghost_tetromino_enabled_;

  int counter_{0};
  BrokenBlockRenderer broken_block_renderer_;
};

}  // namespace mytetris
