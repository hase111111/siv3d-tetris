//! @file i_tetris_field_effect.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <utility>

namespace mytetris {

class ITetrisFieldEffect {
 public:
  virtual ~ITetrisFieldEffect() = default;

  virtual void Update() = 0;

  virtual void Reset() = 0;

  virtual float GetAlpha(int x, int y) const = 0;

  virtual std::pair<int, int> GetDiff(int x, int y) const = 0;

  virtual void SetActive(bool is_active) = 0;
};

}  // namespace mytetris
