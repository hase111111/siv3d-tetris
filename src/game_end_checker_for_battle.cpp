#include "game_end_checker_for_battle.h"

#include "my_assert.h"

namespace mytetris {

GameEndCheckerForBattle::GameEndCheckerForBattle(
    const std::shared_ptr<TetrisField>& enemy_field)
    : enemy_field_ptr_(enemy_field) {
  // nullptr チェック.
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_field);
  DEBUG_ASSERT_NOT_NULL_PTR(enemy_field_ptr_);
}

bool GameEndCheckerForBattle::IsGameEnd() const {
  return enemy_field_ptr_->IsGameOver();
}

void GameEndCheckerForBattle::SetGameMode(const TetrisGameMode) {}

}  // namespace mytetris
