
//! @file scene_change_executer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "scene_change_listener.h"
#include "scene_stack.h"

namespace mytetris {

class SceneChangeExecuter final {
 public:
  SceneChangeExecuter(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<SceneStack>& scene_stack_ptr);

  //! @brief シーンの変更を実行する．
  //! リクエストがない場合は何もしない．
  void execute();

 private:
  std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  std::shared_ptr<SceneStack> scene_stack_ptr_;
};

}  // namespace mytetris
