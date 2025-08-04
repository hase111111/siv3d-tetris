
//! @file tetris_field_renderer.h
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
#include "texture_view.h"

namespace mytetris {

class TetrisFieldRenderer final {
 public:
  TetrisFieldRenderer(
      const std::shared_ptr<const ResourceContainer> resource_container_ptr_);

  void Draw(const TetrisField& tetris_field, int x, int y) const;

 private:
  std::map<Tetromino, TextureView> InitializeBlockTextures(
      const std::shared_ptr<const ResourceContainer> resource_container_ptr_)
      const;

  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  const std::map<Tetromino, TextureView> block_textures_;
};

}  // namespace mytetris
