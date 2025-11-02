#pragma once

#include <memory>

#include "font_view.h"
#include "penalty_updater.h"
#include "resource_container.h"
#include "texture_view.h"

namespace mytetris {

class PenaltyRenderer final {
 public:
  PenaltyRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const PenaltyUpdater>& penalty_updater_ptr,
      const float wall_size);
  ~PenaltyRenderer() = default;

  void Draw(float render_x, float render_y) const;

 private:
  const TextureView wall_texture_;
  const FontView font_view_;
  const FontView font_view_large_;
  const std::shared_ptr<const PenaltyUpdater> penalty_updater_ptr_;
  const float wall_size_{};
};

}  // namespace mytetris
