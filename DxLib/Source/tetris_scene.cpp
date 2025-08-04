
//! @file tetris_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_scene.h"

namespace mytetris {

TetrisScene::TetrisScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      resource_container_ptr_(resource_container_ptr),
      tetris_field_renderer_{resource_container_ptr} {}

bool TetrisScene::Update() { return true; }

void TetrisScene::Draw() const {}

void TetrisScene::OnStart(const SceneChangeParameter& parameter) {}

void TetrisScene::OnReturnFromOtherScene(
    const SceneChangeParameter& parameter) {}

}  // namespace mytetris
