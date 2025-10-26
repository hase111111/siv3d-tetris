
//! @file pause_renderer.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "pause_renderer.h"

#include "game_const.h"
#include "my_assert.h"
#include "my_format.h"
#include "render_util.h"

namespace mytetris {

PauseRenderer::PauseRenderer(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr)
    : key_event_handler_ptr_(key_event_handler_ptr),
      font_view_(resource_container_ptr->GetFont("default")),
      font_view_small_(resource_container_ptr->GetFont("small")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
}

void PauseRenderer::Draw(const bool is_paused) const {
  if (!is_paused) {
    return;
  }

  DrawRectAlpha(0, 0, GameConst::kResolutionX, GameConst::kResolutionY,
                0x00000000, true, 0.5f);

  const std::string pause_text = "PAUSE";
  const std::string resume_text = nostd::format(
      "Press {} to Restart",
      KeyHandleToString(
          key_event_handler_ptr_->GetKeyHandleFromKeyGroup(KeyGroup::kPause)));
  font_view_.Draw(GameConst::kResolutionX / 2.f,
                  GameConst::kResolutionY / 2.f - 25.f, RenderAnchor::Center,
                  pause_text);

  font_view_small_.Draw(GameConst::kResolutionX / 2.f,
                        GameConst::kResolutionY / 2.f + 35.f,
                        RenderAnchor::Center, resume_text);
}

}  // namespace mytetris
