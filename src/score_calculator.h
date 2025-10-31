//! @file score_calculator.h
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

class ScoreCalculator final : public IScoreCalculator {
 public:
  ScoreCalculator(const std::shared_ptr<TetrisAnnounce>& tetris_announce_ptr);
  ~ScoreCalculator() = default;

  void Update() override;

  void AddScore(int lines_num, bool is_tspin, bool is_perfect_clear) override;

  void AddDropScore(int drop_distance, bool is_hard_drop) override;

  inline void ResetCombo() override { combo_num_ = 0; }

  inline int GetScore() const override { return score_; }

  inline int GetScoreDifference() const override { return score_difference_; }

  inline int GetComboNum() const override { return combo_num_; }

  inline bool IsBtbActive() const override { return is_btb_active_; }

 private:
  int Get(const std::vector<int> v, int idx) const;

  bool IsBtbActive(int lines_num, bool is_tspin) const;

  const std::shared_ptr<TetrisAnnounce> tetris_announce_ptr_;
  const int drop_score_{1};
  const int hard_drop_score_{2};
  const std::vector<int> line_clear_scores_{100, 300, 500, 800, 1200};
  const std::vector<int> tspin_scores_{800, 1200, 1600};
  const std::vector<int> perfect_clear_scores_{800, 1000, 1800, 2000};
  const float btb_multiplier_{1.5f};
  const std::vector<int> combo_bonus_{0,   50,  100, 150, 200, 250, 300,
                                      350, 400, 450, 500, 550, 600, 650,
                                      700, 750, 800, 850, 900, 950, 1000};
  const int diff_display_duration_{60};

  int score_{0};
  int score_difference_{0};
  bool is_btb_active_{false};
  int combo_num_{0};
  int diff_display_counter_{0};
};

}  // namespace mytetris
