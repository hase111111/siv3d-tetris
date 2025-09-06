
//! @file tetris_updater.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <vector>

namespace mytetris {

class DropCount {
 public:
  DropCount();
  ~DropCount() = default;

  int GetCount(int level) const;

 private:
  const std::vector<int> count_list_;
};

}  // namespace mytetris
