
//! @file pause_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "font_view.h"
#include "key_event_handler.h"
#include "resource_container.h"

namespace mytetris {

class PauseRenderer final {
 public:
  explicit PauseRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr);
  ~PauseRenderer() = default;

  void Draw(bool is_paused) const;

 private:
  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
  const FontView font_view_;
  const FontView font_view_small_;
};

}  // namespace mytetris
