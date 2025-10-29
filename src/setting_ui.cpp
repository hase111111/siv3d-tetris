//! @file setting_ui.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "setting_ui.h"

#include "game_const.h"
#include "my_assert.h"
#include "my_format.h"
#include "render_util.h"

namespace mytetris {

SettingUI::SettingUI(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
    const std::shared_ptr<GameSettingRecord>& game_setting_record_ptr,
    const std::function<void()>& scene_back_func)
    : key_event_handler_ptr_(key_event_handler_ptr),
      game_setting_record_ptr_(game_setting_record_ptr),
      scene_back_func_(scene_back_func),
      font_view_20_(resource_container_ptr->GetFont("small")),
      font_view_40_(resource_container_ptr->GetFont("default")),
      setting_labels_(InitializeSettingLabels()) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

  DEBUG_ASSERT_NOT_NULL_PTR(key_event_handler_ptr_);
  DEBUG_ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
}

void SettingUI::Update() {
  if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kUp) == 1) {
    selected_index_ += GetTotalSettingItemCount() - 1;
  } else if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kDown) == 1) {
    selected_index_ += 1;
  }

  // 選択されているラベルの関数を描画.
  int actual_index{0};
  const int selected_index = selected_index_ % GetTotalSettingItemCount();

  for (const auto& label : setting_labels_) {
    for (const auto& item : label.setting_items) {
      if (actual_index == selected_index) {
        item.update_func();
      }

      if (!label.is_disabled) {
        actual_index++;
      }
    }
  }

  // 画面の一番下の項目が選択されている場合，メニューに戻る.
  if (selected_index == GetTotalSettingItemCount() - 1 &&
      key_event_handler_ptr_->GetPressingCount(KeyGroup::kDecide) == 1) {
    scene_back_func_();
  }
}

void SettingUI::Draw() const {
  const float label_x = game_const::kResolutionXF * 5.f / 64.f;
  const float value_x = game_const::kResolutionXF * 11.f / 64.f;
  const float start_y = game_const::kResolutionYF * 13.f / 96.f;
  const float y_offset = game_const::kResolutionYF * 5.f / 96.f;

  int counter{0};
  int actual_index{0};
  const int selected_index = selected_index_ % GetTotalSettingItemCount();

  for (const auto& label : setting_labels_) {
    // ラベルを描画.
    const float alpha = label.is_disabled ? 0.2f : 1.0f;
    font_view_40_.DrawAlpha(label_x, start_y + y_offset * counter,
                            RenderAnchor::TopLeft, label.label_name,
                            game_const::kResolutionEx, alpha);
    counter++;
    for (const auto& item : label.setting_items) {
      // 項目を描画.
      const float alpha_item =
          label.is_disabled ? 0.2f
                            : ((actual_index == selected_index) ? 1.0f : 0.5f);
      font_view_40_.DrawAlpha(value_x, start_y + y_offset * counter,
                              RenderAnchor::TopLeft, item.item_name,
                              game_const::kResolutionEx, alpha_item);

      // 値を描画.
      font_view_40_.DrawAlpha(value_x + game_const::kResolutionXF * 15.f / 32.f,
                              start_y + y_offset * counter,
                              RenderAnchor::TopLeft, item.val_func(),
                              game_const::kResolutionEx, alpha_item);

      counter++;

      if (!label.is_disabled) {
        actual_index++;
      }
    }
  }

  // 画面の一番下に戻る項目を描画.
  font_view_40_.DrawAlpha(
      game_const::kResolutionX / 2.f, game_const::kResolutionY - 80.f,
      RenderAnchor::Center, "Back To Menu", game_const::kResolutionEx,
      selected_index == GetTotalSettingItemCount() - 1 ? 1.0f : 0.5f);
}

