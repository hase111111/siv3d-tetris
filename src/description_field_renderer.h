
//! @file description_field_renderer.h
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
#include "tetris_timer.h"
#include "texture_view.h"

namespace mytetris {

class DescriptionFieldRenderer final {
 public:
  DescriptionFieldRenderer(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr);
  ~DescriptionFieldRenderer() = default;

  void Update();

  void Draw(int x, int y) const;

 private:
  std::string GetString() const;

  const std::shared_ptr<const KeyEventHandler> key_ptr_;
  const std::shared_ptr<const TetrisTimer> tetris_timer_ptr_;
  const FontView font_view_;
  const TextureView wall_texture_;
  const int max_history_size_{20};

  std::vector<std::string> input_history_;
  int input_counter{0};
  int hard_drop_counter{0};
};

}  // namespace mytetris
