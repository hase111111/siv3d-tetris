
//! @file title_ui.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_ui.h"

#include <cmath>

#include "game_const.h"
#include "my_assert.h"

namespace mytetris {

TitleUI::TitleUI(
    const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr_)
    : font_view_(resource_container_ptr_->GetFont("default")),
      key_event_handler_ptr_(key_event_handler_ptr),
      title_items_({"GameStart", "SpecialMode", "Setting", "QuitGame"}),
      game_mode_items_({"Endless Mode", "Ultra Mode", "Sprint Mode",
                        "Marathon Mode", "Practice Mode", "Back"}) {}

bool TitleUI::Update() {
  ++counter_;

  // UIの更新処理をここに実装.
  switch (selected_index_) {
    case 0: {
      return UpdateTitle();
    }
    case 1: {
      return UpdateGameStart();
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return true;
    }
  }
}

void TitleUI::Draw() const {
  // UIの描画処理をここに実装.
  switch (selected_index_) {
    case 0: {
      DrawTitle();
      return;
    }
    case 1: {
      DrawGameStart();
      return;
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return;
    }
  }
}

bool TitleUI::UpdateTitle() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    mode_index_ += static_cast<int>(title_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % title_items_.size();

  switch (idx) {
    case 0: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        selected_index_ = 1;
        mode_index_ = 0;
      }
      return true;
    }
    case 1: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        selected_index_ = 2;
        mode_index_ = 0;
      }
      return true;
    }
    case 2: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        selected_index_ = 3;
        mode_index_ = 0;
      }
      return true;
    }
    case 3: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        return false;  // QuitGame selected
      }
      return true;
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return true;
    }
  }
}

bool TitleUI::UpdateGameStart() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    mode_index_ += static_cast<int>(game_mode_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % game_mode_items_.size();

  switch (idx) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        // ゲーム開始処理をここに実装.
        // 現在は選択されたモードをコンソールに出力するだけ.
      }
      return true;
    }
    case 5: {
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        selected_index_ = 0;
        mode_index_ = 0;
      }
      return true;
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return true;
    }
  }
}

void TitleUI::DrawTitle() const {
  const float offset_y = 80.f;
  const int idx = mode_index_ % title_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i = 0; i < title_items_.size(); ++i) {
    font_view_.DrawAlpha(GameConst::kResolutionX / 2.0f,
                         GameConst::kResolutionY / 2.0f + 130 + offset_y * i,
                         RenderAnchor::Center, title_items_[i].c_str(),
                         idx == i ? alpha : 0.5f);
  }
}

void TitleUI::DrawGameStart() const {
  const float offset_y = 60.f;
  const int idx = mode_index_ % game_mode_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i = 0; i < game_mode_items_.size(); ++i) {
    font_view_.DrawAlpha(GameConst::kResolutionX / 2.0f,
                         GameConst::kResolutionY / 2.0f + 100 + offset_y * i,
                         RenderAnchor::Center, game_mode_items_[i].c_str(),
                         idx == i ? alpha : 0.5f);
  }
}

}  // namespace mytetris
