
//! @file next_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <vector>

#include "next_tetromino.h"
#include "resource_container.h"

namespace mytetris {

class NextRenderer final {
 public:
  NextRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const NextTetromino>& next_tetromino_ptr);
  ~NextRenderer() = default;

  void Draw(float render_x, float render_y) const;

 private:
  int GetHeight(const std::vector<std::vector<bool>>& shape) const;

  const std::map<TetrominoColor, TextureView> block_textures_;
  const TextureView wall_texture_;
  const std::shared_ptr<const NextTetromino> next_tetromino_ptr_;
  const float block_size_{30.0f};
  const int count_max_{5};
};

}  // namespace mytetris
