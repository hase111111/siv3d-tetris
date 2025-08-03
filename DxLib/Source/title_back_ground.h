
//! @file title_back_ground.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include "texture.h"

namespace mytetris {

class TitleBackGround final {
 public:
  TitleBackGround();
  ~TitleBackGround() = default;

  void Draw() const;

 private:
  Texture title_texture_;
};

}  // namespace mytetris
