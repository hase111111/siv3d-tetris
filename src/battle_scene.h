//! @file battle_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "game_end_checker.h"
#include "game_setting_record.h"
#include "hold_renderer.h"
#include "hold_tetromino.h"
#include "i_scene.h"
#include "i_tetris_field_effect.h"
#include "key_event_handler.h"
#include "next_renderer.h"
#include "next_tetromino.h"
#include "penalty_renderer.h"
#include "penalty_updater.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "score_calculator_for_battle.h"
#include "tetris_feild.h"
#include "tetris_renderer.h"
#include "tetris_updater.h"

namespace mytetris {

class BattleScene final : public IScene {
 public:
  BattleScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr,
      const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr);
  ~BattleScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter&) override {};

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const float block_size_;
  const std::shared_ptr<TetrisField> player_tetris_field_ptr_;
  const std::shared_ptr<Tetromino> player_tetromino_ptr_;
  const std::shared_ptr<NextTetromino> player_next_ptr_;
  const std::shared_ptr<HoldTetromino> player_hold_ptr_;
  const std::shared_ptr<ScoreCalculatorForBattle> player_score_calculator_ptr_;
  const std::shared_ptr<TetrisUpdater> player_tetris_updater_ptr_;
  TetrisRenderer player_tetris_renderer_;
  HoldRenderer player_hold_renderer_;
  NextRenderer player_next_renderer_;

  const std::shared_ptr<TetrisField> enemy_tetris_field_ptr_;
  const std::shared_ptr<Tetromino> enemy_tetromino_ptr_;
  const std::shared_ptr<NextTetromino> enemy_next_ptr_;
  const std::shared_ptr<HoldTetromino> enemy_hold_ptr_;
  const std::shared_ptr<ScoreCalculatorForBattle> enemy_score_calculator_ptr_;
  const std::shared_ptr<TetrisUpdater> enemy_tetris_updater_ptr_;
  TetrisRenderer enemy_tetris_renderer_;
  HoldRenderer enemy_hold_renderer_;
  NextRenderer enemy_next_renderer_;

  const std::shared_ptr<PenaltyUpdater> penalty_updater_ptr_;
  PenaltyRenderer penalty_renderer_;
};

}  // namespace mytetris