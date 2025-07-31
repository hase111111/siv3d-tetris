
//! @file scene_change_listener.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_change_listener.h"

#include "dxlib_assert.h"

namespace mytetris {

void SceneChangeListener::requestAddScene(
    const SceneName scene_name, const SceneChangeParameter& parameter) {
  // ���N�G�X�g��ݒ肷��D
  has_request_ = true;
  request_type_ = RequestType::kAddScene;

  // �p�����[�^��ݒ肷��D
  scene_name_ = scene_name;
  parameter_ = parameter;
}

void SceneChangeListener::requestDeleteScene(
    const int delete_num, const SceneChangeParameter& parameter) {
  // ���N�G�X�g��ݒ肷��D
  has_request_ = true;
  request_type_ = RequestType::kDeleteScene;

  // �p�����[�^��ݒ肷��D
  parameter_ = parameter;
  delete_num_ = delete_num;
}

void SceneChangeListener::requestDeleteAllScene() {
  // ���N�G�X�g��ݒ肷��D
  has_request_ = true;
  request_type_ = RequestType::kDeleteAllScene;
}

bool SceneChangeListener::hasRequest() const { return has_request_; }

SceneChangeListener::RequestType SceneChangeListener::receiveRequest(
    SceneName* const scene_name, SceneChangeParameter* const parameter,
    int* const delete_num) {
  // ������ null�łȂ����`�F�b�N����D
  ASSERT_NOT_NULL_PTR(scene_name);
  ASSERT_NOT_NULL_PTR(parameter);
  ASSERT_NOT_NULL_PTR(delete_num);

  // �璷�����CC6011�x����}�����邽�߂̏���
  if (scene_name == nullptr || parameter == nullptr || delete_num == nullptr) {
    return RequestType::kNone;
  }

  // ���N�G�X�g���Ȃ��ꍇ�͉������Ȃ��D
  if (!has_request_) {
    return RequestType::kNone;
  }

  // ���N�G�X�g���󂯎��D
  *scene_name = scene_name_;

  *parameter = parameter_;

  *delete_num = delete_num_;

  RequestType ret = request_type_;

  // ���N�G�X�g�����Z�b�g����D
  has_request_ = false;
  request_type_ = RequestType::kNone;

  return ret;
}

}  // namespace mytetris
