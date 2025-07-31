
//! @file scene_creator.cpp
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_creator.h"

#include "debug_scene.h"
#include "dxlib_assert.h"

namespace mytetris {

SceneCreator::SceneCreator(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const FpsController>& fps_controller_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<ResourceContainer>& dxlib_resource_loader_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      fps_controller_ptr_(fps_controller_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr) {
  // ポインタが nullptr でないことを確認
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  ASSERT_NOT_NULL_PTR(fps_controller_ptr);
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr);
  ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
}

std::unique_ptr<IScene> SceneCreator::createScene(
    const SceneName scene_name) const {
  switch (scene_name) {
    case SceneName::kDebug: {
      return std::make_unique<DebugScene>(scene_change_listener_ptr_,
                                          dxlib_keyboard_ptr_);
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      return nullptr;
    }
  }  // switch
}

}  // namespace mytetris
