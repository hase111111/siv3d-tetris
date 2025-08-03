
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
  TitleBackGround(int window_size_x, int window_size_y);
  ~TitleBackGround() = default;

  void Draw() const;

 private:
  const Texture title_texture_;
  const Texture wall_texture_;
  const int window_size_x_;
  const int window_size_y_;
  const float wall_ex_rate_{2.0f};
};

}  // namespace mytetris
