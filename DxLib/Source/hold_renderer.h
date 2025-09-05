
//! @file hold_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "font_view.h"
#include "hold_tetromino.h"
#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class HoldRenderer final {
 public:
  HoldRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const HoldTetromino>& hold_tetromino_ptr);

  void Draw(float x, float y) const;

 private:
  const std::shared_ptr<const HoldTetromino> hold_tetromino_ptr_;
  const std::map<TetrominoColor, TextureView> block_textures_;
  const TextureView wall_texture_;
  const FontView font_view_;
};

}  // namespace mytetris
