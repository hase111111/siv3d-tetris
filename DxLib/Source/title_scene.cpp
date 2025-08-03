
//! @file title_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_scene.h"

#include "dxlib_assert.h"
#include "game_const.h"

namespace mytetris {

TitleScene::TitleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      resource_container_ptr_(resource_container_ptr),
      title_back_ground_{GameConst::kResolutionX, GameConst::kResolutionY,
                         resource_container_ptr_} {
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr);
  ASSERT_NOT_NULL_PTR(resource_container_ptr);
}

bool TitleScene::Update() {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kEscape) == 1) {
    return false;
  }

  return true;
}

void TitleScene::Draw() const { title_back_ground_.Draw(); }

void TitleScene::OnStart(const SceneChangeParameter&) {}

void TitleScene::OnReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
