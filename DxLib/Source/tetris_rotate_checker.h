
//! @file tetris_rotate_checker.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <map>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

#include "tetris_feild.h"
#include "tetromino.h"

namespace mytetris {

class TetrisRotateChecker final {
  using pii = std::pair<int, int>;

 public:
  TetrisRotateChecker(const std::shared_ptr<TetrisField>& tetris_field_ptr);
  ~TetrisRotateChecker() = default;

  std::optional<std::tuple<int, int>> CheckRotation(const Tetromino& tetromino,
                                                    int tetromino_x,
                                                    int tetromino_y,
                                                    bool left_rotate) const;

 private:
  bool CheckRotationCollision(const Tetromino& tetromino, int tetris_x,
                              int tetris_y, int offset_x, int offset_y,
                              bool left_rotate) const;

  int GetRotatedIndex(const Tetromino& tetromino, bool left_rotate) const;

  std::map<std::tuple<RotationType, int>, std::vector<pii>>
  InitializeRightOffset() const;

  std::map<std::tuple<RotationType, int>, std::vector<pii>>
  InitializeLeftOffset() const;

  const std::map<std::tuple<RotationType, int>, std::vector<pii>> right_offset_;
  const std::map<std::tuple<RotationType, int>, std::vector<pii>> left_offset_;
  const std::shared_ptr<TetrisField> tetris_field_ptr_;
};

}  // namespace mytetris
