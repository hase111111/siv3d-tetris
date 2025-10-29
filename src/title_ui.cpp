//! @file title_ui.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "title_ui.h"

#include <cmath>

#include "game_const.h"
#include "my_assert.h"
#include "my_format.h"
#include "tetris_game_mode.h"
#include "version.h"

namespace mytetris {

TitleUI::TitleUI(
    const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr,
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr_,
    const std::function<void(const SceneChangeParameter&)>& to_game_scene,
    const std::function<void()>& to_setting_scene)
    : font_view_40_(resource_container_ptr_->GetFont("default")),
      font_view_20_(resource_container_ptr_->GetFont("small")),
      key_event_handler_ptr_(key_event_handler_ptr),
      title_items_({"Game Start", "Special Mode", "Setting", "Quit Game"}),
      game_mode_items_({"Endless Mode", "Ultra Mode", "Sprint Mode",
                        "Marathon Mode", "Back"}),
      special_mode_items_({"Yamada Mode", "Pentris Mode", "Trick Mode",
                           "Practice Mode", "Back"}),
      to_game_scene_(to_game_scene),
      to_setting_scene_(to_setting_scene) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
}

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
  DrawVersionInfo();

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
  const auto up_key = KeyHandleToString(
      key_event_handler_ptr_->GetKeyHandleFromKeyGroup(KeyGroup::kUp));
  const auto down_key = KeyHandleToString(
      key_event_handler_ptr_->GetKeyHandleFromKeyGroup(KeyGroup::kDown));
  const auto decide_key = KeyHandleToString(
      key_event_handler_ptr_->GetKeyHandleFromKeyGroup(KeyGroup::kDecide));
  lower_announcement_ =
      nostd::format("Use {}/{} key to move, {} key to decide, Esc key to quit.",
                    up_key, down_key, decide_key);

  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    mode_index_ += static_cast<int>(title_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % title_items_.size();

  switch (idx) {
    case 0: {
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
        selected_index_ = 1;
        mode_index_ = 0;
      }
      return true;
    }
    case 1: {
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
        selected_index_ = 2;
        mode_index_ = 0;
      }
      return true;
    }
    case 2: {
      // Setting.
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
        to_setting_scene_();
      }
      return true;
    }
    case 3: {
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    mode_index_ += static_cast<int>(game_mode_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % game_mode_items_.size();

  switch (idx) {
    case 0: {
      // Endless.
      lower_announcement_ =
          "Endless: Play continuously until you top out, no fixed goal.";
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kUltra);
        to_game_scene_(param);
      }
      return true;
    }
    case 2: {
      // Sprint.
      lower_announcement_ = "Sprint: Clear 40 lines as fast as possible.";
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    mode_index_ += static_cast<int>(game_mode_items_.size()) - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) == 1) {
    mode_index_ += 1;
  }

  const int idx = mode_index_ % special_mode_items_.size();

  switch (idx) {
    case 0: {
      // Yamada.
      lower_announcement_ =
          "Yamada: A high-difficulty mode where super-huge blocks fall.";
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
        auto param = SceneChangeParameter{};
        param.SetParameter<TetrisGameMode>("GameMode", TetrisGameMode::kYamada);
        to_game_scene_(param);
      }
      return true;
    }
    case 1: {
      // Pentris.
      lower_announcement_ =
          "Pentris: This mode utilizes Pentris, which consists of five "
          "blocks.";
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
      if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
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
    font_view_40_.DrawAlpha(game_const::kResolutionX / 2.0f,
                            game_const::kResolutionY * 5.f / 8.f +
                                offset_y * game_const::kResolutionEx * i,
                            RenderAnchor::Center, title_items_[i].c_str(),
                            game_const::kResolutionEx, idx == i ? alpha : 0.5f);
  }

  // 下部の案内文を描画.
  font_view_20_.Draw(game_const::kResolutionX / 2.0f,
                     game_const::kResolutionYF * 47.f / 48.f,
                     RenderAnchor::Center, lower_announcement_.c_str(),
                     game_const::kResolutionEx);
}

void TitleUI::DrawGameStart() const {
  const float offset_y = 70.f;
  const int idx = mode_index_ % game_mode_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i = 0; i < game_mode_items_.size(); ++i) {
    font_view_40_.DrawAlpha(game_const::kResolutionX / 2.0f,
                            game_const::kResolutionY * 5.f / 8.f +
                                offset_y * i * game_const::kResolutionEx,
                            RenderAnchor::Center, game_mode_items_[i].c_str(),
                            game_const::kResolutionEx, idx == i ? alpha : 0.5f);
  }

  // 下部の案内文を描画.
  font_view_20_.Draw(game_const::kResolutionX / 2.0f,
                     game_const::kResolutionYF * 47.f / 48.f,
                     RenderAnchor::Center, lower_announcement_.c_str(),
                     game_const::kResolutionEx);
}

void TitleUI::DrawSpecialMode() const {
  const float offset_y = 70.f;
  const int idx = mode_index_ % special_mode_items_.size();
  const float alpha = 0.5f + 0.5f * std::abs(std::sinf(counter_ / 15.f));

  for (int i{0}; i < special_mode_items_.size(); ++i) {
    font_view_40_.DrawAlpha(game_const::kResolutionX / 2.0f,
                            game_const::kResolutionY * 5.f / 8.f +
                                offset_y * i * game_const::kResolutionEx,
                            RenderAnchor::Center,
                            special_mode_items_[i].c_str(),
                            game_const::kResolutionEx, idx == i ? alpha : 0.5f);
  }

  // 下部の案内文を描画.
  font_view_20_.Draw(game_const::kResolutionXF / 2.0f,
                     game_const::kResolutionYF * 47.f / 48.f,
                     RenderAnchor::Center, lower_announcement_.c_str(),
                     game_const::kResolutionEx);
}

void TitleUI::DrawVersionInfo() const {
  // 画面右下にバージョン情報を描画する.
  const std::string version_info =
      nostd::format("Version {}", GetVersionString());
  font_view_20_.Draw(game_const::kResolutionXF * 61.f / 64.f,
                     game_const::kResolutionYF * 95.f / 96.f,
                     RenderAnchor::BottomRight, version_info.c_str(),
                     game_const::kResolutionEx);
}

}  // namespace mytetris
