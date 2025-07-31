
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

  //! @brief シーンの追加をリクエストする．
  //! @param[in] scene_name シーン名．
  //! @param[in] parameter パラメータ．
  void requestAddScene(SceneName scene_name,
                       const SceneChangeParameter& parameter);

  //! @brief シーンの削除をリクエストする．
  //! @param[in] delete_num 削除するシーンの数．
  //! @param[in] parameter パラメータ．
  void requestDeleteScene(int delete_num,
                          const SceneChangeParameter& parameter);

  //! @brief 全てのシーンの削除をリクエストする．
  void requestDeleteAllScene();

  //! @brief リクエストがあるかどうかを返す．
  [[nodiscard]] bool hasRequest() const;

  //! @brief リクエストを受け取る．
  //! 受け取った後，リクエストはリセットされる．
  //! リクエストがない場合は何もしない．
  //! @param[out] scene_name シーン名．
  //! @param[out] parameter パラメータ．
  //! @param[out] delete_num 削除するシーンの数．
  //! @return リクエストの種類．
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
