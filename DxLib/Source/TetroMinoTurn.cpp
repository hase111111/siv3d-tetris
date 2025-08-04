// #include "TetroMino.h"
//
// bool TetroMino::mf_moveUniqueTurn(bool _turnleft) {
//   const int _x = m_fieldx;
//   const int _y = m_fieldy;
//   const int _r = m_roll;
//
//   switch (m_mino) {
//     case enumMino::O:
//       return true;
//       break;
//     case enumMino::L:
//     case enumMino::J:
//     case enumMino::S:
//     case enumMino::Z:
//     case enumMino::T:
//       if (_turnleft) {
//         m_roll += 3;
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 左右に軸をずらす
//         if (m_roll % 4 == 3 || m_roll % 4 == 0) {
//           m_fieldx += 1;
//         } else {
//           m_fieldx -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 上下に軸をずらす
//         if (m_roll % 4 == 0 || m_roll % 4 == 2) {
//           m_fieldy += 1;
//         } else {
//           m_fieldy -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 元に戻して上下に２つずらす
//         m_fieldx = _x;
//         m_fieldy = _y;
//         if (m_roll % 4 == 0 || m_roll % 4 == 2) {
//           m_fieldy -= 2;
//         } else {
//           m_fieldy += 2;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 左右に軸をずらす
//         if (m_roll % 4 == 3 || m_roll % 4 == 0) {
//           m_fieldx += 1;
//         } else {
//           m_fieldx -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//       } else {
//         m_roll++;
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 左右に軸をずらす
//         if (m_roll % 4 == 3 || m_roll % 4 == 2) {
//           m_fieldx += 1;
//         } else {
//           m_fieldx -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 上下に軸をずらす
//         if (m_roll % 4 == 0 || m_roll % 4 == 2) {
//           m_fieldy += 1;
//         } else {
//           m_fieldy -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 元に戻して上下２
//         m_fieldx = _x;
//         m_fieldy = _y;
//         if (m_roll % 4 == 0 || m_roll % 4 == 2) {
//           m_fieldy -= 2;
//         } else {
//           m_fieldy += 2;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 左右に軸をずらす
//         if (m_roll % 4 == 3 || m_roll % 4 == 2) {
//           m_fieldx += 1;
//         } else {
//           m_fieldx -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//       }
//       break;
//     case enumMino::I:
//       if (_turnleft) {
//         m_roll += 3;
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 1
//         if (m_roll % 4 == 1 || m_roll % 4 == 2) {
//           m_fieldx += 1;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx -= 1;
//         } else if (m_roll % 4 == 0) {
//           m_fieldx += 2;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 2
//         if (m_roll % 4 == 0) {
//           m_fieldx -= 3;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx -= 3;
//         } else if (m_roll % 4 == 2) {
//           m_fieldx -= 3;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx += 3;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 3
//         if (m_roll % 4 == 0) {
//           m_fieldx += 3;
//           m_fieldy -= 1;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx += 3;
//           m_fieldy += 2;
//         } else if (m_roll % 4 == 2) {
//           m_fieldy += 1;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx -= 3;
//           m_fieldy -= 2;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 4
//         if (m_roll % 4 == 0) {
//           m_fieldx -= 3;
//           m_fieldy += 3;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx -= 3;
//           m_fieldy -= 3;
//         } else if (m_roll % 4 == 2) {
//           m_fieldx += 3;
//           m_fieldy -= 3;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx += 3;
//           m_fieldy += 3;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//       } else {
//         m_roll++;
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 1
//         if (m_roll % 4 == 0) {
//           m_fieldx -= 2;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx -= 2;
//         } else if (m_roll % 4 == 2) {
//           m_fieldx -= 1;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx += 2;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 2
//         if (m_roll % 4 == 0) {
//           m_fieldx += 3;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx += 3;
//         } else if (m_roll % 4 == 2) {
//           m_fieldx += 3;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx -= 3;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 3
//         if (m_roll % 4 == 0) {
//           m_fieldx += 0;
//           m_fieldy += 2;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx -= 3;
//           m_fieldy += 1;
//         } else if (m_roll % 4 == 2) {
//           m_fieldy -= 3;
//           m_fieldy -= 2;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx += 3;
//           m_fieldy -= 1;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//
//         // 4
//         if (m_roll % 4 == 0) {
//           m_fieldx -= 3;
//           m_fieldy -= 3;
//         } else if (m_roll % 4 == 1) {
//           m_fieldx += 3;
//           m_fieldy -= 3;
//         } else if (m_roll % 4 == 2) {
//           m_fieldx += 3;
//           m_fieldy += 3;
//         } else if (m_roll % 4 == 3) {
//           m_fieldx -= 3;
//           m_fieldy += 3;
//         }
//         if (mf_canSetMinoInField(m_fieldx, m_fieldy)) return true;
//       }
//       break;
//     default:
//       break;
//   }
//
//   // 回転していないならfalseを返しデータを元に戻す
//   m_fieldx = _x;
//   m_fieldy = _y;
//   m_roll = _r;
//
//   return false;
// }