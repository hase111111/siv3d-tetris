#ifndef SIV3D_TOUCH_H_
#define SIV3D_TOUCH_H_

#if defined(__EMSCRIPTEN__)

#include <Siv3D.hpp>

struct TouchInfo {
  int32 id;
  Vec2 pos;
};

inline Array<TouchInfo> GetMyTouches() {
  Array<TouchInfo> result =
      Array<TouchInfo>(EM_ASM_INT({ return window.myTouches.length; }));

  EM_ASM(
      {
        const touches = window.myTouches;

        for (let i = 0; i < touches.length; i++) {
          const touch = touches[i];
          const touchPtr =
              $0 + i * 24;  // TouchInfo ĚTCYÉśÄ˛Ž

          const adjusted = siv3dAdjustPoint(touch.pageX, touch.pageY);

          setValue(touchPtr, touch.identifier, 'i32');
          setValue(touchPtr + 8, adjusted.x, 'double');
          setValue(touchPtr + 16, adjusted.y, 'double');
        }
      },
      result.data());

  for (auto& touch : result) {
    touch.pos = Scene::ClientToScene(touch.pos);
  }

  return result;
}

#endif  // defined(__EMSCRIPTEN__)

#endif  // SIV3D_TOUCH_H_
