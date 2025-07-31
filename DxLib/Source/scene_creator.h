
//! @file scene_creator.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "fps_controller.h"
#include "i_scene.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "scene_name.h"

namespace mytetris {

//! @brief シーンを生成するクラス．
class SceneCreator final {
 public:
  SceneCreator(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const FpsController>& fps_controller_ptr,
      const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
      const std::shared_ptr<ResourceContainer>& dxlib_resource_loader_ptr);
  ~SceneCreator() = default;

  //! @brief シーンを生成する．
  //! @param[in] scene_name シーンの名前．
  //! @return 生成したシーン．
  [[nodiscard]] std::unique_ptr<IScene> createScene(SceneName scene_name) const;

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

  const std::shared_ptr<const FpsController> fps_controller_ptr_;

  const std::shared_ptr<const DxLibKeyboard> dxlib_keyboard_ptr_;

  const std::shared_ptr<ResourceContainer> dxlib_resource_loader_ptr_;
};

}  // namespace mytetris
