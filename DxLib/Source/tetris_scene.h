
//! @file tetris_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "i_scene.h"
#include "next_tetromino.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "tetris_feild.h"
#include "tetris_renderer.h"

namespace mytetris {

class TetrisScene final : public IScene {
 public:
  TetrisScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~TetrisScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter& parameter) override;

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const std::shared_ptr<const DxLibKeyboard> dxlib_keyboard_ptr_;
  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  TetrisField tetris_field_;
  TetrisRenderer tetris_renderer_;
  NextTetromino next_tetromino_;
  Tetromino current_tetromino_;
  int tetromino_x_{4};
  int tetromino_y_{-2};
};

}  // namespace mytetris
