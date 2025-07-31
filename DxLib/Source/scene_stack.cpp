
//! @file scene_stack.cpp
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_stack.h"

#include <utility>

#include "dxlib_assert.h"

namespace mytetris {

SceneStack::SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr)
    : scene_creator_ptr_(std::move(scene_creator_ptr)),
      initial_scene_name_(SceneName::kDebug) {
  initializeScene();
}

bool SceneStack::updateTopScene() {
  ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

  return scene_ptr_stack_.top()->update();
}

void SceneStack::drawTopScene() const {
  ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

  scene_ptr_stack_.top()->draw();
}

void SceneStack::addNewScene(const SceneName scene_name,
                             const SceneChangeParameter& parameter) {
  auto new_scene_ptr = scene_creator_ptr_->createScene(scene_name);

  new_scene_ptr->onStart(parameter);  // �p�����[�^��n���āC�������������s���D

  scene_ptr_stack_.push(std::move(new_scene_ptr));
}

void SceneStack::deleteNowScene(const int delete_num,
                                const SceneChangeParameter& parameter) {
  ASSERT(delete_num <= scene_ptr_stack_.size(),
         "The number of scenes to delete is invalid.");

  // �����̐������V�[�����폜����D
  for (int i = 0; i < delete_num; ++i) {
    scene_ptr_stack_.pop();
  }

  if (scene_ptr_stack_.empty()) {
    // �V�[�����Ȃ��Ȃ����ꍇ�́C�����V�[�����ēx��������D
    initializeScene(parameter);

    return;
  }

  // �폜��̃V�[���ɑ΂��āC�����̃p�����[�^��n���āC�������������s���D
  scene_ptr_stack_.top()->onReturnFromOtherScene(parameter);
}

void SceneStack::deleteAllScene() {
  // �V�[����S�č폜����D
  while (!scene_ptr_stack_.empty()) {
    scene_ptr_stack_.pop();
  }

  // �����V�[�����ēx��������D
  initializeScene();
}

void SceneStack::initializeScene(const SceneChangeParameter& parameter) {
  auto first_scene_ptr = scene_creator_ptr_->createScene(initial_scene_name_);

  // ��̃p�����[�^��n���āC�������������s���D
  first_scene_ptr->onStart(parameter);

  scene_ptr_stack_.push(std::move(first_scene_ptr));
}

}  // namespace mytetris
