#pragma once

#include "key_handle.h"

namespace mytetris {

struct KeyConfigData {
 public:
  KeyConfigData()
      : move_left_key_(KeyHandle::kLeft),
        move_right_key_(KeyHandle::kRight),
        soft_drop_key_(KeyHandle::kDown),
        hard_drop_key_(KeyHandle::kUp),
        rotate_cw_key_(KeyHandle::kD),
        rotate_ccw_key_(KeyHandle::kA),
        hold_key_(KeyHandle::kW),
        pause_key_(KeyHandle::kP) {}
  KeyHandle move_left_key_;
  KeyHandle move_right_key_;
  KeyHandle soft_drop_key_;
  KeyHandle hard_drop_key_;
  KeyHandle rotate_cw_key_;
  KeyHandle rotate_ccw_key_;
  KeyHandle hold_key_;
  KeyHandle pause_key_;
};

}  // namespace mytetris
