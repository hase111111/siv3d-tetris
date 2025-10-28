//! @file render_anchor.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace mytetris {

//! @enum 描画アンカーの位置を表す列挙型.
enum class RenderAnchor : int {
  TopLeft,
  TopRight,
  BottomLeft,
  BottomRight,
  Center
};

}  // namespace mytetris
