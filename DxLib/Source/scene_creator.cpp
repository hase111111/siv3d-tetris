
//! @file scene_creator.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_creator.h"

#include "debug_scene.h"
#include "dxlib_assert.h"
#include "tetris_scene.h"
#include "title_scene.h"

namespace mytetris {

SceneCreator::SceneCreator(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const FpsController>& fps_controller_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      fps_controller_ptr_(fps_controller_ptr),
      key_event_handler_ptr_(key_event_handler_ptr),
      resource_container_ptr_(resource_container_ptr),
      game_setting_record_ptr_(game_setting_record_ptr) {
  // ポインタが nullptr でないことを確認.
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
  ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  ASSERT_NOT_NULL_PTR(resource_container_ptr_);
  ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
}

std::unique_ptr<IScene> SceneCreator::CreateScene(
    const SceneName scene_name) const {
  switch (scene_name) {
    case SceneName::kDebug: {
      return std::make_unique<DebugScene>(scene_change_listener_ptr_,
                                          key_event_handler_ptr_);
    }
    case SceneName::kTitle: {
      return std::make_unique<TitleScene>(scene_change_listener_ptr_,
                                          key_event_handler_ptr_,
                                          resource_container_ptr_);
    }
    case SceneName::kTetris: {
      return std::make_unique<TetrisScene>(scene_change_listener_ptr_,
                                           key_event_handler_ptr_,
                                           resource_container_ptr_);
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      return nullptr;
    }
  }  // switch
}

}  // namespace mytetris
