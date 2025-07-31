
//! @file scene_change_listener.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <tuple>

#include "scene_change_parameter.h"
#include "scene_name.h"

namespace mytetris {

class SceneChangeListener final {
 public:
  enum class RequestType { kNone, kAddScene, kDeleteScene, kDeleteAllScene };

  //! @brief �V�[���̒ǉ������N�G�X�g����D
  //! @param[in] scene_name �V�[�����D
  //! @param[in] parameter �p�����[�^�D
  void RequestAddScene(SceneName scene_name,
                       const SceneChangeParameter& parameter);

  //! @brief �V�[���̍폜�����N�G�X�g����D
  //! @param[in] delete_num �폜����V�[���̐��D
  //! @param[in] parameter �p�����[�^�D
  void RequestDeleteScene(int delete_num,
                          const SceneChangeParameter& parameter);

  //! @brief �S�ẴV�[���̍폜�����N�G�X�g����D
  void RequestDeleteAllScene();

  //! @brief ���N�G�X�g�����邩�ǂ�����Ԃ��D
  [[nodiscard]] inline bool HasRequest() const {
    return request_type_ != RequestType::kNone;
  }

  //! @brief ���N�G�X�g���󂯎��D
  //! �󂯎������C���N�G�X�g�̓��Z�b�g�����D
  //! ���N�G�X�g���Ȃ��ꍇ�͉������Ȃ��D
  //! @return
  //! ���N�G�X�g�̎�ށC�V�[�����C�p�����[�^�C�폜����V�[���̐��̃^�v���D
  [[nodiscard]]
  std::tuple<RequestType, SceneName, SceneChangeParameter, int>
  ReceiveRequest();

 private:
  SceneName scene_name_{SceneName::kTitle};
  SceneChangeParameter parameter_{};
  int delete_num_{0};

  RequestType request_type_{RequestType::kNone};
};

}  // namespace mytetris
