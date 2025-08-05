
//! @file tetris_scene.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_scene.h"

#include "game_const.h"
#include "tetromino_generator.h"

namespace mytetris {

TetrisScene::TetrisScene(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& dxlib_keyboard_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : scene_change_listener_ptr_(scene_change_listener_ptr),
      dxlib_keyboard_ptr_(dxlib_keyboard_ptr),
      resource_container_ptr_(resource_container_ptr),
      tetris_renderer_{resource_container_ptr},
      current_tetromino_(
          TetrominoGenerator{}.Generate(next_tetromino_.GetNext())) {}

bool TetrisScene::Update() {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kW) == 1) {
    next_tetromino_.Next();
  }
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kLeft) == 1) {
    tetromino_x_--;
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kRight) == 1) {
    tetromino_x_++;
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kDown) == 1) {
    tetromino_y_++;
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    tetromino_y_--;
  }

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kA) == 1) {
    current_tetromino_.LeftRotate();
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kD) == 1) {
    current_tetromino_.RightRotate();
  }
  return true;
}

void TetrisScene::Draw() const {
  tetris_renderer_.Draw(tetris_field_, GameConst::kResolutionX / 2,
                        GameConst::kResolutionY / 2, current_tetromino_,
                        tetromino_x_, tetromino_y_);
}

void TetrisScene::OnStart(const SceneChangeParameter& parameter) {}

void TetrisScene::OnReturnFromOtherScene(
    const SceneChangeParameter& parameter) {}

}  // namespace mytetris
