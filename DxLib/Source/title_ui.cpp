
//! @file title_ui.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_ui.h"

namespace mytetris {

TitleUI::TitleUI(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr_)
    : font_view_(resource_container_ptr_->GetFont("default")) {}

void TitleUI::Draw() const {
  // UI‚Ì•`‰æˆ—‚ğ‚±‚±‚ÉÀ‘•.
  font_view_.Draw(100.0f, 100.0f, RenderAnchor::TopLeft,
                  "Press Z to Start\nPress ESC to Exit");
}

}  // namespace mytetris
