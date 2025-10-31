//! @file tetris_field_effect.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <array>
#include <memory>
#include <tuple>
#include <vector>

#include "i_tetris_field_effect.h"
#include "tetris_feild.h"
#include "tetris_game_mode.h"
#include "tetris_level.h"

namespace mytetris {

enum class EffectType : int {
  kBlind = 0,
  kBlink = 1,
  kRandomBlind = 2,
  kRandomShake = 3,
  kRandomMove = 4,
  kSinMove = 5,
  kBlinkAndSinMove = 6,
  kBlinkAndShake = 7,
  kRandomBlinkAndShake = 8,
  kRandomBlinkAndSin = 9,
  kBlindAndRandomMove = 10,
  kNone = 11,
};

class TetrisFieldEffect final : public ITetrisFieldEffect {
  template <typename T>
  using Field =
      std::array<std::array<T, TetrisField::kHeight>, TetrisField::kWidth>;

 public:
  TetrisFieldEffect(const std::shared_ptr<const TetrisLevel>& tetris_level_ptr);

  void Update() override;

  void Reset() override;

  float GetAlpha(int x, int y) const override;

  std::pair<int, int> GetDiff(int x, int y) const override;

  void SetActive(bool is_active) override { is_active_ = is_active; }

 private:
  void UpdateEffect();
  void Blind();
  void Blink();
  void RandomBlind();
  void RandomShake();
  void RandomMove();
  void SinMove();

  void ChangeEffect();

  void ResetFieldEffects();

  const std::shared_ptr<const TetrisLevel> tetris_level_ptr_;

  bool is_active_{false};
  int cnt_{0};
  int last_total_clear_lines_{0};
  Field<std::pair<double, double>> diff_{};
  Field<std::pair<double, double>> speed_{};
  Field<double> alpha_{};
  EffectType effect_type_{EffectType::kNone};
};

}  // namespace mytetris
