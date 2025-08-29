
//! @file scene_change_listener.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "scene_change_listener.h"

namespace mytetris {

void SceneChangeListener::RequestAddScene(
    const SceneName scene_name, const SceneChangeParameter& parameter) {
  // リクエストを設定する．
  request_type_ = RequestType::kAddScene;

  // パラメータを設定する．
  scene_name_ = scene_name;
  parameter_ = parameter;
}

void SceneChangeListener::RequestDeleteScene(
    const int delete_num, const SceneChangeParameter& parameter) {
  // リクエストを設定する．
  request_type_ = RequestType::kDeleteScene;

  // パラメータを設定する．
  parameter_ = parameter;
  delete_num_ = delete_num;
}

void SceneChangeListener::RequestDeleteAllScene() {
  // リクエストを設定する．
  request_type_ = RequestType::kDeleteAllScene;
}

std::tuple<SceneChangeListener::RequestType, SceneName, SceneChangeParameter,
           int>
SceneChangeListener::ReceiveRequest() {
  RequestType ret = request_type_;
  request_type_ = RequestType::kNone;  // リセット.
  return std::make_tuple(ret, scene_name_, parameter_, delete_num_);
}

}  // namespace mytetris
