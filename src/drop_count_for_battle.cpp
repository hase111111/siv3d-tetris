//! @file drop_count_for_battle.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "drop_count_for_battle.h"

namespace mytetris {

int DropCountForBattle::GetCount(int) const {
  // Battle ���[�h�ł͌Œ��75�t���[����1�񗎉�.
  return 75;
}

std::string DropCountForBattle::GetDisplaySpeed(int) const {
  // Battle ���[�h�ł͑��x�\���͕s�v.
  return "";
}

}  // namespace mytetris
