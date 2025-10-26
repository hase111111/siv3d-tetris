
#pragma once

namespace mytetris {

struct GameSettingRecord final {
  int window_width{1280};
  int window_height{720};

  bool is_full_screen{false};

  //! @brief 方向キーを押し続けたとき，連続的に動き始めるまでの遅延時間.
  int delayed_auto_shift_{5};

  //! @brief 方向キーを押し続けたとき，連続的に動く速さ.
  int auto_repeat_rate_{5};

  bool allow_hold{true};
  bool display_ghost_tetromino{true};
  bool hard_drop_lock{true};
  bool soft_drop_lock{false};

  int sound_volume{100};
  int bgm_volume{100};
};

}  // namespace mytetris
