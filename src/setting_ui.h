#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "font_view.h"
#include "game_setting_record.h"
#include "key_event_handler.h"
#include "resource_container.h"

namespace mytetris {

class SettingUI final {
  struct SettingItem final {
    std::string item_name;
    std::function<std::string()> val_func;
    std::function<void()> update_func;
  };

  struct SettingLabel final {
    std::string label_name;
    std::vector<SettingItem> setting_items;
    bool is_disabled{false};
  };

 public:
  SettingUI(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<GameSettingRecord>& game_setting_record_ptr,
      const std::function<void()>& scene_back_func);
  ~SettingUI() = default;

  void Update();

  void Draw() const;

 private:
  std::vector<SettingLabel> InitializeSettingLabels();
  int GetTotalSettingItemCount() const;

  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
  const std::shared_ptr<GameSettingRecord> game_setting_record_ptr_;
  const std::function<void()> scene_back_func_;
  const FontView font_view_40_;
  const FontView font_view_20_;
  const std::vector<SettingLabel> setting_labels_;

  int selected_index_{0};
};

}  // namespace mytetris