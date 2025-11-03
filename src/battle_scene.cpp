//! @file battle_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "battle_scene.h"

#include "drop_count_for_battle.h"
#include "game_const.h"
#include "game_end_checker_nothing.h"
#include "input_bridge_keyboard.h"
#include "input_bridge_simple_cpu.h"
#include "log_print.h"
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
      key_event_handler_ptr_(key_event_handler_ptr),
      block_size_(35.f * game_const::kResolutionEx),
      player_tetris_field_ptr_(std::make_shared<TetrisField>()),
      player_tetromino_ptr_(std::make_shared<Tetromino>()),
      player_next_ptr_(std::make_shared<NextTetromino>()),
      player_hold_ptr_(
          std::make_shared<HoldTetromino>(game_setting_record_ptr->allow_hold)),
      player_announce_ptr_(
          std::make_shared<BattleAnnounce>(resource_container_ptr)),
      player_score_calculator_ptr_(
          std::make_shared<ScoreCalculatorForBattle>(player_announce_ptr_)),
      player_tetris_updater_ptr_(std::make_shared<TetrisUpdater>(
          std::make_shared<InputBridgeKeyBoard>(key_event_handler_ptr),
          player_tetris_field_ptr_, player_tetromino_ptr_, player_next_ptr_,
          player_hold_ptr_, std::make_shared<TetrisLevel>(),
          std::make_shared<DropCountForBattle>(), player_score_calculator_ptr_,
          std::make_shared<GameEndCheckerNothing>(),
          std::make_shared<TetrisFieldEffectNothing>(),
          game_setting_record_ptr)),
      player_tetris_renderer_{resource_container_ptr,
                              player_tetris_field_ptr_,
                              player_tetromino_ptr_,
                              std::make_shared<TetrisFieldEffectNothing>(),
                              player_tetris_updater_ptr_,
                              block_size_,
                              game_setting_record_ptr->display_ghost_tetromino},
      player_hold_renderer_{resource_container_ptr, player_hold_ptr_,
                            block_size_},
      player_next_renderer_{resource_container_ptr, player_next_ptr_,
                            block_size_, 2},
      enemy_tetris_field_ptr_(std::make_shared<TetrisField>()),
      enemy_tetromino_ptr_(std::make_shared<Tetromino>()),
      enemy_next_ptr_(std::make_shared<NextTetromino>()),
      enemy_hold_ptr_(
          std::make_shared<HoldTetromino>(game_setting_record_ptr->allow_hold)),
      enemy_announce_ptr_(
          std::make_shared<BattleAnnounce>(resource_container_ptr)),
      enemy_score_calculator_ptr_(
          std::make_shared<ScoreCalculatorForBattle>(enemy_announce_ptr_)),
      enemy_tetris_updater_ptr_(std::make_shared<TetrisUpdater>(
          std::make_shared<InputBridgeSimpleCPU>(
              enemy_tetris_field_ptr_, enemy_tetromino_ptr_, enemy_next_ptr_,
              enemy_hold_ptr_),
          enemy_tetris_field_ptr_, enemy_tetromino_ptr_, enemy_next_ptr_,
          enemy_hold_ptr_, std::make_shared<TetrisLevel>(),
          std::make_shared<DropCountForBattle>(), enemy_score_calculator_ptr_,
          std::make_shared<GameEndCheckerNothing>(),
          std::make_shared<TetrisFieldEffectNothing>(),
          game_setting_record_ptr)),
      enemy_tetris_renderer_{resource_container_ptr,
                             enemy_tetris_field_ptr_,
                             enemy_tetromino_ptr_,
                             std::make_shared<TetrisFieldEffectNothing>(),
                             enemy_tetris_updater_ptr_,
                             block_size_,
                             game_setting_record_ptr->display_ghost_tetromino},
      enemy_hold_renderer_{resource_container_ptr, enemy_hold_ptr_,
                           block_size_},
      enemy_next_renderer_{resource_container_ptr, enemy_next_ptr_, block_size_,
                           2},
      penalty_updater_ptr_(std::make_shared<PenaltyUpdater>(
          player_score_calculator_ptr_, enemy_score_calculator_ptr_)),
      penalty_renderer_(resource_container_ptr, penalty_updater_ptr_,
                        block_size_),
      fade_effect_{30} {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);

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

  // フェードイン開始.
  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

bool BattleScene::Update() {
  // 盤面の更新.
  player_tetris_updater_ptr_->Update();
  enemy_tetris_updater_ptr_->Update();

  // アナウンスの更新.
  player_announce_ptr_->Update();
  enemy_announce_ptr_->Update();

  // ペナルティライン追加.
  const auto [p_player, p_enemy] = penalty_updater_ptr_->Update();
  player_tetris_updater_ptr_->AddPenaltyLines(p_player);
  enemy_tetris_updater_ptr_->AddPenaltyLines(p_enemy);

  // 描画用データの更新.
  player_tetris_renderer_.Update();
  enemy_tetris_renderer_.Update();
  return true;
}

void BattleScene::Draw() const {
  const float player_render_x =
      player_tetris_renderer_.GetRenderWidth() / 2.f + block_size_ / 4.f;
  const float enemy_render_x = game_const::kResolutionXF -
                               enemy_tetris_renderer_.GetRenderWidth() / 2.f -
                               block_size_ / 4.f;
  const float render_y = -player_tetris_renderer_.GetRenderHeight() / 2.f +
                         game_const::kResolutionYF - block_size_ / 4.f;

  player_hold_renderer_.Draw(player_render_x + block_size_ * 5.5f,
                             render_y - block_size_ * 13.f);
  player_next_renderer_.Draw(player_render_x + block_size_ * 6.f,
                             render_y - block_size_ * 6.5f);

  enemy_hold_renderer_.Draw(enemy_render_x - block_size_ * 10.5f,
                            render_y - block_size_ * 13.f);
  enemy_next_renderer_.Draw(enemy_render_x - block_size_ * 10.f,
                            render_y - block_size_ * 6.5f);

  penalty_renderer_.Draw(player_render_x + block_size_ * 6.f,
                         render_y + block_size_ * 4.5f);

  player_tetris_renderer_.Draw(player_render_x, render_y);
  enemy_tetris_renderer_.Draw(enemy_render_x, render_y);

  player_announce_ptr_->Draw(player_render_x, render_y);
  enemy_announce_ptr_->Draw(enemy_render_x, render_y);
}

void BattleScene::OnStart(const SceneChangeParameter&) {}

}  // namespace mytetris
