
//! @file title_ui.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "font_view.h"
#include "key_event_handler.h"
#include "resource_container.h"

namespace mytetris {

class TitleUI final {
 public:
  TitleUI(
      const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~TitleUI() = default;

  bool Update();

  void Draw() const;

 private:
  bool UpdateTitle();
  bool UpdateGameStart();

  void DrawTitle() const;
  void DrawGameStart() const;

  const FontView font_view_;
  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
  const std::vector<std::string> title_items_;
  const std::vector<std::string> menu_items_;

  int counter_{0};
  int mode_index_{0};
  int selected_index_{0};
};

}  // namespace mytetris
