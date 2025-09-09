
//! @file title_ui.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_ui.h"

#include <cmath>

#include "game_const.h"
#include "my_assert.h"
#include "tetris_game_mode.h"

namespace mytetris {

TitleUI::TitleUI(
    const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr_,
    const std::function<void(const SceneChangeParameter&)>& to_game_scene)
    : font_view_40_(resource_container_ptr_->GetFont("default")),
      font_view_20_(resource_container_ptr_->GetFont("small")),
      key_event_handler_ptr_(key_event_handler_ptr),
      title_items_({"Game Start", "Special Mode", "Setting", "Quit Game"}),
      game_mode_items_({"Endless Mode", "Ultra Mode", "Sprint Mode",
                        "Marathon Mode", "Back"}),
      special_mode_items_(
          {"Ueda Mode", "Pentris Mode", "Trick Mode", "Practice Mode", "Back"}),
      to_game_scene_(to_game_scene) {}

bool TitleUI::Update() {
  ++counter_;

  // UI‚ÌXVˆ—‚ð‚±‚±‚ÉŽÀ‘•.
  switch (selected_index_) {
    case 0: {
      return UpdateTitle();
    }
    case 1: {
      return UpdateGameStart();
    }
    case 2: {
      return UpdateSpecialMode();
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return true;
    }
  }
}

void TitleUI::Draw() const {
  // UI‚Ì•`‰æˆ—‚ð‚±‚±‚ÉŽÀ‘•.
  switch (selected_index_) {
    case 0: {
      DrawTitle();
      return;
    }
    case 1: {
      DrawGameStart();
      return;
    }
    case 2: {
      DrawSpecialMode();
      return;
    }
    default: {
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return;
    }
  }
}

bool TitleUI::UpdateTitle() {
  lower_announcement_ =
      "Use Up/Down key to move, Z key to decide, Esc key to quit.";

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
    case 0: {
      // Endless.
      lower_announcement_ =
          "Endless: Play continuously until you top out, no fixed goal.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode",
                                           TetrisGameMode::kEndless);
        to_game_scene_(param);
      }
      return true;
    }
    case 1: {
      // Ultra.
      lower_announcement_ =
          "Ultra: Score as many points as possible in 3 minutes.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kUltra);
        to_game_scene_(param);
      }
      return true;
    }
    case 2: {
      // Sprint.
      lower_announcement_ = "Sprint: Clear 40 lines as fast as possible.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kSprint);
        to_game_scene_(param);
      }
      return true;
    }
    case 3: {
      // Marathon.
      lower_announcement_ =
          "Marathon: Play continuously until you top out, with a fixed goal of "
          "200 lines.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode",
                                           TetrisGameMode::kMarathon);
        to_game_scene_(param);
      }
      return true;
    }
    case 4: {
      // Back.
      lower_announcement_ = "Return to the previous menu.";
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

bool TitleUI::UpdateSpecialMode() {
  if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kUp) == 1) {
    mode_index_ += static_cast<int>(game_mode_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % special_mode_items_.size();

  switch (idx) {
    case 0: {
      // Ueda.
      lower_announcement_ =
          "Ueda: A high-difficulty mode where super-huge blocks fall.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kUeda);
        to_game_scene_(param);
      }
      return true;
    }
    case 1: {
      // Pentris.
      lower_announcement_ =
          "Pentris: This mode utilizes Pentris, which consists of five "
          "blocks.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode",
                                           TetrisGameMode::kPentris);
        to_game_scene_(param);
      }
      return true;
    }
    case 2: {
      // Trick.
      lower_announcement_ =
          "Trick: This mode lets you enjoy mysterious visual effects.";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kTrick);
        to_game_scene_(param);
      }
      return true;
    }
    case 3: {
      // Practice.
      lower_announcement_ =
          "Practice: This is practice mode. Let's practice hard!";
      if (key_event_handler_ptr_->GetPressingCount(KeyHandle::kZ) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode",
                                           TetrisGameMode::kPractice);
        to_game_scene_(param);
      }
      return true;
    }
    case 4: {
      // Back.
      lower_announcement_ = "Return to the previous menu.";
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
    font_view_40_.DrawAlpha(GameConst::kResolutionX / 2.0f,
                            GameConst::kResolutionY / 2.0f + 120 + offset_y * i,
                            RenderAnchor::Center, title_items_[i].c_str(),
                            idx == i ? alpha : 0.5f);
  }

  // ‰º•”‚ÌˆÄ“à•¶‚ð•`‰æ.
  font_view_20_.Draw(GameConst::kResolutionX / 2.0f,
                     GameConst::kResolutionY - 20.f, RenderAnchor::Center,
                     lower_announcement_.c_str());
}

void TitleUI::DrawGameStart() const {
  const float offset_y = 70.f;
  const int idx = mode_index_ % game_mode_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i = 0; i < game_mode_items_.size(); ++i) {
    font_view_40_.DrawAlpha(GameConst::kResolutionX / 2.0f,
                            GameConst::kResolutionY / 2.0f + 120 + offset_y * i,
                            RenderAnchor::Center, game_mode_items_[i].c_str(),
                            idx == i ? alpha : 0.5f);
  }

  // ‰º•”‚ÌˆÄ“à•¶‚ð•`‰æ.
  font_view_20_.Draw(GameConst::kResolutionX / 2.0f,
                     GameConst::kResolutionY - 20.f, RenderAnchor::Center,
                     lower_announcement_.c_str());
}

void TitleUI::DrawSpecialMode() const {
  const float offset_y = 70.f;
  const int idx = mode_index_ % special_mode_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i = 0; i < special_mode_items_.size(); ++i) {
    font_view_40_.DrawAlpha(GameConst::kResolutionX / 2.0f,
                            GameConst::kResolutionY / 2.0f + 120 + offset_y * i,
                            RenderAnchor::Center,
                            special_mode_items_[i].c_str(),
                            idx == i ? alpha : 0.5f);
  }

  // ‰º•”‚ÌˆÄ“à•¶‚ð•`‰æ.
  font_view_20_.Draw(GameConst::kResolutionX / 2.0f,
                     GameConst::kResolutionY - 20.f, RenderAnchor::Center,
                     lower_announcement_.c_str());
}

}  // namespace mytetris
