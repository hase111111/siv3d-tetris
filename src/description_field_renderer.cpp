//! @file description_field_renderer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "description_field_renderer.h"

#include "calc_util.h"
#include "game_const.h"
#include "my_assert.h"
#include "my_format.h"

namespace mytetris {

DescriptionFieldRenderer::DescriptionFieldRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const GameEndChecker>& game_end_checker_ptr,
    const std::shared_ptr<const TetrisField>& tetris_field_ptr,
    const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr)
    : key_ptr_(key_event_handler_ptr),
      game_end_checker_ptr_(game_end_checker_ptr),
      tetris_field_ptr_(tetris_field_ptr),
      tetris_timer_ptr_(tetris_timer_ptr),
      font_view_(resource_container_ptr->GetFont("small")),
      wall_texture_(resource_container_ptr->GetTexture("wall.png")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(game_end_checker_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_end_checker_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(tetris_timer_ptr_);
}

void DescriptionFieldRenderer::Update() {
  // ゲーム終了時は入力をカウントしない.
  if (game_end_checker_ptr_->IsGameEnd() || tetris_field_ptr_->IsGameOver()) {
    return;
  }

  std::vector<KeyGroup> keys_to_check{
      KeyGroup::kLeft,     KeyGroup::kRight,     KeyGroup::kDown, KeyGroup::kUp,
      KeyGroup::kRotateCW, KeyGroup::kRotateCCW, KeyGroup::kHold,
  };

  for (const auto& key : keys_to_check) {
    if (key_ptr_->GetPressingCount(key) == 1) {
      ++input_counter;

      if (key == KeyGroup::kUp) {
        ++hard_drop_counter;
      }

      input_history_.push_back(
          KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(key)));
      if (static_cast<int>(input_history_.size()) > max_history_size_) {
        input_history_.erase(input_history_.begin());
      }
    }
  }
}

void DescriptionFieldRenderer::Draw(const int render_x,
                                    const int render_y) const {
  const float wall_size{40.f * game_const::kResolutionEx};
  const float wall_ex{2.f};
  const float box_size_x{wall_size * 10.f};
  const float box_size_y{wall_size * 23.f};

  // フレーム.
  for (int x = 0; x < box_size_x / wall_size; ++x) {
    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f, RenderAnchor::TopLeft,
                              wall_ex * game_const::kResolutionEx, 0.0f);

    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size / 2.f + box_size_y,
                              RenderAnchor::TopLeft,
                              wall_ex * game_const::kResolutionEx, 0.0f);

    wall_texture_.DrawRotated(render_x + wall_size * x - wall_size / 2.f,
                              render_y - wall_size + box_size_y / 2.f,
                              RenderAnchor::TopLeft,
                              wall_ex * game_const::kResolutionEx, 0.0f);
  }

  for (int y = 0; y < box_size_y / wall_size + 1; ++y) {
    wall_texture_.DrawRotated(
        render_x - wall_size / 2.f, render_y + wall_size * y - wall_size / 2.f,
        RenderAnchor::TopLeft, wall_ex * game_const::kResolutionEx, 0.0f);
    wall_texture_.DrawRotated(render_x - wall_size / 2.f + box_size_x,
                              render_y + wall_size * y - wall_size / 2.f,
                              RenderAnchor::TopLeft,
                              wall_ex * game_const::kResolutionEx, 0.0f);
  }

  // 文字.
  font_view_.Draw(render_x + wall_size * 3.f / 4.0f,
                  render_y + wall_size * 3.f / 4.0f, RenderAnchor::TopLeft,
                  "Controls:", game_const::kResolutionEx);
  font_view_.Draw(render_x + wall_size, render_y + wall_size * 2.f,
                  RenderAnchor::TopLeft, GetString(),
                  game_const::kResolutionEx);

  // 下の文字.
  font_view_.Draw(
      render_x + wall_size * 3 / 4.0f,
      render_y + wall_size * 3 / 4.0f - wall_size / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft, "Input History:", game_const::kResolutionEx);

  // キー入力の履歴を表示する.
  for (size_t i = 0; i < input_history_.size(); ++i) {
    font_view_.Draw(
        render_x + wall_size,
        render_y + wall_size * 3 / 4.0f - wall_size / 2.f + box_size_y / 2.f +
            20 * static_cast<float>(i + 1),
        RenderAnchor::TopLeft,
        nostd::format(
            "{}: {}",
            i + 1 + std::max<int>(0, input_counter - max_history_size_),
            input_history_[i]),
        game_const::kResolutionEx);
  }

  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.0f - wall_size / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft, "Input per Sec:", game_const::kResolutionEx);

  const auto time = tetris_timer_ptr_->GetTime();
  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.f + wall_size / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft,
      nostd::format(
          " {} input/sec",
          time == 0 ? "0.000" : RoundToString(input_counter * 60.f / time, 3)),
      game_const::kResolutionEx);

  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.f + wall_size * 3.f / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft, "HardDrop per Sec:", game_const::kResolutionEx);
  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.f + wall_size * 5.f / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft,
      nostd::format(" {} drop/sec",
                    time == 0
                        ? "0.000"
                        : RoundToString(hard_drop_counter * 60.f / time, 3)),
      game_const::kResolutionEx);

  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.f + wall_size * 7.f / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft, "HardDrop per Input:", game_const::kResolutionEx);
  font_view_.Draw(
      render_x + box_size_x / 2.f,
      render_y + wall_size * 3 / 4.f + wall_size * 9.f / 2.f + box_size_y / 2.f,
      RenderAnchor::TopLeft,
      nostd::format(
          " {} drop/input",
          input_counter == 0
              ? "0.000"
              : RoundToString(
                    hard_drop_counter / static_cast<float>(input_counter), 3)),
      game_const::kResolutionEx);
}

std::string DescriptionFieldRenderer::GetString() const {
  using enum KeyGroup;
  return nostd::format(
      "Move Left: {}\n"
      "Move Right: {}\n"
      "Soft Drop: {}\n"
      "Hard Drop: {}\n"
      "Rotate Clockwise: {}\n"
      "Rotate Inverse: {}\n"
      "Hold: {}\n"
      "\n"
      "Back to Menu: {}\n"
      "Pause: {}\n"
      "Reset: {}\n"
      "End Game: Esc\n"
      "\n",
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kLeft)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kRight)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kDown)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kUp)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kRotateCW)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kRotateCCW)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kHold)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kToMenu)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kPause)),
      KeyHandleToString(key_ptr_->GetKeyHandleFromKeyGroup(kRestart)));
}

}  // namespace mytetris
