
//! @file render_util.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "render_util.h"

#include <DxLib.h>

namespace mytetris {

void DrawRect(const float left, const float top, const float right,
              const float bottom, const unsigned int color, const bool fill) {
  if (fill) {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, TRUE);
  } else {
    DrawBox(static_cast<int>(left), static_cast<int>(top),
            static_cast<int>(right), static_cast<int>(bottom), color, FALSE);
  }
}

}  // namespace mytetris
