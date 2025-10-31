//! @file battle_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "battle_scene.h"

#include "game_const.h"
#include "tetris_field_effect_nothing.h"

namespace mytetris {

BattleScene::BattleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : player_tetris_field_ptr_(std::make_shared<TetrisField>()),
      player_tetromino_ptr_(std::make_shared<Tetromino>()),
      player_tetris_renderer_{
          resource_container_ptr,
          player_tetris_field_ptr_,
          player_tetromino_ptr_,
          std::make_shared<TetrisFieldEffectNothing>(),
          40.f * game_const::kResolutionEx,
          game_setting_record_ptr->display_ghost_tetromino} {}

bool BattleScene::Update() { return true; }

void BattleScene::Draw() const {
  player_tetris_renderer_.Draw(
      game_const::kResolutionXF / 2.f - 200.f * game_const::kResolutionEx,
      game_const::kResolutionYF / 2.f, 0, 0, false, false);
}

void BattleScene::OnStart(const SceneChangeParameter&) {}

}  // namespace mytetris
