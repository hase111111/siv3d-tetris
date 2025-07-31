
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

  //! @brief シーンの追加をリクエストする．
  //! @param[in] scene_name シーン名．
  //! @param[in] parameter パラメータ．
  void RequestAddScene(SceneName scene_name,
                       const SceneChangeParameter& parameter);

  //! @brief シーンの削除をリクエストする．
  //! @param[in] delete_num 削除するシーンの数．
  //! @param[in] parameter パラメータ．
  void RequestDeleteScene(int delete_num,
                          const SceneChangeParameter& parameter);

  //! @brief 全てのシーンの削除をリクエストする．
  void RequestDeleteAllScene();

  //! @brief リクエストがあるかどうかを返す．
  [[nodiscard]] inline bool HasRequest() const {
    return request_type_ != RequestType::kNone;
  }

  //! @brief リクエストを受け取る．
  //! 受け取った後，リクエストはリセットされる．
  //! リクエストがない場合は何もしない．
  //! @return
  //! リクエストの種類，シーン名，パラメータ，削除するシーンの数のタプル．
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
