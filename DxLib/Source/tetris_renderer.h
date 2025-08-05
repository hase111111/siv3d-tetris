
//! @file tetris_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <map>
#include <memory>

#include "resource_container.h"
#include "tetris_feild.h"
#include "tetromino.h"
#include "texture_view.h"

namespace mytetris {

class TetrisRenderer final {
 public:
  TetrisRenderer(
      const std::shared_ptr<const ResourceContainer> resource_container_ptr_);

  void Draw(const TetrisField& tetris_field, int render_x, int render_y,
            const Tetromino& tetromino, int tetromino_pos_x,
            int tetromino_pos_y) const;

 private:
  std::map<TetrominoColor, TextureView> InitializeBlockTextures(
      const std::shared_ptr<const ResourceContainer> resource_container_ptr_)
      const;

  void DrawTetromino(const Tetromino& tetromino, float render_x, float render_y,
                     int tetromino_pos_x, int tetromino_pos_y,
                     float alpha) const;

  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  const std::map<TetrominoColor, TextureView> block_textures_;
  const float block_size_{40.f};  // Size of each block in pixels
};

}  // namespace mytetris
