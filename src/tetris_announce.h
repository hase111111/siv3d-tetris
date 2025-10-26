
//! @file tetris_announce.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "font_view.h"
#include "game_end_checker.h"
#include "resource_container.h"
#include "tetris_feild.h"
#include "tetris_game_mode.h"
#include "tetris_level.h"
#include "tetris_timer.h"

namespace mytetris {

class TetrisAnnounce final {
 public:
  TetrisAnnounce(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const TetrisLevel>& tetris_level_ptr,
      const std::shared_ptr<const TetrisTimer>& tetris_timer_ptr,
      const std::shared_ptr<const GameEndChecker>& game_end_checker_ptr,
      const std::shared_ptr<const TetrisField>& tetris_field_ptr);
  ~TetrisAnnounce() = default;

  inline void SetGameMode(const TetrisGameMode game_mode) {
    game_mode_ = game_mode;
  }

  void SetClearLineAnnounce(int line_num, int combo, bool is_tspin,
                            bool is_btb);

  void Update();

  void Draw(int x, int y) const;

 private:
  const std::shared_ptr<const TetrisLevel> tetris_level_ptr_;
  const std::shared_ptr<const TetrisTimer> tetris_timer_ptr_;
  const std::shared_ptr<const GameEndChecker> game_end_checker_ptr_;
  const std::shared_ptr<const TetrisField> tetris_field_ptr_;
  const FontView font_view_;
  const FontView font_view_small_;
  const int animation_duration_{120};

  TetrisGameMode game_mode_{TetrisGameMode::kEndless};
  std::string announce_text_{""};
  std::string announce_text_small_{""};
  std::vector<std::string> clear_line_announce_{};
  int counter_{0};                //!< アナウンス用カウンター.
  int start_time_{0};             //!< アナウンス開始時のタイマー値.
  int clear_line_start_time_{0};  //!< クリアラインアナウンス開始時のタイマー値.
  int total_clear_lines_{0};      //!< 最後に記録したクリアライン数.
  int timer_count_{0};            //<! 最後に記録したタイマー値.
};

}  // namespace mytetris