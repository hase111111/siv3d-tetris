
//! @file game_main_loop.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "game_main_loop.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#endif  // defined DXLIB_COMPILE

#include <format>
#include <utility>

#include "my_assert.h"
#include "resource_container.h"
#include "texture.h"

namespace mytetris {

GameMainLoop::GameMainLoop(
    const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr)
    : key_event_handler_ptr_(std::make_shared<KeyEventHandler>()),
      fps_controller_ptr_(std::make_shared<FpsController>(60)),
      game_setting_record_ptr_(game_setting_record_ptr),
      scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
      scene_stack_ptr_(InitializeSceneStack()),
      scene_change_executer_{scene_change_listener_ptr_, scene_stack_ptr_} {
  // NULLチェック．
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(scene_stack_ptr_);
}

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
  if (!fps_controller_ptr_->SkipDrawScene()) {
#if defined DXLIB_COMPILE
    // スクリーンを消す．
    if (DxLib::ClearDrawScreen() != 0) {
      return false;
    }
#endif  // defined DXLIB_COMPILE

    // 描画する．
    scene_stack_ptr_->DrawTopScene();

#if defined DXLIB_COMPILE
    // スクリーンに表示する．
    if (DxLib::ScreenFlip() != 0) {
      return false;
    }
#endif  // defined DXLIB_COMPILE
  }

  // FPSを調整するための処理．
  fps_controller_ptr_->Wait();

  // シーンの変更を実行する．
  scene_change_executer_.Execute();

  return true;
}

std::shared_ptr<SceneStack> GameMainLoop::InitializeSceneStack() const {
  // NULLチェック．
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
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
    resource_container->RegisterTexture(std::format("block_{}.png", i),
                                        std::move(tetromino[i]));
  }
#elif defined SIV3D_COMPILE
  for (int i = 0; i < 16; ++i) {
    resource_container->RegisterTexture(
        std::format("block_{}.png", i),
        std::make_unique<Texture>(
            std::format("dat/img/for_siv3d/block_{}.png", i)));
  }
#endif

  resource_container->RegisterFont(
      "default",
      std::move(std::make_unique<Font>("dat/font/JK-Maru-Gothic-M.otf", 40)));
  resource_container->RegisterFont(
      "small",
      std::move(std::make_unique<Font>("dat/font/JK-Maru-Gothic-M_.otf", 20)));

  auto scene_creator_ptr = std::make_unique<SceneCreator>(
      scene_change_listener_ptr_, fps_controller_ptr_, key_event_handler_ptr_,
      resource_container, game_setting_record_ptr_);

  auto scene_stack_ptr =
      std::make_shared<SceneStack>(std::move(scene_creator_ptr));

  return scene_stack_ptr;
}

}  // namespace mytetris
