//! @file title_back_ground.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class TitleBackGround final {
 public:
  TitleBackGround(
      int window_size_x, int window_size_y,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~TitleBackGround() = default;

  void Draw() const;

 private:
  const TextureView title_texture_;
  const TextureView wall_texture_;
  const int window_size_x_;
  const int window_size_y_;
  const float wall_ex_{2.0f};
};

}  // namespace mytetris
