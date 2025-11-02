//! @file score_calculator_for_battle.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "score_calculator_for_battle.h"

#include "my_assert.h"

namespace mytetris {

void ScoreCalculatorForBattle::Update() { score_ = 0; }

void ScoreCalculatorForBattle::AddScore(const int lines_num,
                                        const bool is_tspin,
                                        const bool is_perfect_clear) {
  if (lines_num <= 0) {
    // ラインを消していない場合はスコアを加算しない.
    return;
  }

  // コンボ数を加算.
  ++combo_num_;

  // BTB を切る場合は, 点数計算の前に BTB を無効化しておく.
  if (!IsBtbActive(lines_num, is_tspin)) {
    is_btb_active_ = false;
  }

  // コンボボーナス加算.
  int diff{0};
  diff += Get(combo_bonus_, combo_num_ - 1);

  if (is_perfect_clear) {
    // パーフェクトクリア時のスコア加算.
    diff += Get(perfect_clear_scores_, lines_num - 1);
  } else {
    if (is_tspin) {
      diff += Get(tspin_scores_, lines_num - 1);
    } else {
      diff += Get(line_clear_scores_, lines_num - 1);
    }
  }

  // BTB ボーナス加算.
  if (is_btb_active_) {
    diff = static_cast<int>(diff * btb_multiplier_);
  }

  // BTB 状態更新.
  is_btb_active_ = IsBtbActive(lines_num, is_tspin);

  score_ = diff;
}

int ScoreCalculatorForBattle::Get(const std::vector<int> v, int idx) const {
  if (idx < 0) {
    return 0;
  }
  if (idx >= static_cast<int>(v.size())) {
    return v.back();
  }
  return v[idx];
}

bool ScoreCalculatorForBattle::IsBtbActive(const int lines_num,
                                           const bool is_tspin) const {
  return is_tspin || lines_num >= 4;
}

}  // namespace mytetris
