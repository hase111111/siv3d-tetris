
#pragma once

namespace mytetris {

struct GameSettingRecord final {
  int window_width{1280};
  int window_height{720};

  bool is_full_screen{false};

  int sound_volume{100};
  int bgm_volume{100};
};

}  // namespace mytetris
