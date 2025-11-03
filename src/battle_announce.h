#pragma once

#include <string>
#include <vector>

#include "font_view.h"
#include "resource_container.h"
#include "tetris_feild.h"

namespace mytetris {

class BattleAnnounce final {
 public:
  BattleAnnounce(
      const std::shared_ptr<const ResourceContainer>& resource_container,
      const std::shared_ptr<TetrisField>& enemy_field);
  ~BattleAnnounce() = default;

  void SetClearLineAnnounce(int line_num, int combo, bool is_tspin,
                            bool is_btb);

  void Update();

  void Draw(float render_x, float render_y) const;

 private:
  const int animation_duration_ = 120;  // アニメーションの長さ（フレーム数）.
  const std::shared_ptr<TetrisField> enemy_field_ptr_;

  FontView font_view_;
  FontView font_view_large_;
  FontView font_view_small_;
  std::vector<std::string> clear_line_announce_;
  int clear_line_start_time_ = 0;
  int counter_ = 0;
};

}  // namespace mytetris
