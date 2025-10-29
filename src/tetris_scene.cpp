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
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      resource_container_ptr_(resource_container_ptr),
      next_tetromino_ptr_(std::make_shared<NextTetromino>()),
      tetris_field_ptr_(std::make_shared<TetrisField>()),
      tetromino_ptr_(std::make_shared<Tetromino>(
          std::vector<std::vector<bool>>{{1}}, TetrominoColor::kI,
          RotationType::kNormal)),
      hold_tetromino_ptr_(
          std::make_shared<HoldTetromino>(game_setting_record_ptr->allow_hold)),
      tetris_level_ptr_(std::make_shared<TetrisLevel>()),
      tetris_timer_ptr_(std::make_shared<TetrisTimer>()),
      drop_count_ptr_(std::make_shared<DropCount>()),
      game_end_checker_ptr_(std::make_shared<GameEndChecker>(
          tetris_level_ptr_, tetris_timer_ptr_)),
      tetris_announce_ptr_(std::make_shared<TetrisAnnounce>(
          resource_container_ptr, tetris_level_ptr_, tetris_timer_ptr_,
          game_end_checker_ptr_, tetris_field_ptr_)),
      score_calculator_ptr_(
          std::make_shared<ScoreCalculator>(tetris_announce_ptr_)),
      tetris_field_effect_ptr_(
          std::make_shared<TetrisFieldEffect>(tetris_level_ptr_)),
      tetris_updater_ptr_(std::make_unique<TetrisUpdater>(
          key_event_handler_ptr_, tetris_field_ptr_, tetromino_ptr_,
          next_tetromino_ptr_, hold_tetromino_ptr_, tetris_level_ptr_,
          drop_count_ptr_, score_calculator_ptr_, game_end_checker_ptr_,
          tetris_field_effect_ptr_, game_setting_record_ptr)),
      description_field_renderer_{resource_container_ptr, key_event_handler_ptr,
                                  game_end_checker_ptr_, tetris_field_ptr_,
                                  tetris_timer_ptr_},
      tetris_renderer_{resource_container_ptr,
                       tetris_field_ptr_,
                       tetromino_ptr_,
                       tetris_field_effect_ptr_,
                       40.0f,
                       game_setting_record_ptr->display_ghost_tetromino},
      next_renderer_{resource_container_ptr, next_tetromino_ptr_},
      hold_renderer_{resource_container_ptr, hold_tetromino_ptr_},
      fade_effect_{30},
      score_board_renderer_{tetris_timer_ptr_, tetris_level_ptr_,
                            drop_count_ptr_, score_calculator_ptr_,
                            resource_container_ptr},
      pause_renderer_{resource_container_ptr, key_event_handler_ptr},
      tetris_game_mode_{TetrisGameMode::kEndless} {
  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

bool TetrisScene::Update() {
  if (fade_effect_.Update()) {
    // フェード中は更新しない.
    return true;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kGameEnd) == 1) {
    // エスケープキーでゲーム終了.
    return false;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kToMenu) == 1) {
    // Zキーでタイトルへ戻る.
    fade_effect_.Start(FadeType::kFadeOut, [this]() {
      scene_change_listener_ptr_->RequestDeleteScene(1, {});
    });
    return true;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kRestart) == 1) {
    // Rキーでリトライ.
    fade_effect_.Start(FadeType::kFadeOut, [this]() {
      scene_change_listener_ptr_->RequestDeleteAndAddScene(SceneName::kTetris,
                                                           1, parameter_);
    });
    return true;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kPause) == 1) {
    // Pキーでポーズ.
    is_paused_ = !is_paused_;
  }

  if (is_paused_) {
    // ポーズ中は更新しない.
    return true;
  }

  tetris_updater_ptr_->Update();

  if (!tetris_field_ptr_->IsGameOver() && !game_end_checker_ptr_->IsGameEnd()) {
    tetris_timer_ptr_->Update();
  }

  const auto cleared_lines = tetris_updater_ptr_->GetClearedLines();

  if (!tetris_field_ptr_->IsGameOver()) {
    tetris_level_ptr_->AddClearLines(static_cast<int>(cleared_lines.size()));
  }

  // 描画画面の更新.
  tetris_renderer_.SetClearLines(cleared_lines);
  tetris_renderer_.Update();
  tetris_field_effect_ptr_->Update();
  description_field_renderer_.Update();
  score_calculator_ptr_->Update();
  tetris_announce_ptr_->Update();

  return true;
}

void TetrisScene::Draw() const {
  next_renderer_.Draw(880, 40);

  drop_gauge_renderer_.Draw(960, 888, tetris_updater_ptr_->GetDropGauge(),
                            tetris_updater_ptr_->GetFixGauge(),
                            tetris_updater_ptr_->GetMoveGauge());

  hold_renderer_.Draw(1060, 20);

  score_board_renderer_.Draw(1060, 260);

  description_field_renderer_.Draw(20, 20);

  const auto [tetromino_x, tetromino_y] = tetris_updater_ptr_->GetPosition();
  tetris_renderer_.Draw(
      game_const::kResolutionX / 2,
      game_const::kResolutionY / 2 -
          static_cast<int>(tetris_renderer_.GetBlockSize() * 1.5f),
      tetromino_x, tetromino_y, tetris_updater_ptr_->IsGameOver(),
      tetris_updater_ptr_->IsPinch());

  tetris_announce_ptr_->Draw(game_const::kResolutionX / 2,
                             game_const::kResolutionY / 2);

  pause_renderer_.Draw(is_paused_);

  fade_effect_.Draw();
}

void TetrisScene::OnStart(const SceneChangeParameter& parameter) {
  parameter_ = parameter;
  tetris_game_mode_ = parameter.GetParameter<TetrisGameMode>("GameMode");
  score_board_renderer_.SetGameMode(tetris_game_mode_);
  tetris_announce_ptr_->SetGameMode(tetris_game_mode_);
  game_end_checker_ptr_->SetGameMode(tetris_game_mode_);
  next_tetromino_ptr_->SetGameMode(tetris_game_mode_);
  tetris_level_ptr_->SetGameMode(tetris_game_mode_);

  tetris_field_effect_ptr_->SetActive(tetris_game_mode_ ==
                                      TetrisGameMode::kTrick);

  tetromino_ptr_->Reshape(next_tetromino_ptr_->GetNext());
  next_tetromino_ptr_->Next();
}

}  // namespace mytetris
