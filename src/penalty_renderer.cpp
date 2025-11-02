#include "penalty_renderer.h"

#include "game_const.h"
#include "my_assert.h"
#include "render_util.h"

namespace mytetris {

PenaltyRenderer::PenaltyRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const PenaltyUpdater>& penalty_updater_ptr,
    const float wall_size)
    : wall_texture_(resource_container_ptr->GetTexture("wall.png")),
      font_view_(resource_container_ptr->GetFont("small")),
      font_view_large_(resource_container_ptr->GetFont("large")),
      penalty_updater_ptr_(penalty_updater_ptr),
      wall_size_(wall_size) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(penalty_updater_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(penalty_updater_ptr_);
}

void PenaltyRenderer::Draw(const float render_x, const float render_y) const {
  const int wall_x_num = 12;
  const int wall_y_num = 5;
  const float wall_ex = wall_size_ / wall_texture_.GetHeight();

  if (const auto penalty_counter = penalty_updater_ptr_->GetCounter();
      penalty_counter != 0) {
    const float alpha =
        0.5f * penalty_counter /
        static_cast<float>(penalty_updater_ptr_->GetPenaltyInterval());
    DrawRectAlpha(render_x, render_y, render_x + wall_size_ * (wall_x_num + 1),
                  render_y + wall_size_ * (wall_y_num + 1), 0xFFFF00, true,
                  alpha);
  }

  // ペナルティライン数表示.
  const int penalty_lines = penalty_updater_ptr_->GetPenaltyLines();
  font_view_.Draw(render_x + wall_size_ * wall_x_num / 2.f,
                  render_y + wall_size_ / 2.f, RenderAnchor::Center,
                  "Penalty Lines", game_const::kResolutionEx);

  if (penalty_lines < 0) {
    font_view_large_.Draw(
        render_x + wall_size_ * wall_x_num / 4.f,
        render_y + wall_size_ * wall_y_num / 2.f, RenderAnchor::Center,
        std::to_string(penalty_lines * -1), game_const::kResolutionEx);
  } else if (0 < penalty_lines) {
    font_view_large_.Draw(render_x + wall_size_ * wall_x_num * 3.f / 4.f,
                          render_y + wall_size_ * wall_y_num / 2.f,
                          RenderAnchor::Center, std::to_string(penalty_lines),
                          game_const::kResolutionEx);
  }

  // フレーム.
  for (int x = 0; x < wall_x_num + 2; ++x) {
    wall_texture_.DrawRotated(render_x + wall_size_ * x - wall_size_ / 2.f,
                              render_y - wall_size_ / 2.f, RenderAnchor::Center,
                              wall_ex, 0.0f);

    wall_texture_.DrawRotated(
        render_x + wall_size_ * x - wall_size_ / 2.f,
        render_y + wall_size_ / 2.f + wall_size_ * wall_y_num,
        RenderAnchor::Center, wall_ex, 0.0f);
  }

  for (int y = 0; y < wall_y_num + 2; ++y) {
    wall_texture_.DrawRotated(render_x - wall_size_ / 2.f,
                              render_y + wall_size_ * y - wall_size_ / 2.f,
                              RenderAnchor::Center, wall_ex, 0.0f);

    wall_texture_.DrawRotated(
        render_x + wall_size_ / 2.f + wall_size_ * wall_x_num,
        render_y + wall_size_ * y - wall_size_ / 2.f, RenderAnchor::Center,
        wall_ex, 0.0f);
  }
}

}  // namespace mytetris
