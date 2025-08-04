//
// #include "Field.h"
// #include "TetroMino.h"
//
// bool TetroMino::mf_canSetMinoInField(const int _fieldx,
//                                     const int _fieldy) const {
//  switch (m_mino) {
//    case enumMino::O:
//      if (m_fielddate[_fieldx + 0][_fieldy + 0] != enumMino::none) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//        return false;
//      }
//      break;
//    case enumMino::S:
//      if (m_roll % 4 == 0) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 1) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 2) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 3) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      }
//      break;
//    case enumMino::Z:
//      if (m_roll % 4 == 0) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 1) {
//        if (m_fielddate[_fieldx + 2][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 2) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 3) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      }
//      break;
//    case enumMino::J:
//      if (m_roll % 4 == 0) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 1) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 2) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 3) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      }
//      break;
//    case enumMino::L:
//      if (m_roll % 4 == 0) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 1) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 2) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 3) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 0][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//      }
//      break;
//    case enumMino::T:
//      if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none &&
//          m_roll % 4 != 2) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none &&
//          m_roll % 4 != 1) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none &&
//          m_roll % 4 != 0) {
//        return false;
//      }
//      if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none &&
//          m_roll % 4 != 3) {
//        return false;
//      }
//      break;
//    case enumMino::I:
//      if (m_roll % 4 == 0) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 3][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 1) {
//        if (m_fielddate[_fieldx + 2][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 3] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 2) {
//        if (m_fielddate[_fieldx + 0][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 2][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 3][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//      } else if (m_roll % 4 == 3) {
//        if (m_fielddate[_fieldx + 1][_fieldy + 0] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 1] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 2] != enumMino::none) {
//          return false;
//        }
//        if (m_fielddate[_fieldx + 1][_fieldy + 3] != enumMino::none) {
//          return false;
//        }
//      }
//      break;
//    default:
//      break;
//  }
//  return true;
//}
