
#include "next_renderer.h"

namespace mytetris {

NextRenderer::NextRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const NextTetromino>& next_tetromino_ptr)
    : resource_container_ptr_(resource_container_ptr),
      next_tetromino_ptr_(next_tetromino_ptr) {}

void NextRenderer::Draw(int render_x, int render_y) const {}

}  // namespace mytetris
