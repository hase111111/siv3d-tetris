#pragma once

#include "key_group.h"
#include "key_handle.h"

namespace mytetris {

struct KeyConfigData final {
  KeyConfigData()
      : move_left_key(KeyHandle::kLeft),
        move_right_key(KeyHandle::kRight),
        soft_drop_key(KeyHandle::kDown),
        hard_drop_key(KeyHandle::kUp),
        rotate_cw_key(KeyHandle::kD),
        rotate_ccw_key(KeyHandle::kA),
        hold_key(KeyHandle::kW),
        decide_key(KeyHandle::kZ),
        pause_key(KeyHandle::kP),
        restart_key(KeyHandle::kR),
        game_end_key(KeyHandle::kEscape) {}

  KeyHandle Map(KeyGroup key_group) const;

  KeyHandle move_left_key;
  KeyHandle move_right_key;
  KeyHandle soft_drop_key;
  KeyHandle hard_drop_key;
  KeyHandle rotate_cw_key;
  KeyHandle rotate_ccw_key;
  KeyHandle hold_key;
  KeyHandle decide_key;
  KeyHandle pause_key;
  KeyHandle restart_key;
  KeyHandle game_end_key;
};

}  // namespace mytetris
