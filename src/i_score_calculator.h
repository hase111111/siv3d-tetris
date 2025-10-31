//! @file i_score_calculator.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <vector>

namespace mytetris {

class IScoreCalculator {
 public:
  virtual ~IScoreCalculator() = default;

  virtual void Update() = 0;

  virtual void AddScore(int lines_num, bool is_tspin,
                        bool is_perfect_clear) = 0;

  virtual void AddDropScore(int drop_distance, bool is_hard_drop) = 0;

  virtual void ResetCombo() = 0;

  virtual int GetScore() const = 0;

  virtual int GetScoreDifference() const = 0;

  virtual int GetComboNum() const = 0;

  virtual bool IsBtbActive() const = 0;
};

}  // namespace mytetris
