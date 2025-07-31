
//! @file i_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "scene_change_parameter.h"

namespace mytetris {

//! @brief �V�[���̃C���^�[�t�F�[�X�D
class IScene {
 public:
  virtual ~IScene() = default;

  //! @brief �V�[���̍X�V�����D
  //! @return ���C�����[�v�𔲂���Ȃ�� false ��Ԃ��D
  virtual bool update() = 0;

  //! @brief �V�[���̕`�揈���D
  virtual void draw() const = 0;

  //! @brief �V�[�����J�n���ꂽ�Ƃ��ɌĂяo�����֐��D
  //! @param parameter �V�[���ύX���̃p�����[�^�D
  virtual void onStart(const SceneChangeParameter& parameter) = 0;

  //! @brief �ʂ̃V�[������߂��Ă����Ƃ��ɌĂяo�����֐��D
  //! @param parameter �V�[���ύX���̃p�����[�^�D
  virtual void onReturnFromOtherScene(
      const SceneChangeParameter& parameter) = 0;
};

}  // namespace mytetris
