
//! @file title_back_ground.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_back_ground.h"

#include "dxlib_assert.h"

namespace mytetris {

TitleBackGround::TitleBackGround() : title_texture_("dat/img/title.png") {
  ASSERT(title_texture_.IsValid(), "Failed to load title texture.");
}

void TitleBackGround::Draw() const {
  title_texture_.Draw(0.f, 0.f, RenderAnchor::TopLeft);
}

}  // namespace mytetris
