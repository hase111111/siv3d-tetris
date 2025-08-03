
//! @file game_main_loop.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "game_main_loop.h"

#include <DxLib.h>

#include <format>
#include <utility>

#include "dxlib_assert.h"
#include "resource_container.h"
#include "texture.h"

namespace mytetris {

GameMainLoop::GameMainLoop(
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : dxlib_keyboard_ptr_(std::make_shared<DxLibKeyboard>()),
      fps_controller_ptr_(std::make_shared<FpsController>(60)),
      game_setting_record_ptr_(game_setting_record_ptr),
      scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
      scene_stack_ptr_(InitializeSceneStack()),
      scene_change_executer_{scene_change_listener_ptr_, scene_stack_ptr_} {
  // NULL�`�F�b�N�D
  ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr_);
  ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
  ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  ASSERT_NOT_NULL_PTR(scene_stack_ptr_);
}

bool GameMainLoop::Loop() {
  // ���͂��擾
  dxlib_keyboard_ptr_->Update();

  // �V�[���̃X�^�b�N�̈�ԏ�����s����D
  if (!scene_stack_ptr_->UpdateTopScene()) {
    return false;
  }

  ASSERT(Texture::GetCount() - texture_count_ < 1000,
         "A large number of textures are generated in a single frame");
  texture_count_ = Texture::GetCount();

  // �������d���ꍇ�͂����ŃR�}����������D
  if (!fps_controller_ptr_->SkipDrawScene()) {
    // �X�N���[���������D
    if (DxLib::ClearDrawScreen() != 0) {
      return false;
    }

    // �`�悷��D
    scene_stack_ptr_->DrawTopScene();

    // �X�N���[���ɕ\������D
    if (DxLib::ScreenFlip() != 0) {
      return false;
    }
  }

  // FPS�𒲐����邽�߂̏����D
  fps_controller_ptr_->Wait();

  // �V�[���̕ύX�����s����D
  scene_change_executer_.Execute();

  return true;
}

std::shared_ptr<SceneStack> GameMainLoop::InitializeSceneStack() const {
  // NULL�`�F�b�N�D
  ASSERT_NOT_NULL_PTR(dxlib_keyboard_ptr_);
  ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
  ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
  ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

  const auto dxlib_resource_loader_ptr = std::make_shared<ResourceContainer>();

  auto scene_creator_ptr = std::make_unique<SceneCreator>(
      scene_change_listener_ptr_, fps_controller_ptr_, dxlib_keyboard_ptr_,
      dxlib_resource_loader_ptr, game_setting_record_ptr_);

  auto scene_stack_ptr =
      std::make_shared<SceneStack>(std::move(scene_creator_ptr));

  return scene_stack_ptr;
}

}  // namespace mytetris