std::vector<SettingUI::SettingLabel> SettingUI::InitializeSettingLabels() {
  std::vector<SettingLabel> res;

  {
    SettingLabel window_size_label;
    window_size_label.label_name = "Window Size";
    window_size_label.setting_items.push_back(
        SettingItem{"Window Width", []() { return ""; }, []() {}});
    window_size_label.setting_items.push_back(
        SettingItem{"Window Height", []() { return ""; }, []() {}});
    window_size_label.is_disabled = true;
    res.push_back(window_size_label);
  }

  {
    SettingLabel volume_label;
    volume_label.label_name = "Volume";
    volume_label.setting_items.push_back(
        SettingItem{"Master Volume", []() { return ""; }, []() {}});
    volume_label.setting_items.push_back(
        SettingItem{"Sound Volume", []() { return ""; }, []() {}});
    volume_label.setting_items.push_back(
        SettingItem{"BGM Volume", []() { return ""; }, []() {}});
    volume_label.is_disabled = true;
    res.push_back(volume_label);
  }

  {
    SettingLabel gameplay_label;
    gameplay_label.label_name = "Game Play";
    gameplay_label.setting_items.push_back(SettingItem{
        "Delayed Auto Shift",
        [this]() {
          return nostd::format("<  {}  >",
                               game_setting_record_ptr_->delayed_auto_shift_);
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1) {
            game_setting_record_ptr_->delayed_auto_shift_ =
                std::max(1, game_setting_record_ptr_->delayed_auto_shift_ - 1);
          } else if (key_event_handler_ptr_->GetPressingCount(
                         KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->delayed_auto_shift_ =
                std::min(20, game_setting_record_ptr_->delayed_auto_shift_ + 1);
          }
        }});
    gameplay_label.setting_items.push_back(SettingItem{
        "Auto Repeat Rate",
        [this]() {
          return nostd::format("<  {}  >",
                               game_setting_record_ptr_->auto_repeat_rate_);
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1) {
            game_setting_record_ptr_->auto_repeat_rate_ =
                std::max(1, game_setting_record_ptr_->auto_repeat_rate_ - 1);
          } else if (key_event_handler_ptr_->GetPressingCount(
                         KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->auto_repeat_rate_ =
                std::min(20, game_setting_record_ptr_->auto_repeat_rate_ + 1);
          }
        }});
    gameplay_label.setting_items.push_back(SettingItem{
        "Allow Hold",
        [this]() {
          return nostd::format("<  {}  >", game_setting_record_ptr_->allow_hold
                                               ? "True"
                                               : "False");
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1 ||
              key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->allow_hold =
                !game_setting_record_ptr_->allow_hold;
          }
        }});
    gameplay_label.setting_items.push_back(SettingItem{
        "Display Ghost Tetromino",
        [this]() {
          return nostd::format("<  {}  >",
                               game_setting_record_ptr_->display_ghost_tetromino
                                   ? "True"
                                   : "False");
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1 ||
              key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->display_ghost_tetromino =
                !game_setting_record_ptr_->display_ghost_tetromino;
          }
        }});
    gameplay_label.setting_items.push_back(SettingItem{
        "Hard Drop Lock",
        [this]() {
          return nostd::format(
              "<  {}  >",
              game_setting_record_ptr_->hard_drop_lock ? "True" : "False");
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1 ||
              key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->hard_drop_lock =
                !game_setting_record_ptr_->hard_drop_lock;
          }
        }});
    gameplay_label.setting_items.push_back(SettingItem{
        "Soft Drop Lock",
        [this]() {
          return nostd::format(
              "<  {}  >",
              game_setting_record_ptr_->soft_drop_lock ? "True" : "False");
        },
        [this]() {
          if (key_event_handler_ptr_->GetPressingCount(KeyGroup::kLeft) == 1 ||
              key_event_handler_ptr_->GetPressingCount(KeyGroup::kRight) == 1) {
            game_setting_record_ptr_->soft_drop_lock =
                !game_setting_record_ptr_->soft_drop_lock;
          }
        }});
    gameplay_label.is_disabled = false;
    res.push_back(gameplay_label);
  }

  return res;
}

int SettingUI::GetTotalSettingItemCount() const {
  int count = 0;
  for (const auto& label : setting_labels_) {
    count +=
        label.is_disabled ? 0 : static_cast<int>(label.setting_items.size());
  }
  return count + 1;
}

}  // namespace mytetris
