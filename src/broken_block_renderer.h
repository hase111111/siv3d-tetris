
//! @file broken_block_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <vector>

#include "resource_container.h"
#include "tetromino_color.h"
#include "texture_view.h"

namespace mytetris {

class BrokenBlockRenderer final {
 public:
  BrokenBlockRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~BrokenBlockRenderer() = default;

  void SetBrokenBlocks(float x, float y, TetrominoColor color, bool left);

  void Update();

  void Draw(float offset_x, float offset_y) const;

 private:
  const std::map<TetrominoColor, TextureView> block_textures_;
  std::vector<std::tuple<float, float, float, float, float, TetrominoColor>>
      broken_blocks_;
};

}  // namespace mytetris
