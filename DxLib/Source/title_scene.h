
//! @file title_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "i_scene.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "title_back_ground.h"

namespace mytetris {

class TitleScene final : public IScene {
 public:
  TitleScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~TitleScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter& parameter) override;

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const std::shared_ptr<const DxLibKeyboard> dxlib_keyboard_ptr_;
  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  TitleBackGround title_back_ground_;
};

}  // namespace mytetris
