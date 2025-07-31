
//! @file scene_change_listener.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "scene_change_parameter.h"
#include "scene_name.h"

namespace mytetris {

class SceneChangeListener final {
 public:
  enum class RequestType { kNone, kAddScene, kDeleteScene, kDeleteAllScene };

  //! @brief �V�[���̒ǉ������N�G�X�g����D
  //! @param[in] scene_name �V�[�����D
  //! @param[in] parameter �p�����[�^�D
  void requestAddScene(SceneName scene_name,
                       const SceneChangeParameter& parameter);

  //! @brief �V�[���̍폜�����N�G�X�g����D
  //! @param[in] delete_num �폜����V�[���̐��D
  //! @param[in] parameter �p�����[�^�D
  void requestDeleteScene(int delete_num,
                          const SceneChangeParameter& parameter);

  //! @brief �S�ẴV�[���̍폜�����N�G�X�g����D
  void requestDeleteAllScene();

  //! @brief ���N�G�X�g�����邩�ǂ�����Ԃ��D
  [[nodiscard]] bool hasRequest() const;

  //! @brief ���N�G�X�g���󂯎��D
  //! �󂯎������C���N�G�X�g�̓��Z�b�g�����D
  //! ���N�G�X�g���Ȃ��ꍇ�͉������Ȃ��D
  //! @param[out] scene_name �V�[�����D
  //! @param[out] parameter �p�����[�^�D
  //! @param[out] delete_num �폜����V�[���̐��D
  //! @return ���N�G�X�g�̎�ށD
  RequestType receiveRequest(SceneName* const scene_name,
                             SceneChangeParameter* const parameter,
                             int* const delete_num);

 private:
  SceneName scene_name_{SceneName::kTitle};
  SceneChangeParameter parameter_{};
  int delete_num_{0};

  bool has_request_{false};
  RequestType request_type_{RequestType::kNone};
};

}  // namespace mytetris
