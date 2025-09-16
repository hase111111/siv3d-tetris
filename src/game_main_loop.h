
//! @file game_main_loop.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "fps_controller.h"
#include "game_setting_record.h"
#include "key_event_handler.h"
#include "scene_change_executer.h"
#include "scene_change_listener.h"
#include "scene_stack.h"

namespace mytetris {

//! @class GameMainLoop
//! @brief ゲームのメインループ内で1フレームごとに行う処理を呼ぶクラス．
class GameMainLoop final {
 public:
  explicit GameMainLoop(
      const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr);
  ~GameMainLoop() = default;

  //! @brief メインループ内で1フレームごとに行う処理を呼ぶ．
  //! @return false := ゲームを終了する．
  bool Loop();

 private:
  [[nodiscard]] std::shared_ptr<SceneStack> InitializeSceneStack() const;

  const std::shared_ptr<KeyEventHandler> key_event_handler_ptr_;

  const std::shared_ptr<const GameSettingRecord> game_setting_record_ptr_;

  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const std::shared_ptr<SceneStack> scene_stack_ptr_;
  SceneChangeExecuter scene_change_executer_;

  FpsController fps_controller_{60};

  int texture_count_{0};
};

}  // namespace mytetris
