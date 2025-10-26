#pragma once

#include <memory>

#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class SettingBack final {
 public:
  SettingBack(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~SettingBack() = default;

  void Draw() const;

 private:
  const TextureView wall_texture_;
  const FontView font_view_40_;
};

}  // namespace mytetris