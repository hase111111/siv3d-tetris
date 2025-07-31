#pragma once
#include "EnumTetris.h"
#include "TetrisDefine.h"

class TetroMino final {
 public:
  TetroMino();

  void update(const int _speed = 0);
  void reset(const enumMino _mino);

  bool getFlagRockMino() const { return m_rock; }
  enumMino getMinoType() const { return m_mino; }
  void getMinoPos(int (&_meta)[4][2], const bool _get_gost = false) const;

  void setFieldDate(
      const enumMino (&_date)[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y]);

 private:
  int m_fieldx, m_fieldy;  // ミノの左上のフィールド座標
  unsigned int m_roll, m_counter, m_rock_counter, m_rock_operation_counter;
  bool m_rock;
  enumMino m_mino;
  enumMino m_fielddate[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y];

  bool mf_canSetMinoInField(const int _fieldx, const int _fieldy) const;
  bool mf_moveUniqueTurn(bool _turnleft);
  void mf_moveTurn();
  void mf_moveHorizontal();
  void mf_moveHardDrop();
  void mf_moveSoftDrop();
  void mf_moveFreeDrop(int _speed);
};
