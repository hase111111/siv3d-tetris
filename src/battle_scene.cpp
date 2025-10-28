//! @file battle_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "battle_scene.h"

namespace mytetris {

BattleScene::BattleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr) {}

bool BattleScene::Update() { return true; }

void BattleScene::Draw() const {}

void BattleScene::OnStart(const SceneChangeParameter& parameter) {}

}  // namespace mytetris
