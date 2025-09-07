
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

  //! @brief シーンのスタックの一番上を実行する．
  //! @return false : メインループを終了する．
  [[nodiscard]] bool UpdateTopScene();

  //! @brief シーンのスタックの一番上を描画する．
  void DrawTopScene() const;

  //! @brief 1番上にシーンを追加する．
  //! @param[in] scene_name シーンの名前．
  //! @param[in] parameter シーンの変更時のパラメータ．
  void AddNewScene(SceneName scene_name, const SceneChangeParameter& parameter);

  //! @brief 1番上のシーンを削除する．
  //! @param[in] delete_num 削除するシーンの数．
  //! @param[in] parameter シーンの変更時のパラメータ．
  void DeleteNowScene(int delete_num, const SceneChangeParameter& parameter);

  void DeleteAndAddNewScene(SceneName scene_name, int delete_num,
                            const SceneChangeParameter& parameter);

  //! @brief シーンを全て削除する．
  void DeleteAllScene();

 private:
  void InitializeScene(
      const SceneChangeParameter& parameter = SceneChangeParameter{});

  //! シーンを格納する配列．スタック．
  std::stack<std::unique_ptr<IScene>> scene_ptr_stack_;

  //!< シーンを生成するクラス．
  const std::unique_ptr<SceneCreator> scene_creator_ptr_;

  const SceneName initial_scene_name_;
};

}  // namespace mytetris
