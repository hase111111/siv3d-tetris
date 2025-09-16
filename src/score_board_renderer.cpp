
//! @file score_board_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "score_board_renderer.h"

#include "my_assert.h"
#include "my_format.h"

namespace mytetris {

ScoreBoardRenderer::ScoreBoardRenderer(
    const std::shared_ptr<TetrisTimer>& tetris_timer_ptr,
    const std::shared_ptr<TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<DropCount>& drop_count_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : tetris_timer_ptr_(tetris_timer_ptr),
      tetris_level_ptr_(tetris_level_ptr),
      tetris_game_mode_(TetrisGameMode::kEndless),  // âºÇ…èâä˙âª.
      font_view_(resource_container_ptr->GetFont("small")),
      drop_count_ptr_(drop_count_ptr),
      wall_texture_(resource_container_ptr->GetTexture("wall.png")) {
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
}

void ScoreBoardRenderer::Draw(const int render_x, const int render_y) const {
  const float wall_size{40.f};
  const float wall_ex{2.f};
  const float box_size_x{wall_size * 5.f};
  const float box_size_y{wall_size * 17.f};

  // ï∂éö.
  font_view_.Draw(render_x + wall_size * 3 / 4.0f,
                  render_y + wall_size * 3 / 4.0f, RenderAnchor::TopLeft,
                  "Score Board");
  font_view_.Draw(render_x + wall_size * 3 / 4.f, render_y + wall_size * 2.f,
                  RenderAnchor::TopLeft, GetString());

  // ÉtÉåÅ[ÉÄ.
  for (int x = 0; x < box_size_x / wall_size; ++x) {
    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f, RenderAnchor::TopLeft,
                              wall_ex, 0.0f);

    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f + box_size_y,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }

  for (int y = 0; y < box_size_y / wall_size + 1; ++y) {
    wall_texture_.DrawRotated(render_x - wall_size / 2.f,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
    wall_texture_.DrawRotated(render_x - wall_size / 2.f + box_size_x,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft, wall_ex, 0.0f);
  }
}

std::string ScoreBoardRenderer::GetString() const {
  std::string result;

  result += "Score\n 0 \n\n";
  result += "Time\n " + tetris_timer_ptr_->GetTimeString() + "\n\n";
  result += nostd::format("Level\n {}\n\n", tetris_level_ptr_->GetLevel());
  result +=
      nostd::format("Lines\n {}\n\n", tetris_level_ptr_->GetTotalClearLines());
  result += nostd::format("Speed\n {}\n\n", drop_count_ptr_->GetDisplaySpeed(
                                                tetris_level_ptr_->GetLevel()));
  result += nostd::format("GameRule\n {}\n\n", ToString(tetris_game_mode_));

  return result;
}

}  // namespace mytetris
