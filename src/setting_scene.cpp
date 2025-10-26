#include "setting_scene.h"

#include "my_assert.h"

namespace mytetris {

SettingScene::SettingScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      setting_back_{resource_container_ptr},
      setting_ui_{resource_container_ptr, []() {}} {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);

  // フェードを始める.
  fade_effect_.Start(FadeType::kFadeIn, []() {});
}

bool SettingScene::Update() {
  if (fade_effect_.Update()) {
    return true;
  }

  setting_ui_.Update();

  return true;
}

void SettingScene::Draw() const {
  setting_back_.Draw();

  setting_ui_.Draw();

  fade_effect_.Draw();
}

void SettingScene::OnStart(const SceneChangeParameter&) {}

}  // namespace mytetris
