
#include "debug_scene.h"

#include <DxLib.h>

#include "dxlib_assert.h"

namespace mytetris {

DebugScene::DebugScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr) {
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr);
}

bool DebugScene::update() {
  if (dxlib_keyboard_ptr_->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
    return false;
  }

  if (dxlib_keyboard_ptr_->getPressingCount(KEY_INPUT_R) == 1) {
    scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
  }

  return true;
}

void DebugScene::draw() const {
  DrawString(0, 0, "Debug Scene", GetColor(255, 255, 255));
}

void DebugScene::onStart(const SceneChangeParameter&) {}

void DebugScene::onReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
