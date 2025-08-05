// #pragma once
// #include "Define.h"
// #include "EnumTetris.h"
// #include "TetrisDefine.h"
//
// class Field {
//  public:
//   Field();
//
//   void getField(
//       enumMino (&_field)[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y])
//       const;
//   bool getTspinFlag() const;
//
//   bool setMino(const enumMino _mino, const int (&_pos)[4][2]);
//   enumDeleteLine deleteLine();
//   bool anime();
//   void reset();
//
//   static bool mf_isInField(const int _x, const int _y);
//
//  private:
//   void mf_init();
//   unsigned int m_anime_counter = 0;
//   bool m_tspin_flag;
//
//   enumMino m_field[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y];
// };