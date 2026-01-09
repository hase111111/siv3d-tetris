//! @file game_main_loop.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "game_main_loop.h"

#if defined(DXLIB_COMPILE)
#include <DxLib.h>
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include <utility>

#include "fps_addon.h"
#include "my_assert.h"
#include "my_format.h"
#include "resource_container.h"
#include "texture.h"
#include "touch_pad_addon.h"

namespace mytetris {

GameMainLoop::GameMainLoop(
    const std::shared_ptr<GameSettingRecord>& game_setting_record_ptr)
    : key_config_data_ptr_(std::make_shared<KeyConfigData>()),
      key_event_handler_ptr_(
          std::make_shared<KeyEventHandler>(key_config_data_ptr_)),
      game_setting_record_ptr_(game_setting_record_ptr),
      scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
      scene_stack_ptr_(InitializeSceneStack()),
      scene_change_executer_{scene_change_listener_ptr_, scene_stack_ptr_} {
  // NULLチェック．
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(scene_stack_ptr_);

#if defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
  // Addon登録.
  s3d::Addon::Register(U"FpsController", std::make_unique<FpsAddon>(60));
  // タッチパッドアドオンを登録.
  s3d::Addon::Register(U"TouchPad", std::make_unique<TouchPadAddon>());
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
}

#if defined(DXLIB_COMPILE)
bool GameMainLoop::Loop() {
  // 入力を取得
  key_event_handler_ptr_->Update();

  // シーンのスタックの一番上を実行する．
  if (!scene_stack_ptr_->UpdateTopScene()) {
    return false;
  }

  ASSERT(Texture::GetCount() - texture_count_ < 1000,
         "A large number of textures are generated in a single frame");
  texture_count_ = Texture::GetCount();

  // 処理が重い場合はここでコマ落ちさせる．
  if (!fps_controller_.SkipDrawScene()) {
    // スクリーンを消す．
    if (DxLib::ClearDrawScreen() != 0) {
      return false;
    }

    // 描画する．
    scene_stack_ptr_->DrawTopScene();

    // スクリーンに表示する．
    if (DxLib::ScreenFlip() != 0) {
      return false;
    }
  }

  // FPSを調整するための処理．
  fps_controller_.Wait();

  // シーンの変更を実行する．
  scene_change_executer_.Execute();

  return true;
}
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
bool GameMainLoop::Loop() {
  // 入力を取得
  key_event_handler_ptr_->Update();

  // シーンのスタックの一番上を実行する．
  if (!scene_stack_ptr_->UpdateTopScene()) {
    return false;
  }

  ASSERT(Texture::GetCount() - texture_count_ < 1000,
         "A large number of textures are generated in a single frame");
  texture_count_ = Texture::GetCount();

  // 処理が重い場合はここでコマ落ちさせる．
  scene_stack_ptr_->DrawTopScene();

  // シーンの変更を実行する．
  scene_change_executer_.Execute();

  return true;
}
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

std::shared_ptr<SceneStack> GameMainLoop::InitializeSceneStack() const {
  // NULLチェック．
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

  const auto resource_container = std::make_shared<ResourceContainer>();
  resource_container->RegisterTexture(
      "title.png", std::move(std::make_unique<Texture>("dat/img/title.png")));
  resource_container->RegisterTexture(
      "wall.png", std::move(std::make_unique<Texture>("dat/img/wall.png")));

#ifdef DXLIB_COMPILE

  auto tetromino = LoadDivideGraph("dat/img/blocks.png", 8, 2, 16, 20, 20);
  for (int i = 0; i < 16; ++i) {
    resource_container->RegisterTexture(nostd::format("block_{}.png", i),
                                        std::move(tetromino[i]));
  }

  resource_container->RegisterFont(
      "default", std::move(std::make_unique<Font>("dat/font/JKGothic40.dft")));
  resource_container->RegisterFont(
      "small", std::move(std::make_unique<Font>("dat/font/JKGothic20.dft")));

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

  for (int i = 0; i < 16; ++i) {
    resource_container->RegisterTexture(
        nostd::format("block_{}.png", i),
        std::make_unique<Texture>(
            nostd::format("dat/img/for_siv3d/block_{}.png", i)));
  }

  resource_container->RegisterFont(
      "default", std::move(std::make_unique<Font>(
                     "dat/font/x10y12pxDonguriDuel.ttf", 40)));
  resource_container->RegisterFont(
      "large", std::move(std::make_unique<Font>(
                   "dat/font/x10y12pxDonguriDuel.ttf", 100)));
  resource_container->RegisterFont(
      "small", std::move(std::make_unique<Font>(
                   "dat/font/x10y12pxDonguriDuel.ttf", 20)));

#endif  // defined DXLIB_COMPILE

  auto scene_creator_ptr = std::make_unique<SceneCreator>(
      scene_change_listener_ptr_, key_event_handler_ptr_, resource_container,
      game_setting_record_ptr_);

  auto scene_stack_ptr =
      std::make_shared<SceneStack>(std::move(scene_creator_ptr));

  return scene_stack_ptr;
}

}  // namespace mytetris
