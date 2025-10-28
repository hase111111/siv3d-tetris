
//! @file scene_stack.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_stack.h"

#include <utility>

#include "my_assert.h"

namespace mytetris {

SceneStack::SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr)
    : scene_creator_ptr_(std::move(scene_creator_ptr)),
      initial_scene_name_(SceneName::kBattle) {
  InitializeScene();
}

bool SceneStack::UpdateTopScene() {
  DEBUG_ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

  return scene_ptr_stack_.top()->Update();
}

void SceneStack::DrawTopScene() const {
  DEBUG_ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

  scene_ptr_stack_.top()->Draw();
}

void SceneStack::AddNewScene(const SceneName scene_name,
                             const SceneChangeParameter& parameter) {
  auto new_scene_ptr = scene_creator_ptr_->CreateScene(scene_name);

  new_scene_ptr->OnStart(parameter);  // �p�����[�^��n���āC�������������s���D

  scene_ptr_stack_.push(std::move(new_scene_ptr));
}

void SceneStack::DeleteNowScene(const int delete_num,
                                const SceneChangeParameter& parameter) {
  DEBUG_ASSERT(delete_num <= scene_ptr_stack_.size(),
               "The number of scenes to delete is invalid.");

  // �����̐������V�[�����폜����D
  for (int i = 0; i < delete_num; ++i) {
    scene_ptr_stack_.pop();
  }

  if (scene_ptr_stack_.empty()) {
    // �V�[�����Ȃ��Ȃ����ꍇ�́C�����V�[�����ēx��������D
    InitializeScene(parameter);

    return;
  }

  // �폜��̃V�[���ɑ΂��āC�����̃p�����[�^��n���āC�������������s���D
  scene_ptr_stack_.top()->OnReturnFromOtherScene(parameter);
}

void SceneStack::DeleteAndAddNewScene(SceneName scene_name, int delete_num,
                                      const SceneChangeParameter& parameter) {
  // �����̐������V�[�����폜����D
  for (int i = 0; i < delete_num; ++i) {
    scene_ptr_stack_.pop();
  }

  auto new_scene_ptr = scene_creator_ptr_->CreateScene(scene_name);

  new_scene_ptr->OnStart(parameter);  // �p�����[�^��n���āC�������������s���D

  scene_ptr_stack_.push(std::move(new_scene_ptr));
}

void SceneStack::DeleteAllScene() {
  // �V�[����S�č폜����D
  while (!scene_ptr_stack_.empty()) {
    scene_ptr_stack_.pop();
  }

  // �����V�[�����ēx��������D
  InitializeScene();
}

void SceneStack::InitializeScene(const SceneChangeParameter& parameter) {
  auto first_scene_ptr = scene_creator_ptr_->CreateScene(initial_scene_name_);

  // ��̃p�����[�^��n���āC�������������s���D
  first_scene_ptr->OnStart(parameter);

  scene_ptr_stack_.push(std::move(first_scene_ptr));
}

}  // namespace mytetris
