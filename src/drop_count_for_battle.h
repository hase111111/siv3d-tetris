//! @file drop_count_for_battle.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>
#include <vector>

#include "i_drop_count.h"

namespace mytetris {

class DropCountForBattle final : public IDropCount {
 public:
  DropCountForBattle() = default;
  ~DropCountForBattle() = default;

  int GetCount(int level) const override;

  std::string GetDisplaySpeed(int level) const override;
};

}  // namespace mytetris
