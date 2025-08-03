
//! @file title_ui.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "texture.h"

namespace mytetris {

class TitleUI final {
 public:
  TitleUI() = default;
  ~TitleUI() = default;
  void Draw() const;
};

}  // namespace mytetris
