
#pragma once

namespace mytetris {

struct GameSettingRecord final {
  int window_width{1280};
  int window_height{720};

  bool is_full_screen{false};

  //! @brief �����L�[�������������Ƃ��C�A���I�ɓ����n�߂�܂ł̒x������.
  int delayed_auto_shift_{5};

  //! @brief �����L�[�������������Ƃ��C�A���I�ɓ�������.
  int auto_repeat_rate_{5};

  bool allow_hold{true};
  bool display_ghost_tetromino{true};
  bool hard_drop_lock{true};
  bool soft_drop_lock{false};

  int sound_volume{100};
  int bgm_volume{100};
};

}  // namespace mytetris
