
//! @file debug_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "debug_scene.h"

#include <DxLib.h>

#include "my_assert.h"

namespace mytetris {

DebugScene::DebugScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr) {
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
}

bool DebugScene::Update() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kEscape) == 1) {
    return false;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kT) == 1) {
    scene_change_listener_ptr_->RequestAddScene(SceneName::kTetris,
                                                SceneChangeParameter{});
  }

  return true;
}

void DebugScene::Draw() const {
  DrawString(0, 0, "Debug Scene", GetColor(255, 255, 255));
}

void DebugScene::OnStart(const SceneChangeParameter&) {}

void DebugScene::OnReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
