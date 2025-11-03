#pragma once

#include <string>

namespace mytetris {

class BattleAnnounce final {
 public:
  BattleAnnounce() = default;
  ~BattleAnnounce() = default;

  void SetClearLineAnnounce(int line_num, int combo, bool is_tspin,
                            bool is_btb);

  void Draw(float render_x, float render_y) const;
};

}  // namespace mytetris
