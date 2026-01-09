#include "key_config_data.h"

#include "my_assert.h"

namespace mytetris {

KeyHandle KeyConfigData::Map(const KeyGroup key_group) const {
  switch (key_group) {
    case KeyGroup::kLeft:
      return move_left_key;
    case KeyGroup::kRight:
      return move_right_key;
    case KeyGroup::kDown:
      return soft_drop_key;
    case KeyGroup::kUp:
      return hard_drop_key;
    case KeyGroup::kRotateCW:
      return rotate_cw_key;
    case KeyGroup::kRotateCCW:
      return rotate_ccw_key;
    case KeyGroup::kHold:
      return hold_key;
    case KeyGroup::kPause:
      return pause_key;
    case KeyGroup::kDecide:
      return decide_key;
    case KeyGroup::kRestart:
      return restart_key;
    case KeyGroup::kToMenu:
      return to_menu_key;
    case KeyGroup::kGameEnd:
      return game_end_key;
    default:
      // Ç±Ç±Ç…ÇÕóàÇ»Ç¢ÇÕÇ∏ÅD
      //! @todo C++ÇÃédólè„Ç±Ç±Ç…óàÇƒÇµÇ‹Ç§.
      DEBUG_ASSERT_MUST_NOT_REACH_HERE();
      return KeyHandle::kEscape;
  }
}

}  // namespace mytetris
