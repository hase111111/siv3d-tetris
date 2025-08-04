#include "Next.h"

#include "DxLib.h"
#include "dxlib_assert.h"
#include "next_tetromino.h"

Next::Next() {
  for (int i = 0; i < 21; i++) {
    m_minos[i] = enumMino::I;
  }

  for (int i = 0; i < 21; i++) {
    getTopMino();
    mf_addNewMinoBack();
  }
}

enumMino Next::getTopMino() {
  const enumMino _result = m_minos[0];

  for (size_t i = 0; i < 21; i++) {
    if (i < 20) {
      m_minos[i] = m_minos[i + 1];
    } else {
      m_minos[i] = enumMino::none;
    }
  }

  mf_addNewMinoBack();

  if (_result == enumMino::jammer || _result == enumMino::none ||
      _result == enumMino::wall) {
    ASSERT_MUST_NOT_REACH_HERE();
  }

  return _result;
}

void Next::getDrawMino(enumMino (&_mino)[6]) const {
  for (size_t i = 0; i < 6; i++) {
    _mino[i] = m_minos[i];
  }
}

void Next::mf_addNewMinoBack() {
  // Œã‚ëŽµƒ}ƒX‚ª‹ó‚Á‚Û‚©‚Ç‚¤‚©’²‚×‚é
  for (size_t i = 0; i < 7; i++) {
    if (m_minos[14 + i] != enumMino::none) return;
  }

  int r = 0;
  for (size_t i = 0; i < 7; i++) {
    r = GetRand(6);  // 0`6‚Ì—”‚ð”­¶

    // ‹ó‚Á‚Û‚È‚ç‚Îƒ~ƒm‚ð‘}“ü
    while (true) {
      if (m_minos[14 + r] == enumMino::none) {
        // ‘}“ü
        if (i == 0)
          m_minos[14 + r] = enumMino::I;
        else if (i == 1)
          m_minos[14 + r] = enumMino::J;
        else if (i == 2)
          m_minos[14 + r] = enumMino::L;
        else if (i == 3)
          m_minos[14 + r] = enumMino::O;
        else if (i == 4)
          m_minos[14 + r] = enumMino::S;
        else if (i == 5)
          m_minos[14 + r] = enumMino::T;
        else if (i == 6)
          m_minos[14 + r] = enumMino::Z;

        break;
      }

      if (r <= 5)
        r++;
      else {
        r = 0;
      }
    }
  }
}

void Next::reset() {
  for (int i = 0; i < 21; i++) {
    m_minos[i] = enumMino::I;
  }

  for (int i = 0; i < 21; i++) {
    getTopMino();
    mf_addNewMinoBack();
  }
}
