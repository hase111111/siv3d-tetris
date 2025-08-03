
//! @file title_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_scene.h"

#include "dxlib_assert.h"

namespace mytetris {

TitleScene::TitleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      game_setting_record_ptr_(game_setting_record_ptr),
      title_back_ground_{game_setting_record_ptr->window_width,
                         game_setting_record_ptr->window_height} {
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr);
  ASSERT_NOT_NULL_PTR(game_setting_record_ptr);
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
