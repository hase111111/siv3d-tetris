#include "setting_ui.h"

#include "my_assert.h"

namespace mytetris {

SettingUI::SettingUI(
    const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
    const std::function<void()>& scene_back_func)
    : scene_back_func_(scene_back_func),
      font_view_20_(resource_container_ptr->GetFont("small")),
      font_view_40_(resource_container_ptr->GetFont("default")) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(resource_container_ptr);
}

void SettingUI::Update() {
  // 現状，特に更新処理はなし.
}

void SettingUI::Draw() const {
  const int label_x = 100;
  const int value_x = 220;
  const int start_y = 130;
  const int y_offset = 50;

  // サンプルでいくつかの設定項目を描画.
  font_view_40_.Draw(label_x, start_y + y_offset * 0, RenderAnchor::TopLeft,
                     "Window Size:");
  font_view_40_.Draw(value_x, start_y + y_offset * 1, RenderAnchor::TopLeft,
                     "Window Width");
  font_view_40_.Draw(value_x, start_y + y_offset * 2, RenderAnchor::TopLeft,
                     "Window Height");

  font_view_40_.Draw(label_x, start_y + y_offset * 3, RenderAnchor::TopLeft,
                     "Volume:");
  font_view_40_.Draw(value_x, start_y + y_offset * 4, RenderAnchor::TopLeft,
                     "Master Volume");
  font_view_40_.Draw(value_x, start_y + y_offset * 5, RenderAnchor::TopLeft,
                     "Sound Volume");
  font_view_40_.Draw(value_x, start_y + y_offset * 6, RenderAnchor::TopLeft,
                     "BGM Volume");

  font_view_40_.Draw(label_x, start_y + y_offset * 7, RenderAnchor::TopLeft,
                     "Game Play:");
  font_view_40_.Draw(value_x, start_y + y_offset * 8, RenderAnchor::TopLeft,
                     "Delayed Auto Shift");
  font_view_40_.Draw(value_x, start_y + y_offset * 9, RenderAnchor::TopLeft,
                     "Auto Repeat Rate");
  font_view_40_.Draw(value_x, start_y + y_offset * 10, RenderAnchor::TopLeft,
                     "Allow Hold");
  font_view_40_.Draw(value_x, start_y + y_offset * 11, RenderAnchor::TopLeft,
                     "Display Ghost Tetromino");
  font_view_40_.Draw(value_x, start_y + y_offset * 12, RenderAnchor::TopLeft,
                     "Hard Drop Lock");
  font_view_40_.Draw(value_x, start_y + y_offset * 13, RenderAnchor::TopLeft,
                     "Soft Drop Lock");
}

}  // namespace mytetris
