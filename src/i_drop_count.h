//! @file i_drop_count.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

namespace mytetris {

class IDropCount {
 public:
  virtual ~IDropCount() = default;

  virtual int GetCount(int level) const = 0;

  virtual std::string GetDisplaySpeed(int level) const = 0;
};

}  // namespace mytetris
