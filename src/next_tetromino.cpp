
//! @file next_tetromino.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "next_tetromino.h"

#include <algorithm>
#include <random>

#include "my_assert.h"

namespace mytetris {

NextTetromino::NextTetromino() : next_{MakeNextTetromino()} {}

Tetromino NextTetromino::GetNext() const {
  ASSERT(!next_.empty(), "No next tetromino available.");
  return tetromino_generator_.Generate(next_.back());
}

std::vector<Tetromino> NextTetromino::GetNextList() const {
  // 後ろから7つのテトリミノを返す, 足りなければ先頭から埋める.
  if (next_.size() >= tetrominos_.size()) {
    const auto types = std::vector<TetrominoType>(
        next_.end() - tetrominos_.size(), next_.end());
    std::vector<Tetromino> tetrominos;
    tetrominos.reserve(types.size());
    for (const auto& type : types) {
      tetrominos.push_back(tetromino_generator_.Generate(type));
    }
    return tetrominos;
  } else {
    std::vector<Tetromino> tetrominos;
    tetrominos.reserve(next_.size());
    for (const auto& type : next_) {
      tetrominos.push_back(tetromino_generator_.Generate(type));
    }
    return tetrominos;
  }
}

void NextTetromino::Next() {
  next_.pop_back();
  if (next_.size() < tetrominos_.size()) {
    // 7個未満なら新しいテトリミノを追加する
    std::vector<TetrominoType> new_tetrominos = MakeNextTetromino();
    next_.insert(next_.begin(), new_tetrominos.begin(), new_tetrominos.end());
  }
}

void NextTetromino::SetGameMode(const TetrisGameMode game_mode) {
  switch (game_mode) {
    case TetrisGameMode::kEndless:
    case TetrisGameMode::kSprint:
    case TetrisGameMode::kUltra:
    case TetrisGameMode::kMarathon:
    case TetrisGameMode::kTrick: {
      tetrominos_ = {
          TetrominoType::kI, TetrominoType::kJ, TetrominoType::kL,
          TetrominoType::kO, TetrominoType::kS, TetrominoType::kT,
          TetrominoType::kZ,
      };
      break;
    }
    case TetrisGameMode::kYamada: {
      tetrominos_ = {
          TetrominoType::kI,        TetrominoType::kI,
          TetrominoType::kI,        TetrominoType::kI,
          TetrominoType::kJ,        TetrominoType::kJ,
          TetrominoType::kL,        TetrominoType::kL,
          TetrominoType::kO,        TetrominoType::kO,
          TetrominoType::kS,        TetrominoType::kS,
          TetrominoType::kT,        TetrominoType::kT,
          TetrominoType::kT,        TetrominoType::kZ,
          TetrominoType::kZ,        TetrominoType::kYama,
          TetrominoType::kDa,       TetrominoType::kMiniI,
          TetrominoType::kOneByTwo, TetrominoType::kOneByTwo,
          TetrominoType::kOneByTwo, TetrominoType::kOneByTwo,
          TetrominoType::kOneByOne, TetrominoType::kOneByOne,
          TetrominoType::kSilentT,  TetrominoType::kPentrisCross,
      };
      break;
    }
    case TetrisGameMode::kPentris: {
      tetrominos_ = {
          TetrominoType::kPentrisI,     TetrominoType::kPentrisJ,
          TetrominoType::kPentrisJDash, TetrominoType::kPentrisL,
          TetrominoType::kPentrisLDash, TetrominoType::kPentrisOL,
          TetrominoType::kPentrisOR,    TetrominoType::kPentrisS,
          TetrominoType::kPentrisSDash, TetrominoType::kPentrisZ,
          TetrominoType::kPentrisZDash, TetrominoType::kPentrisTL,
          TetrominoType::kPentrisTR,    TetrominoType::kPentrisTCenter,
          TetrominoType::kPentrisOu,    TetrominoType::kPentrisCorner,
          TetrominoType::kPentrisCross, TetrominoType::kPentrisStep,
      };
      break;
    }
    default:
      break;
  }

  next_ = MakeNextTetromino();
}

std::vector<TetrominoType> NextTetromino::MakeNextTetromino() const {
  std::vector<TetrominoType> tetrominos = tetrominos_;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(tetrominos.begin(), tetrominos.end(), engine);
  return tetrominos;
}

}  // namespace mytetris