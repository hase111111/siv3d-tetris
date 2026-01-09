#if defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

#include "touch_pad_addon.h"

#if defined(__EMSCRIPTEN__)
#include "siv3d_touch.h"
#endif  // defined(__EMSCRIPTEN__)

namespace mytetris {

// 初期化.
HashTable<KeyGroup, TouchPadAddon::Button> TouchPadAddon::buttons_{};

bool TouchPadAddon::is_active_{false};

static inline String ToLabel(mytetris::KeyGroup key) {
  using KG = mytetris::KeyGroup;
  switch (key) {
    case KG::kLeft:
      return U"<";
    case KG::kRight:
      return U">";
    case KG::kUp:
      return U"^";
    case KG::kDown:
      return U"v";
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
      return U"TO MENU";
    case KG::kGameEnd:
      return U"GAME END";
    default:
      return U"x";
  }
}

void TouchPadAddon::Init() {
  const double size = 120;

  // 十字キー
  const Vec2 joy_pad{Scene::Width() - size * 3.5, Scene::Height() - size * 3.5};

  // 回転操作系ボタン
  const Vec2 operation_pad{size * 1.2, Scene::Height() - size * 2.5};

  buttons_ = {
      {KeyGroup::kUp,
       {RectF{joy_pad + Vec2{size * 1.05, 0}, size}, ToLabel(KeyGroup::kUp)}},
      {KeyGroup::kDown,
       {RectF{joy_pad + Vec2{size * 1.05, size * 2.1}, size},
        ToLabel(KeyGroup::kDown)}},
      {KeyGroup::kLeft,
       {RectF{joy_pad + Vec2{0, size * 1.05}, size}, ToLabel(KeyGroup::kLeft)}},
      {KeyGroup::kRight,
       {RectF{joy_pad + Vec2{size * 2.1, size * 1.05}, size},
        ToLabel(KeyGroup::kRight)}},

      // --- 操作系 ---
      {KeyGroup::kRotateCW,
       {RectF{operation_pad + Vec2{size * 1.05, 0}, size},
        ToLabel(KeyGroup::kRotateCW)}},
      {KeyGroup::kRotateCCW,
       {RectF{operation_pad - Vec2{size * 1.05, 0}, size},
        ToLabel(KeyGroup::kRotateCCW)}},
      {KeyGroup::kHold,
       {RectF{operation_pad - Vec2{0, size * 1.05}, size},
        ToLabel(KeyGroup::kHold)}},

      // --- システム系 ---
      {KeyGroup::kDecide,
       {RectF{joy_pad + Vec2{size * 1.05, size * 1.05}, size},
        ToLabel(KeyGroup::kDecide)}},
      {KeyGroup::kPause,
       {RectF{Scene::Width() - 160, 10, size}, ToLabel(KeyGroup::kPause)}},
      {KeyGroup::kRestart,
       {RectF{40, size * 0.1, size * 1.6, size}, ToLabel(KeyGroup::kRestart)}},
      {KeyGroup::kToMenu,
       {RectF{40, size * 1.2, size * 1.6, size}, ToLabel(KeyGroup::kToMenu)}},
  };

  deactivate_rect_ = RectF{Scene::Width() - size * 2.5, 10, size};

  s3d::FontAsset::Register(U"pad", FontMethod::MSDF, 40,
                           U"dat/font/x10y12pxDonguriDuel.ttf");

  return;
}

#if defined(__EMSCRIPTEN__)
bool TouchPadAddon::update() {
  updateInput();
  return true;
}
#else
void TouchPadAddon::postPresent() { updateInput(); }
#endif  // defined(__EMSCRIPTEN__)

void TouchPadAddon::updateInput() {
  if (!is_active_) {
    // 直近3回のタッチ時間を記録する.
    if (MouseL.down()) {
      touch_times_.push_back(Scene::Time());
      if (3 < touch_times_.size()) {
        touch_times_.erase(touch_times_.begin());
      }
    }

    // 1秒以内に3回タッチされていたら有効化する.
    if (touch_times_.size() == 3 &&
        (touch_times_.back() - touch_times_.front()) < 1.0) {
      is_active_ = true;
    }
    return;
  }

#if defined(__EMSCRIPTEN__)
  // タッチ情報を取得.
  auto touches = GetMyTouches();
  const auto mouse_pos = Cursor::PosF();
  if (MouseL.pressed()) {
    touches.push_back(TouchInfo{-1, mouse_pos});
  }

  // 非アクティブ化ボタンが押されたら非アクティブ化.
  bool deactivate_pressed = false;
  for (const auto& t : touches) {
    if (deactivate_rect_.contains(t.pos)) {
      deactivate_pressed = true;
      break;
    }
  }
  if (deactivate_pressed) {
    is_active_ = false;
    touch_times_.clear();
    for (auto& [_, b] : buttons_) {
      b.pressed_cnt = 0;
    }
    return;
  }

  // 押されているフレーム数をカウントする方式に変更.
  for (auto& [_, b] : buttons_) {
    bool is_pressed = false;
    for (const auto& t : touches) {
      if (b.rect.contains(t.pos)) {
        is_pressed = true;
        break;
      }
    }
    if (is_pressed) {
      if (b.pressed_cnt == 0) {
        b.pressed_cnt = 1;
      } else {
        ++b.pressed_cnt;
      }
    } else {
      b.pressed_cnt = 0;
    }
  }
#else
  // 押されているフレーム数をカウントする方式に変更.
  for (auto& [_, b] : buttons_) {
    if (b.rect.leftClicked()) {
      b.pressed_cnt = 1;
    } else if (0 < b.pressed_cnt && b.rect.leftPressed()) {
      ++b.pressed_cnt;
    } else {
      b.pressed_cnt = 0;
    }
  }
#endif  // defined(__EMSCRIPTEN__)
}

void TouchPadAddon::draw() const {
  if (!is_active_) {
    return;
  }

  for (auto& [_, b] : buttons_) {
    const ColorF body = b.pressed_cnt > 0 ? ColorF{1.0, 0.5, 0.5, 0.6}
                                          : ColorF{1.0, 0.5, 0.5, 0.9};

    b.rect.rounded(12).draw(body);

    s3d::FontAsset(U"pad")(b.label).drawAt(b.rect.center(),
                                           s3d::Palette::Aquamarine);
  }

  deactivate_rect_.rounded(12).draw(ColorF{1.0, 0.5, 0.5, 0.9});
  s3d::FontAsset(U"pad")(U"X").drawAt(80, deactivate_rect_.center(),
                                      s3d::Palette::Aquamarine);
}

int TouchPadAddon::pressedCount(KeyGroup key) {
  if (!is_active_) {
    return 0;
  }

  if (auto it = buttons_.find(key); it != buttons_.end()) {
    return it->second.pressed_cnt;
  }
  return 0;
}

}  // namespace mytetris

#endif  // defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
