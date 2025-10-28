//! @file setting_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "fade_effect.h"
#include "game_setting_record.h"
#include "i_scene.h"
#include "key_event_handler.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "setting_back.h"
#include "setting_ui.h"

namespace mytetris {

class SettingScene final : public IScene {
 public:
  SettingScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<GameSettingRecord>& game_setting_record_ptr);
  ~SettingScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter&) override {};

  void OnReturnFromOtherScene(const SceneChangeParameter&) override {};

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const SettingBack setting_back_;

  SettingUI setting_ui_;
  FadeEffect fade_effect_{30};
};

}  // namespace mytetris
