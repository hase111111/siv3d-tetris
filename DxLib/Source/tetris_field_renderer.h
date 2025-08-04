
//! @file tetris_field_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <memory>

#include "resource_container.h"
#include "tetris_feild.h"

namespace mytetris {

class TetrisFieldRenderer final {
 public:
  TetrisFieldRenderer(
      const std::shared_ptr<const ResourceContainer> resource_container_ptr_);

 private:
  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
};

}  // namespace mytetris
