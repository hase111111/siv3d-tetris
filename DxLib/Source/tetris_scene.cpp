
//! @file tetris_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_scene.h"

#include "game_const.h"
#include "tetromino_generator.h"

namespace mytetris {

TetrisScene::TetrisScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      resource_container_ptr_(resource_container_ptr),
      next_tetromino_ptr_(std::make_shared<NextTetromino>()),
      tetris_field_ptr_(std::make_shared<TetrisField>()),
      tetromino_ptr_(
          std::make_shared<Tetromino>(next_tetromino_ptr_->GetNext())),
      hold_tetromino_ptr_(std::make_shared<HoldTetromino>()),
      tetris_level_ptr_(std::make_shared<TetrisLevel>()),
      tetris_timer_ptr_(std::make_shared<TetrisTimer>()),
      drop_count_ptr_(std::make_shared<DropCount>()),
      tetris_updater_ptr_(std::make_unique<TetrisUpdater>(
          key_event_handler_ptr_, tetris_field_ptr_, tetromino_ptr_,
          next_tetromino_ptr_, hold_tetromino_ptr_, tetris_level_ptr_,
          drop_count_ptr_)),
      tetris_renderer_{resource_container_ptr, tetris_field_ptr_,
                       tetromino_ptr_, 40.0f},
      next_renderer_{resource_container_ptr, next_tetromino_ptr_},
      hold_renderer_{resource_container_ptr, hold_tetromino_ptr_},
      fade_effect_{30},
      score_board_renderer_{tetris_timer_ptr_, tetris_level_ptr_,
                            drop_count_ptr_, resource_container_ptr_} {
  next_tetromino_ptr_->Next();
  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

bool TetrisScene::Update() {
  if (fade_effect_.Update()) {
    return true;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kEscape) == 1) {
    return false;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
    fade_effect_.Start(FadeType::kFadeOut, [this]() {
      scene_change_listener_ptr_->RequestDeleteScene(1, {});
    });
    return true;
  }

  tetris_updater_ptr_->Update();
  tetris_timer_ptr_->Update();

  const auto cleared_lines = tetris_updater_ptr_->GetClearedLines();
  tetris_level_ptr_->AddClearLines(static_cast<int>(cleared_lines.size()));

  // •`‰æ‰æ–Ê‚ÌXV.
  tetris_renderer_.SetClearLines(cleared_lines);
  tetris_renderer_.Update();

  drop_gauge_renderer_.SetDropPercent(tetris_updater_ptr_->GetDropGauge());
  drop_gauge_renderer_.SetFixPercent(tetris_updater_ptr_->GetFixGauge());
  drop_gauge_renderer_.SetMovePercent(tetris_updater_ptr_->GetMoveGauge());

  return true;
}

void TetrisScene::Draw() const {
  next_renderer_.Draw(880, 40);

  drop_gauge_renderer_.Draw(960, 888);

  hold_renderer_.Draw(1060, 20);

  score_board_renderer_.Draw(1060, 260);

  const auto [tetromino_x, tetromino_y] = tetris_updater_ptr_->GetPosition();
  tetris_renderer_.Draw(
      GameConst::kResolutionX / 2,
      GameConst::kResolutionY / 2 -
          static_cast<int>(tetris_renderer_.GetBlockSize() * 1.5f),
      tetromino_x, tetromino_y);

  fade_effect_.Draw();
}

void TetrisScene::OnStart(const SceneChangeParameter&) {}

void TetrisScene::OnReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
