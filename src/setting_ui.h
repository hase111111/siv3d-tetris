#pragma once

#include <functional>
#include <memory>

#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class SettingUI final {
 public:
  SettingUI(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::function<void()>& scene_back_func);
  ~SettingUI() = default;

  void Update();

  void Draw() const;

 private:
  const std::function<void()>& scene_back_func_;
  const FontView font_view_40_;
  const FontView font_view_20_;
};

}  // namespace mytetris