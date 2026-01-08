#pragma once

#include <Siv3D.hpp>

#include "key_group.h"

namespace mytetris {

class TouchPadAddon final : public IAddon {
  struct Button final {
    RectF rect;
    String label;
    bool pressed = false;
  };

 public:
#if defined(__EMSCRIPTEN__)
  bool update() override;
#else
  void postPresent() override;
#endif  // defined(__EMSCRIPTEN__)

  void draw() const override;

  bool pressed(KeyGroup key) const;

  bool init();

 private:
  void updateInput();

  HashTable<KeyGroup, Button> buttons_;
};

}  // namespace mytetris
