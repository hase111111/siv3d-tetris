//! @file tetris_field_effect_nothing.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <utility>

#include "i_tetris_field_effect.h"

namespace mytetris {

class TetrisFieldEffectNothing : public ITetrisFieldEffect {
 public:
  inline void Update() override {};

  inline void Reset() override {};

  float GetAlpha(int x, int y) const override;

  std::pair<int, int> GetDiff(int x, int y) const override;

  void SetActive(bool is_active) override;
};

}  // namespace mytetris
