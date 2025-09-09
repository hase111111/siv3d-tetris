
//! @file score_board_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>

#include "drop_count.h"
#include "font_view.h"
#include "resource_container.h"
#include "tetris_game_mode.h"
#include "tetris_level.h"
#include "tetris_timer.h"
#include "texture_view.h"

namespace mytetris {

class ScoreBoardRenderer final {
 public:
  ScoreBoardRenderer(
      const std::shared_ptr<TetrisTimer>& tetris_timer_ptr,
      const std::shared_ptr<TetrisLevel>& tetris_level_ptr_,
      const std::shared_ptr<DropCount>& drop_count_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~ScoreBoardRenderer() = default;

  inline void SetGameMode(const TetrisGameMode game_mode) {
    tetris_game_mode_ = game_mode;
  }

  void Draw(int x, int y) const;

 private:
  std::string GetString() const;

  const std::shared_ptr<TetrisTimer> tetris_timer_ptr_;
  const std::shared_ptr<TetrisLevel> tetris_level_ptr_;
  const std::shared_ptr<DropCount> drop_count_ptr_;
  TetrisGameMode tetris_game_mode_{};
  FontView font_view_;
  TextureView wall_texture_;
};

}  // namespace mytetris
