//! @file battle_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "game_setting_record.h"
#include "i_scene.h"
#include "key_event_handler.h"
#include "resource_container.h"
#include "scene_change_listener.h"

namespace mytetris {

class BattleScene final : public IScene {
 public:
  BattleScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr);
  ~BattleScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter&) override {};

 private:
};

}  // namespace mytetris