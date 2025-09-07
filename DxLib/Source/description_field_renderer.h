
//! @file description_field_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>

#include "font_view.h"
#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class DescriptionFieldRenderer final {
 public:
  DescriptionFieldRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~DescriptionFieldRenderer() = default;

  void Draw(int x, int y) const;

 private:
  std::string GetString() const;

  const FontView font_view_;
  const TextureView wall_texture_;
};

}  // namespace mytetris
