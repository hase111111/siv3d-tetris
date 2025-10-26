
//! @file title_ui.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "font_view.h"
#include "key_event_handler.h"
#include "resource_container.h"
#include "scene_change_parameter.h"

namespace mytetris {

class TitleUI final {
 public:
  TitleUI(
      const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::function<void(const SceneChangeParameter&)>& to_game_scene,
      const std::function<void()>& to_setting_scene);
  ~TitleUI() = default;

  bool Update();

  void Draw() const;

 private:
  bool UpdateTitle();
  bool UpdateGameStart();
  bool UpdateSpecialMode();

  void DrawTitle() const;
  void DrawGameStart() const;
  void DrawSpecialMode() const;
  void DrawVersionInfo() const;

  const FontView font_view_40_;
  const FontView font_view_20_;
  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
  const std::vector<std::string> title_items_;
  const std::vector<std::string> game_mode_items_;
  const std::vector<std::string> special_mode_items_;
  const std::function<void(const SceneChangeParameter&)> to_game_scene_;
  const std::function<void()> to_setting_scene_;

  std::string lower_announcement_;
  int counter_{0};
  int mode_index_{0};
  int selected_index_{0};
};

}  // namespace mytetris
