#pragma once

#if defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

#include <Siv3D.hpp>

#include "key_group.h"

namespace mytetris {

class TouchPadAddon final : public IAddon {
  struct Button final {
    RectF rect;
    String label;
    int pressed_cnt{0};
  };

 public:
  TouchPadAddon() { Init(); };

#if defined(__EMSCRIPTEN__)
  bool update() override;
#else
  void postPresent() override;
#endif  // defined(__EMSCRIPTEN__)

  void draw() const override;

  static int pressedCount(KeyGroup key);

 private:
  void Init();
  void updateInput();

  static HashTable<KeyGroup, Button> buttons_;

  static bool is_active_;

  Array<double> touch_times_;

  RectF deactivate_rect_{};
};

}  // namespace mytetris

#endif  // defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
