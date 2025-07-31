
//! @file scene_change_executer.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_change_executer.h"

#include "dxlib_assert.h"

namespace mytetris {

SceneChangeExecuter::SceneChangeExecuter(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<SceneStack>& scene_stack_ptr)
    : scene_change_listener_ptr_{scene_change_listener_ptr},
      scene_stack_ptr_{scene_stack_ptr} {
  // NULL チェック．
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
  ASSERT_NOT_NULL_PTR(scene_stack_ptr);
}

void SceneChangeExecuter::Execute() {
  // リクエストがない場合は何もしない．
  if (!scene_change_listener_ptr_->HasRequest()) {
    return;
  }

  // リクエストを受け取る．
  const auto [request_type, scene_name, parameter, delete_num] =
      scene_change_listener_ptr_->ReceiveRequest();

  // リクエストに応じて処理を行う．
  switch (request_type) {
    case SceneChangeListener::RequestType::kAddScene: {
      scene_stack_ptr_->AddNewScene(scene_name, parameter);
      break;
    }
    case SceneChangeListener::RequestType::kDeleteScene: {
      scene_stack_ptr_->DeleteNowScene(delete_num, parameter);
      break;
    }
    case SceneChangeListener::RequestType::kDeleteAllScene: {
      scene_stack_ptr_->DeleteAllScene();
      break;
    }
    default: {
      ASSERT_MUST_NOT_REACH_HERE();
      break;
    }
  }
}

}  // namespace mytetris
