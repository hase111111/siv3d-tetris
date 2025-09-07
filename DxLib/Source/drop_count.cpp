
//! @file tetris_updater.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "drop_count.h"

#include <format>

namespace mytetris {

DropCount::DropCount()
    : count_list_{10000, 60, 50, 45, 40, 36, 32, 28, 24,
                  20,    16, 12, 8,  4,  2,  1,  0} {}

int DropCount::GetCount(const int level) const {
  if (level < 0) {
    return count_list_.front();
  } else if (level >= static_cast<int>(count_list_.size())) {
    return count_list_.back();
  } else {
    return count_list_[static_cast<size_t>(level)];
  }
}

std::string DropCount::GetDisplaySpeed(int level) const {
  const int count = GetCount(level);

  if (count == 0) {
    return "Infinity";
  } else {
    const float interp = count / 60.0f * 100;
    const float speed = 101.0f - 1 * interp;
    return std::format("{}", static_cast<int>(speed));
  }
}

}  // namespace mytetris
