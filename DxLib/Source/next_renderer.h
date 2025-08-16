
//! @file next_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "next_renderer.h"
#include "resource_container.h"

namespace mytetris {

class NextRenderer final {
 public:
  NextRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~NextRenderer() = default;

  void Draw(int render_x, int render_y) const;

 private:
  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
};

}  // namespace mytetris