
//! @file i_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "scene_change_parameter.h"

namespace mytetris {

//! @brief シーンのインターフェース．
class IScene {
 public:
  virtual ~IScene() = default;

  //! @brief シーンの更新処理．
  //! @return メインループを抜けるならば false を返す．
  virtual bool update() = 0;

  //! @brief シーンの描画処理．
  virtual void draw() const = 0;

  //! @brief シーンが開始されたときに呼び出される関数．
  //! @param parameter シーン変更時のパラメータ．
  virtual void onStart(const SceneChangeParameter& parameter) = 0;

  //! @brief 別のシーンから戻ってきたときに呼び出される関数．
  //! @param parameter シーン変更時のパラメータ．
  virtual void onReturnFromOtherScene(
      const SceneChangeParameter& parameter) = 0;
};

}  // namespace mytetris
