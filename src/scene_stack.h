
//! @file scene_stack.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <stack>

#include "i_scene.h"
#include "scene_change_parameter.h"
#include "scene_creator.h"
#include "scene_name.h"

namespace mytetris {

class SceneStack final {
 public:
  explicit SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr);

  //! @brief �V�[���̃X�^�b�N�̈�ԏ�����s����D
  //! @return false : ���C�����[�v���I������D
  [[nodiscard]] bool UpdateTopScene();

  //! @brief �V�[���̃X�^�b�N�̈�ԏ��`�悷��D
  void DrawTopScene() const;

  //! @brief 1�ԏ�ɃV�[����ǉ�����D
  //! @param[in] scene_name �V�[���̖��O�D
  //! @param[in] parameter �V�[���̕ύX���̃p�����[�^�D
  void AddNewScene(SceneName scene_name, const SceneChangeParameter& parameter);

  //! @brief 1�ԏ�̃V�[�����폜����D
  //! @param[in] delete_num �폜����V�[���̐��D
  //! @param[in] parameter �V�[���̕ύX���̃p�����[�^�D
  void DeleteNowScene(int delete_num, const SceneChangeParameter& parameter);

  void DeleteAndAddNewScene(SceneName scene_name, int delete_num,
                            const SceneChangeParameter& parameter);

  //! @brief �V�[����S�č폜����D
  void DeleteAllScene();

 private:
  void InitializeScene(
      const SceneChangeParameter& parameter = SceneChangeParameter{});

  //! �V�[�����i�[����z��D�X�^�b�N�D
  std::stack<std::unique_ptr<IScene>> scene_ptr_stack_;

  //!< �V�[���𐶐�����N���X�D
  const std::unique_ptr<SceneCreator> scene_creator_ptr_;

  const SceneName initial_scene_name_;
};

}  // namespace mytetris
