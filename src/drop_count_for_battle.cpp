//! @file drop_count_for_battle.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "drop_count_for_battle.h"

namespace mytetris {

int DropCountForBattle::GetCount(int) const {
  // Battle モードでは固定で75フレームに1回落下.
  return 75;
}

std::string DropCountForBattle::GetDisplaySpeed(int) const {
  // Battle モードでは速度表示は不要.
  return "";
}

}  // namespace mytetris
