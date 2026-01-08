#include "touch_pad_addon.h"

namespace mytetris {

inline String ToLabel(mytetris::KeyGroup key) {
  using KG = mytetris::KeyGroup;
  switch (key) {
    case KG::kLeft:
      return U"←";
    case KG::kRight:
      return U"→";
    case KG::kUp:
      return U"↑";
    case KG::kDown:
      return U"↓";
    case KG::kRotateCW:
      return U"CW";
    case KG::kRotateCCW:
      return U"CCW";
    case KG::kHold:
      return U"HOLD";
    case KG::kPause:
      return U"PAUSE";
    case KG::kDecide:
      return U"OK";
    case KG::kRestart:
      return U"RESTART";
    case KG::kToMenu:
      return U"BACK";
    case KG::kGameEnd:
      return U"END";
    default:
      return U"?";
  }
}

bool TouchPadAddon::init() {
  const double size = 72;

  // --- 十字キー ---
  const Vec2 dpad{80, Scene::Height() - 200};

  buttons_ = {
      {KeyGroup::kUp,
       {RectF(dpad + Vec2(72, 0), size), ToLabel(KeyGroup::kUp)}},
      {KeyGroup::kDown,
       {RectF(dpad + Vec2(72, 144), size), ToLabel(KeyGroup::kDown)}},
      {KeyGroup::kLeft,
       {RectF(dpad + Vec2(0, 72), size), ToLabel(KeyGroup::kLeft)}},
      {KeyGroup::kRight,
       {RectF(dpad + Vec2(144, 72), size), ToLabel(KeyGroup::kRight)}},

      // --- 操作系 ---
      {KeyGroup::kRotateCW,
       {RectF(Scene::Width() - 260, Scene::Height() - 220, size),
        ToLabel(KeyGroup::kRotateCW)}},
      {KeyGroup::kRotateCCW,
       {RectF(Scene::Width() - 340, Scene::Height() - 160, size),
        ToLabel(KeyGroup::kRotateCCW)}},
      {KeyGroup::kHold,
       {RectF(Scene::Width() - 420, Scene::Height() - 100, size),
        ToLabel(KeyGroup::kHold)}},

      // --- システム系 ---
      {KeyGroup::kDecide,
       {RectF(Scene::Width() - 160, Scene::Height() - 100, size),
        ToLabel(KeyGroup::kDecide)}},
      {KeyGroup::kPause,
       {RectF(Scene::Width() - 160, 40, size), ToLabel(KeyGroup::kPause)}},
      {KeyGroup::kRestart,
       {RectF(40, 40, size * 1.6, size), ToLabel(KeyGroup::kRestart)}},
      {KeyGroup::kToMenu,
       {RectF(40, 120, size * 1.6, size), ToLabel(KeyGroup::kToMenu)}},
      {KeyGroup::kGameEnd,
       {RectF(40, 200, size * 1.6, size), ToLabel(KeyGroup::kGameEnd)}},
  };

  return true;
}

#if defined(__EMSCRIPTEN__)
void TouchPadAddon::update() { updateInput(); }
#else
void TouchPadAddon::postPresent() { updateInput(); }
#endif  // defined(__EMSCRIPTEN__)

void TouchPadAddon::updateInput() {
  for (auto& [_, b] : buttons_) {
    b.pressed = false;
  }

  // for (const auto& touch : Touch::GetTouches()) {
  //   for (auto& [_, b] : buttons_) {
  //     if (b.rect.contains(touch.pos)) {
  //       b.pressed = true;
  //     }
  //   }
  // }

  // PC デバッグ用
  if (MouseL.pressed()) {
    for (auto& [_, b] : buttons_) {
      if (b.rect.mouseOver()) {
        b.pressed = true;
      }
    }
  }
}

void TouchPadAddon::draw() const {
  const Font font{24, Typeface::Bold};

  for (auto& [_, b] : buttons_) {
    const ColorF body =
        b.pressed ? ColorF(0.2, 0.7, 1.0, 0.55) : ColorF(0.4, 0.4, 0.4, 0.35);

    b.rect.rounded(12).draw(body);

    font(b.label).drawAt(b.rect.center(), Palette::White);
  }
}

bool TouchPadAddon::pressed(KeyGroup key) const {
  if (auto it = buttons_.find(key); it != buttons_.end()) {
    return it->second.pressed;
  }
  return false;
}

}  // namespace mytetris
