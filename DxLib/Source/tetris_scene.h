
//! @file tetris_scene.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>

#include "description_field_renderer.h"
#include "drop_count.h"
#include "drop_gauge_renderer.h"
#include "fade_effect.h"
#include "hold_renderer.h"
#include "hold_tetromino.h"
#include "i_scene.h"
#include "key_event_handler.h"
#include "next_renderer.h"
#include "next_tetromino.h"
#include "resource_container.h"
#include "scene_change_listener.h"
#include "score_board_renderer.h"
#include "tetris_feild.h"
#include "tetris_level.h"
#include "tetris_renderer.h"
#include "tetris_timer.h"
#include "tetris_updater.h"

namespace mytetris {

class TetrisScene final : public IScene {
 public:
  TetrisScene(
      const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
      const std::shared_ptr<const KeyEventHandler>& key_event_handler_ptr,
      const std::shared_ptr<const ResourceContainer>& resource_container_ptr);
  ~TetrisScene() = default;

  bool Update() override;

  void Draw() const override;

  void OnStart(const SceneChangeParameter& parameter) override;

  void OnReturnFromOtherScene(const SceneChangeParameter& parameter) override;

 private:
  const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
  const std::shared_ptr<const KeyEventHandler> key_event_handler_ptr_;
  const std::shared_ptr<const ResourceContainer> resource_container_ptr_;
  const std::shared_ptr<NextTetromino> next_tetromino_ptr_;
  const std::shared_ptr<TetrisField> tetris_field_ptr_;
  const std::shared_ptr<Tetromino> tetromino_ptr_;
  const std::shared_ptr<HoldTetromino> hold_tetromino_ptr_;
  const std::shared_ptr<TetrisLevel> tetris_level_ptr_;
  const std::shared_ptr<TetrisTimer> tetris_timer_ptr_;
  const std::shared_ptr<DropCount> drop_count_ptr_;
  const std::unique_ptr<TetrisUpdater> tetris_updater_ptr_;
  DescriptionFieldRenderer description_field_renderer_;
  TetrisRenderer tetris_renderer_;
  NextRenderer next_renderer_;
  DropGaugeRenderer drop_gauge_renderer_;
  HoldRenderer hold_renderer_;
  FadeEffect fade_effect_;
  ScoreBoardRenderer score_board_renderer_;
  SceneChangeParameter parameter_;
};

}  // namespace mytetris
