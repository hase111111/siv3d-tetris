//! @file battle_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "battle_scene.h"

#include "game_const.h"
#include "game_end_checker_nothing.h"
#include "my_assert.h"
#include "score_calculator_nothing.h"
#include "tetris_field_effect_nothing.h"

namespace mytetris {

BattleScene::BattleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      block_size_(35.f * game_const::kResolutionEx),
      player_tetris_field_ptr_(std::make_shared<TetrisField>()),
      player_tetromino_ptr_(std::make_shared<Tetromino>()),
      player_next_ptr_(std::make_shared<NextTetromino>()),
      player_hold_ptr_(
          std::make_shared<HoldTetromino>(game_setting_record_ptr->allow_hold)),
      player_tetris_updater_{key_event_handler_ptr,
                             player_tetris_field_ptr_,
                             player_tetromino_ptr_,
                             player_next_ptr_,
                             player_hold_ptr_,
                             std::make_shared<TetrisLevel>(),
                             std::make_shared<DropCount>(),
                             std::make_shared<ScoreCalculatorNothing>(),
                             std::make_shared<GameEndCheckerNothing>(),
                             std::make_shared<TetrisFieldEffectNothing>(),
                             game_setting_record_ptr},
      player_tetris_renderer_{resource_container_ptr,
                              player_tetris_field_ptr_,
                              player_tetromino_ptr_,
                              std::make_shared<TetrisFieldEffectNothing>(),
                              block_size_,
                              game_setting_record_ptr->display_ghost_tetromino},
      player_hold_renderer_{resource_container_ptr, player_hold_ptr_,
                            block_size_},
      enemy_tetris_field_ptr_(std::make_shared<TetrisField>()),
      enemy_tetromino_ptr_(std::make_shared<Tetromino>()),
      enemy_next_ptr_(std::make_shared<NextTetromino>()),
      enemy_hold_ptr_(
          std::make_shared<HoldTetromino>(game_setting_record_ptr->allow_hold)),
      enemy_tetris_updater_{key_event_handler_ptr,
                            enemy_tetris_field_ptr_,
                            enemy_tetromino_ptr_,
                            enemy_next_ptr_,
                            enemy_hold_ptr_,
                            std::make_shared<TetrisLevel>(),
                            std::make_shared<DropCount>(),
                            std::make_shared<ScoreCalculatorNothing>(),
                            std::make_shared<GameEndCheckerNothing>(),
                            std::make_shared<TetrisFieldEffectNothing>(),
                            game_setting_record_ptr},
      enemy_tetris_renderer_{resource_container_ptr,
                             enemy_tetris_field_ptr_,
                             enemy_tetromino_ptr_,
                             std::make_shared<TetrisFieldEffectNothing>(),
                             block_size_,
                             game_setting_record_ptr->display_ghost_tetromino},
      enemy_hold_renderer_{resource_container_ptr, enemy_hold_ptr_,
                           block_size_} {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(player_tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(player_tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(player_next_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(player_hold_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_tetris_field_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_tetromino_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_next_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_hold_ptr_);

  // next を初期化.
  player_next_ptr_->SetGameMode(TetrisGameMode::kEndless);
  player_tetromino_ptr_->Reshape(player_next_ptr_->GetNext());
  player_next_ptr_->Next();

  enemy_next_ptr_->SetGameMode(TetrisGameMode::kEndless);
  enemy_tetromino_ptr_->Reshape(enemy_next_ptr_->GetNext());
  enemy_next_ptr_->Next();
}

bool BattleScene::Update() {
  player_tetris_updater_.Update();
  enemy_tetris_updater_.Update();
  return true;
}

void BattleScene::Draw() const {
  const float player_render_x = player_tetris_renderer_.GetRenderWidth() / 2.f;
  const float enemy_render_x =
      game_const::kResolutionXF - enemy_tetris_renderer_.GetRenderWidth() / 2.f;
  const float render_y = -player_tetris_renderer_.GetRenderHeight() / 2.f +
                         game_const::kResolutionYF;

  const auto [player_tetromino_x, player_tetromino_y] =
      player_tetris_updater_.GetPosition();
  player_tetris_renderer_.Draw(
      player_render_x, render_y, player_tetromino_x, player_tetromino_y,
      player_tetris_updater_.IsGameOver(), player_tetris_updater_.IsPinch());
  player_hold_renderer_.Draw(block_size_ * 11.5f, render_y - block_size_ * 13);

  const auto [enemy_tetromino_x, enemy_tetromino_y] =
      enemy_tetris_updater_.GetPosition();
  enemy_tetris_renderer_.Draw(
      enemy_render_x, render_y, enemy_tetromino_x, enemy_tetromino_y,
      enemy_tetris_updater_.IsGameOver(), enemy_tetris_updater_.IsPinch());
  enemy_hold_renderer_.Draw(game_const::kResolutionXF - block_size_ * 16.5f,
                            render_y - block_size_ * 13);
}

void BattleScene::OnStart(const SceneChangeParameter&) {}

}  // namespace mytetris
