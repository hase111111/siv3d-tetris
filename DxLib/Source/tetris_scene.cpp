
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
      next_tetromino_{},
      tetris_field_ptr_(std::make_shared<TetrisField>()),
      tetromino_ptr_(std::make_shared<Tetromino>(next_tetromino_.GetNext())),
      tetris_input_handler_ptr_(std::make_unique<TetrisInputHandler>(
          dxlib_keyboard_ptr_, tetris_field_ptr_, tetromino_ptr_)) {}

bool TetrisScene::Update() {
  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kW) == 1) {
    next_tetromino_.Next();
  }

  const auto [new_x, new_y] =
      tetris_input_handler_ptr_->UpdatePosition(tetromino_x_, tetromino_y_);
  tetromino_x_ = new_x;
  tetromino_y_ = new_y;

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kDown) == 1) {
    tetromino_y_++;
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    tetromino_y_--;
  }

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kA) == 1) {
    tetromino_ptr_->LeftRotate();
  } else if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kD) == 1) {
    tetromino_ptr_->RightRotate();
  }

  if (dxlib_keyboard_ptr_->GetPressingCount(KeyHandle::kS) == 1) {
    tetris_field_ptr_->SetTetromino(*tetromino_ptr_, tetromino_x_,
                                    tetromino_y_);
  }
  return true;
}

void TetrisScene::Draw() const {
  tetris_renderer_.Draw(*tetris_field_ptr_, GameConst::kResolutionX / 2,
                        GameConst::kResolutionY / 2, *tetromino_ptr_,
                        tetromino_x_, tetromino_y_);
}

void TetrisScene::OnStart(const SceneChangeParameter& parameter) {}

void TetrisScene::OnReturnFromOtherScene(
    const SceneChangeParameter& parameter) {}

}  // namespace mytetris
