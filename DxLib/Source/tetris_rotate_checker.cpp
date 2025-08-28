
//! @file tetris_rotate_checker.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "tetris_rotate_checker.h"

#include "dxlib_assert.h"

namespace mytetris {

TetrisRotateChecker::TetrisRotateChecker(
    const std::shared_ptr<TetrisField>& tetris_field_ptr)
    : right_offset_(InitializeRightOffset()),
      left_offset_(InitializeLeftOffset()),
      tetris_field_ptr_(tetris_field_ptr) {}

std::optional<std::tuple<int, int>> TetrisRotateChecker::CheckRotation(
    const Tetromino& tetromino, const int tetromino_x, const int tetromino_y,
    const bool left_rotate) const {
  const auto rot_type = tetromino.GetRotationType();
  const int rot_idx = GetRotatedIndex(tetromino, left_rotate);

  // 回転オフセットを取得.
  const auto& offset_map = left_rotate ? left_offset_ : right_offset_;
  const auto it = offset_map.find({rot_type, rot_idx});

  if (it == offset_map.end()) {
    // 見つからない場合はアサートを出す.
    ASSERT_MUST_NOT_REACH_HERE();
    return std::nullopt;
  }

  // オフセットを順番に試す.
  for (const auto& [offset_x, offset_y] : it->second) {
    if (CheckRotationCollision(tetromino, tetromino_x, tetromino_y, offset_x,
                               offset_y, left_rotate)) {
      return std::make_tuple(offset_x, offset_y);
    }
  }

  // 見つからなかった場合は nullopt を返す.
  // つまり，回転できない.
  return std::nullopt;
}

bool TetrisRotateChecker::CheckRotationCollision(
    const Tetromino& tetromino, const int tetromino_x, const int tetromino_y,
    const int offset_x, const int offset_y, const bool left_rotate) const {
  Tetromino rotate_tetromino = tetromino;

  if (left_rotate) {
    rotate_tetromino.LeftRotate();
  } else {
    rotate_tetromino.RightRotate();
  }

  return tetris_field_ptr_->IsValidPosition(
      rotate_tetromino, tetromino_x + offset_x, tetromino_y + offset_y);
}

int TetrisRotateChecker::GetRotatedIndex(const Tetromino& tetromino,
                                         const bool left_rotate) const {
  Tetromino rotate_tetromino = tetromino;

  if (left_rotate) {
    rotate_tetromino.LeftRotate();
  } else {
    rotate_tetromino.RightRotate();
  }

  return rotate_tetromino.GetRotationIndex();
}

std::map<std::tuple<RotationType, int>, std::vector<TetrisRotateChecker::pii>>
TetrisRotateChecker::InitializeRightOffset() const {
  std::map<std::tuple<RotationType, int>, std::vector<pii>> result;

  // None はオフセットなし.
  result[{RotationType::kNone, 0}] = {{0, 0}};
  result[{RotationType::kNone, 1}] = {{0, 0}};
  result[{RotationType::kNone, 2}] = {{0, 0}};
  result[{RotationType::kNone, 3}] = {{0, 0}};

  // Normal のオフセット.
  result[{RotationType::kNormal, 0}] = {
      {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
  result[{RotationType::kNormal, 1}] = {
      {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
  result[{RotationType::kNormal, 2}] = {
      {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}};
  result[{RotationType::kNormal, 3}] = {
      {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}};

  // I のオフセット.
  result[{RotationType::kI, 0}] = {{0, 0}};
  result[{RotationType::kI, 1}] = {{0, 0}};
  result[{RotationType::kI, 2}] = {{0, 0}};
  result[{RotationType::kI, 3}] = {{0, 0}};

  return result;
}

std::map<std::tuple<RotationType, int>, std::vector<TetrisRotateChecker::pii>>
TetrisRotateChecker::InitializeLeftOffset() const {
  std::map<std::tuple<RotationType, int>, std::vector<pii>> result;

  // None はオフセットなし.
  result[{RotationType::kNone, 0}] = {{0, 0}};
  result[{RotationType::kNone, 1}] = {{0, 0}};
  result[{RotationType::kNone, 2}] = {{0, 0}};
  result[{RotationType::kNone, 3}] = {{0, 0}};

  // Normal のオフセット.
  result[{RotationType::kNormal, 0}] = {
      {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}};
  result[{RotationType::kNormal, 1}] = {
      {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
  result[{RotationType::kNormal, 2}] = {
      {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
  result[{RotationType::kNormal, 3}] = {
      {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}};

  // I のオフセット.
  result[{RotationType::kI, 0}] = {{0, 0}};
  result[{RotationType::kI, 1}] = {{0, 0}};
  result[{RotationType::kI, 2}] = {{0, 0}};
  result[{RotationType::kI, 3}] = {{0, 0}};

  return result;
}

}  // namespace mytetris
