
//! @file scene_creator.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "game_setting_record.h"
#include "i_scene.h"
#include "key_event_handler.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "scene_name.h"

namespace mytetris {

//! @brief シーンを生成するクラス．
class SceneCreator final {
 public:
  SceneCreator(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<GameSettingRecord>& game_setting_record_ptr);
  ~SceneCreator() = default;

  //! @brief シーンを生成する．
  //! @param[in] scene_name シーンの名前．
  //! @return 生成したシーン．
  [[nodiscard]] std::unique_ptr<IScene> CreateScene(SceneName scene_name) const;

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;

  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;

  const std::shared_ptr<GameSettingRecord> game_setting_record_ptr_;
};

}  // namespace mytetris
