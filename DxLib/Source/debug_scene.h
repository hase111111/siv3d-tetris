
//! @file debug_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "i_scene.h"
#include "key_event_handler.h"
#include "scene_change_listener.h"

namespace mytetris {

class DebugScene final : public IScene {
 public:
  DebugScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr);
  ~DebugScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter& parameter) override;

 private:
  std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
};

}  // namespace mytetris
