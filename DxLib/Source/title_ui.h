
//! @file title_ui.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "font_view.h"
#include "resource_container.h"

namespace mytetris {

class TitleUI final {
 public:
  TitleUI(
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr_);
  ~TitleUI() = default;

  void Draw() const;

 private:
  FontView font_view_;
};

}  // namespace mytetris
