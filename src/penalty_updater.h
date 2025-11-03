#pragma once

#include <memory>
#include <tuple>

#include "i_score_calculator.h"

namespace mytetris {

class PenaltyUpdater final {
 public:
  PenaltyUpdater(const std::shared_ptr<IScoreCalculator>& player,
                 const std::shared_ptr<IScoreCalculator>& enemy);
  ~PenaltyUpdater() = default;

  std::tuple<int, int> Update();

  int GetPenaltyLines() const { return penalty_lines_; }

  int GetCounter() const { return counter_; }

  int GetPenaltyInterval() const { return penalty_interval_; }

 private:
  const std::shared_ptr<IScoreCalculator> player_score_calculator_ptr_;
  const std::shared_ptr<IScoreCalculator> enemy_score_calculator_ptr_;
  const int penalty_interval_{60 * 6};

  int penalty_lines_{0};
  int counter_{0};
  int dic_counter_{0};
};

}  // namespace mytetris
