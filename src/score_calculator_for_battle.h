//! @file score_calculator_for_battle.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <vector>

#include "battle_announce.h"
#include "i_score_calculator.h"
#include "tetris_announce.h"

namespace mytetris {

class ScoreCalculatorForBattle final : public IScoreCalculator {
 public:
  ScoreCalculatorForBattle(const std::shared_ptr<BattleAnnounce>& announce_ptr);
  ~ScoreCalculatorForBattle() = default;

  void Update() override;

  void AddScore(int lines_num, bool is_tspin, bool is_perfect_clear) override;

  void AddDropScore(int, bool) override {};

  inline void ResetCombo() override { combo_num_ = 0; }

  inline int GetScore() const override { return score_; }

  inline int GetScoreDifference() const override { return 0; }

  inline int GetComboNum() const override { return combo_num_; }

  inline bool IsBtbActive() const override { return is_btb_active_; }

 private:
  int Get(const std::vector<int> v, int idx) const;

  bool IsBtbActive(int lines_num, bool is_tspin) const;

  const std::shared_ptr<BattleAnnounce> announce_ptr_;
  const std::vector<int> line_clear_scores_{0, 1, 2, 4, 5};
  const std::vector<int> tspin_scores_{2, 4, 6};
  const std::vector<int> perfect_clear_scores_{10, 10, 10, 10};
  const int btb_bonus_score_ = 1;
  const std::vector<int> combo_bonus_{0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4, 5};

  int score_{0};
  bool is_btb_active_{false};
  int combo_num_{0};
};

}  // namespace mytetris
