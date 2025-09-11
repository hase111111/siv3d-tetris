
//! @file pause_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "pause_renderer.h"

#include "game_const.h"
#include "render_util.h"

namespace mytetris {

PauseRenderer::PauseRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr)
    : font_view_(resource_container_ptr->GetFont("default")),
      font_view_small_(resource_container_ptr->GetFont("small")) {}

void PauseRenderer::Draw(const bool is_paused) const {
  if (!is_paused) {
    return;
  }

  DrawRectAlpha(0, 0, GameConst::kResolutionX, GameConst::kResolutionY,
                0x00000000, true, 0.5f);

  const std::string pause_text = "PAUSE";
  const std::string resume_text = "Press P to Restart";
  font_view_.Draw(GameConst::kResolutionX / 2.f,
                  GameConst::kResolutionY / 2.f - 25.f, RenderAnchor::Center,
                  pause_text);

  font_view_small_.Draw(GameConst::kResolutionX / 2.f,
                        GameConst::kResolutionY / 2.f + 35.f,
                        RenderAnchor::Center, resume_text);
}

}  // namespace mytetris
