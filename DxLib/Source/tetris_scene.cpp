
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
      next_tetromino_ptr_(std::make_shared<NextTetromino>()),
      tetris_field_ptr_(std::make_shared<TetrisField>()),
      tetromino_ptr_(
          std::make_shared<Tetromino>(next_tetromino_ptr_->GetNext())),
      tetris_updater_ptr_(std::make_unique<TetrisUpdater>(
          dxlib_keyboard_ptr_, tetris_field_ptr_, tetromino_ptr_,
          next_tetromino_ptr_)),
      tetris_renderer_{resource_container_ptr, tetris_field_ptr_,
                       tetromino_ptr_} {
  next_tetromino_ptr_->Next();
}

bool TetrisScene::Update() {
  tetris_updater_ptr_->Update();

  return true;
}

void TetrisScene::Draw() const {
  const auto [tetromino_x, tetromino_y] = tetris_updater_ptr_->GetPosition();
  tetris_renderer_.Draw(
      GameConst::kResolutionX / 2,
      GameConst::kResolutionY / 2 -
          static_cast<int>(tetris_renderer_.GetBlockSize() * 1.5f),
      tetromino_x, tetromino_y);
}

void TetrisScene::OnStart(const SceneChangeParameter&) {}

void TetrisScene::OnReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace mytetris
