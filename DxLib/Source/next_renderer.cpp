
#include "next_renderer.h"

namespace mytetris {

NextRenderer::NextRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const NextTetromino>& next_tetromino_ptr)
    : resource_container_ptr_(resource_container_ptr),
      next_tetromino_ptr_(next_tetromino_ptr) {}

void NextRenderer::Draw(const int render_x, const int render_y) const {
  const auto next = next_tetromino_ptr_->GetNextList();
}

}  // namespace mytetris
