//! @file score_calculator_nothing.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <vector>

#include "i_score_calculator.h"
#include "tetris_announce.h"

namespace mytetris {

class ScoreCalculatorNothing final : public IScoreCalculator {
 public:
  ScoreCalculatorNothing();
  ~ScoreCalculatorNothing() = default;

  void Update() override;

  void AddScore(int, bool, bool) override;

  void AddDropScore(int, bool) override;

  inline void ResetCombo() override {}

  inline int GetScore() const override { return 0; }

  inline int GetScoreDifference() const override { return 0; }

  inline int GetComboNum() const override { return 0; }

  inline bool IsBtbActive() const override { return false; }
};

}  // namespace mytetris
