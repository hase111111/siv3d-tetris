//! @file score_board_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "score_board_renderer.h"

#include "game_const.h"
#include "my_assert.h"
#include "my_format.h"

namespace mytetris {

ScoreBoardRenderer::ScoreBoardRenderer(
    const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr,
    const std::shared_ptr<const TetrisLevel>& tetris_level_ptr,
    const std::shared_ptr<const DropCount>& drop_count_ptr,
    const std::shared_ptr<const ScoreCalculator>& score_calculator_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : tetris_timer_ptr_(tetris_timer_ptr),
      tetris_level_ptr_(tetris_level_ptr),
      tetris_game_mode_(TetrisGameMode::kEndless),  // 仮に初期化.
      font_view_(resource_container_ptr->GetFont("small")),
      drop_count_ptr_(drop_count_ptr),
      score_calculator_ptr_(score_calculator_ptr),
      wall_texture_(resource_container_ptr->GetTexture("wall.png")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(score_calculator_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_level_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(drop_count_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(score_calculator_ptr_);
}

void ScoreBoardRenderer::Draw(const int render_x, const int render_y) const {
  const float wall_size{40.f * game_const::kResolutionEx};
  const float wall_ex{2.f * game_const::kResolutionEx};
  const float box_size_x{wall_size * 5.f};
  const float box_size_y{wall_size * 17.f};

  // 文字.
  font_view_.Draw(render_x + wall_size * 3 / 4.0f,
                  render_y + wall_size * 3 / 4.0f, RenderAnchor::TopLeft,
                  "Score Board", game_const::kResolutionEx);
  font_view_.Draw(render_x + wall_size * 3 / 4.f, render_y + wall_size * 2.f,
                  RenderAnchor::TopLeft, GetString(),
                  game_const::kResolutionEx);

  // フレーム.
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

  const auto diff = score_calculator_ptr_->GetScoreDifference();
  result +=
      nostd::format("Score\n {} \n{}\n\n", score_calculator_ptr_->GetScore(),
                    diff == 0 ? "" : nostd::format("(diff +{})", diff));
  result += "Time\n " + tetris_timer_ptr_->GetTimeString() + "\n\n";
  result += nostd::format("Level\n {}\n\n", tetris_level_ptr_->GetLevel());
  result +=
      nostd::format("Lines\n {}\n\n", tetris_level_ptr_->GetTotalClearLines());
  result += nostd::format("Speed\n {}\n\n", drop_count_ptr_->GetDisplaySpeed(
                                                tetris_level_ptr_->GetLevel()));
  result += nostd::format("GameRule\n {}\n\n", ToString(tetris_game_mode_));
  result +=
      nostd::format("Combo\n {}\n\n", score_calculator_ptr_->GetComboNum());
  result += nostd::format(
      " {}\n\n", score_calculator_ptr_->IsBtbActive() ? "Back to Back" : "");

  return result;
}

}  // namespace mytetris
