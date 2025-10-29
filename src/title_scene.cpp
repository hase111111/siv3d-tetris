//! @file title_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_scene.h"

#include "game_const.h"
#include "my_assert.h"
#include "render_util.h"

namespace mytetris {

TitleScene::TitleScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      resource_container_ptr_(resource_container_ptr),
      title_back_ground_{resource_container_ptr},
      title_ui_{
          key_event_handler_ptr, resource_container_ptr,
          std::bind(&TitleScene::ToTetrisScene, this, std::placeholders::_1),
          std::bind(&TitleScene::ToSettingScene, this)},
      fade_effect_{30} {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr_);

  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

bool TitleScene::Update() {
  // フェード処理を優先して行う．
  if (fade_effect_.Update()) {
    return true;
  }

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kGameEnd) == 1) {
    return false;
  }

  return title_ui_.Update();
}

void TitleScene::Draw() const {
  title_back_ground_.Draw();
  title_ui_.Draw();
  fade_effect_.Draw();
}

void TitleScene::OnStart(const SceneChangeParameter&) {}

void TitleScene::OnReturnFromOtherScene(const SceneChangeParameter&) {
  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

void TitleScene::ToTetrisScene(const SceneChangeParameter& parameter) {
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  fade_effect_.Start(FadeType::kFadeOut, [this, parameter]() {
    scene_change_listener_ptr_->RequestAddScene(SceneName::kTetris, parameter);
  });
}

void TitleScene::ToSettingScene() {
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  fade_effect_.Start(FadeType::kFadeOut, [this]() {
    scene_change_listener_ptr_->RequestAddScene(SceneName::kSetting, {});
  });
}

}  // namespace mytetris
