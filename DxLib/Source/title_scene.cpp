
//! @file title_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_scene.h"

#include "game_const.h"
#include "my_assert.h"

namespace mytetris {

TitleScene::TitleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      resource_container_ptr_(resource_container_ptr),
      title_back_ground_{GameConst::kResolutionX, GameConst::kResolutionY,
                         resource_container_ptr_} {
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr_);
}

bool TitleScene::Update() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kEscape) == 1) {
    return false;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
    scene_change_listener_ptr_->RequestAddScene(SceneName::kTetris,
                                                SceneChangeParameter{});
    return true;
  }

  return true;
}

void TitleScene::Draw() const { title_back_ground_.Draw(); }

void TitleScene::OnStart(const SceneChangeParameter&) {}

void TitleScene::OnReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
