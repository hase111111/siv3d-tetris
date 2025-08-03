#include "Field.h"

#include "DxLib.h"
// #include "Image.h"
// #include "Keyboard.h"
#include "dxlib_assert.h"

Field::Field() { mf_init(); }

void Field::getField(
    enumMino (&_field)[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y]) const {
  for (int x = 0; x < TetrisDefine::FIELD_X; x++) {
    for (int y = 0; y < TetrisDefine::FIELD_Y; y++) {
      // �󂯎�����f�[�^��ύX����
      _field[x][y] = m_field[x][y];
    }
  }
}

bool Field::getTspinFlag() const {
  // if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 0) {
  //   return m_tspin_flag;
  // }

  return false;
}

/// <summary>
/// �e�g���~�m��ݒu����֐�
/// �e�g���X�̔s�k�͂��̏u�ԂɌ��肷��
/// </summary>
/// <param name="_mino">�ݒu����e�g���~�m�̎��</param>
/// <param name="_pos">�ݒu����ӏ�</param>
/// <returns>false���Ԃ�ꍇ�Q�[���I�[�o�[</returns>
bool Field::setMino(const enumMino _mino, const int (&_pos)[4][2]) {
  int _most_low_y =
      TetrisDefine::FIELD_Y;  // 21�i�ڂɐݒu�����ꍇ�Q�[���I�[�o�[
  m_tspin_flag = false;

  for (int i = 0; i < 4; i++) {
    // �t�B�[���h�O���Q�Ƃ����Ȃ�
    if (!mf_isInField(_pos[i][0], _pos[i][1])) ASSERT_MUST_NOT_REACH_HERE();

    if (m_field[_pos[i][0]][_pos[i][1]] != enumMino::none) return false;

    if (_most_low_y > _pos[i][1]) _most_low_y = _pos[i][1];

    m_field[_pos[i][0]][_pos[i][1]] = _mino;
  }

  if (_most_low_y < TetrisDefine::FIELD_Y - TetrisDefine::GAMR_OVER_Y)
    return false;

  // Tspin���̏���
  if (_mino == enumMino::T) {
    int _c = 0;
    if (m_field[_pos[0][0] - 1][_pos[0][1] - 1] != enumMino::none) {
      _c++;
    }
    if (m_field[_pos[0][0] + 1][_pos[0][1] - 1] != enumMino::none) {
      _c++;
    }
    if (m_field[_pos[0][0] - 1][_pos[0][1] + 1] != enumMino::none) {
      _c++;
    }
    if (m_field[_pos[0][0] + 1][_pos[0][1] + 1] != enumMino::none) {
      _c++;
    }

    if (_c >= 3) m_tspin_flag = true;
  }

  return true;
}

/// <summary>
/// �񂪂���������m�F���A������Ă���s���_�~�[�u���b�N�ɒu������
/// </summary>
enumDeleteLine Field::deleteLine() {
  int i = 0;
  int _delete_line = 0;

  for (int y = 2; y <= Define::FIELD_SIZEY; y++) {
    i = 0;

    for (int x = 0; x < Define::FIELD_SIZEX; x++) {
      if (m_field[x][Define::FIELD_SIZEY - y] == enumMino::none) break;
      i++;
    }

    // �񂪂�������Ƃ�
    if (i == Define::FIELD_SIZEX) {
      // �������C�������Z
      _delete_line++;

      for (int n = y; n < Define::FIELD_SIZEY; n++) {
        for (int x = 1; x < Define::FIELD_SIZEX - 1; x++) {
          // �_�~�[�u���b�N�ɒu��������
          m_field[x][Define::FIELD_SIZEY - y] = enumMino::jammer;
        }
      }
    }
  }

  // �l��Ԃ�
  if (_delete_line == 1) {
    return enumDeleteLine::oneline;
  } else if (_delete_line == 2) {
    return enumDeleteLine::twoline;
  } else if (_delete_line == 3) {
    return enumDeleteLine::threeline;
  } else if (_delete_line == 4) {
    return enumDeleteLine::tetris;
  }

  return enumDeleteLine::zero;
}

// �����o�֐�
void Field::mf_init() { reset(); }

bool Field::mf_isInField(const int _x, const int _y) {
  if (_x < 0 || _y < 0 || _x >= TetrisDefine::FIELD_X ||
      _y >= TetrisDefine::FIELD_Y) {
    return false;
  } else {
    return true;
  }
}

bool Field::anime() {
  // �_�~�[�e�g���~�m�����݂��Ȃ��Ȃ�Ώ������s��Ȃ�
  bool do_anime = false;
  for (int y = 0; y < Define::FIELD_SIZEY; y++) {
    for (int x = 0; x < Define::FIELD_SIZEX; x++) {
      if (m_field[x][y] == enumMino::jammer) {
        do_anime = true;
      }
    }
  }

  // ������������false��Ԃ�
  if (!do_anime) {
    return false;
  }

  // 5f���Ƃɏ������s��
  m_anime_counter++;
  if (m_anime_counter % 5 != 0) {
    return true;
  }

  // �_�~�[�̏����A�j���y�ї�����ɉ����鏈��
  for (int y = 0; y < Define::FIELD_SIZEY; y++) {
    for (int x = 0; x < Define::FIELD_SIZEX / 2; x++) {
      if (x < Define::FIELD_SIZEX / 2 - 2 &&
          m_field[Define::FIELD_SIZEX / 2 - 1 - x]
                 [Define::FIELD_SIZEY - y - 1] == enumMino::jammer) {
        m_field[Define::FIELD_SIZEX / 2 - 1 - x][Define::FIELD_SIZEY - y - 1] =
            enumMino::none;
        m_field[Define::FIELD_SIZEX / 2 + x][Define::FIELD_SIZEY - y - 1] =
            enumMino::none;
        break;
      } else {
        if (m_field[Define::FIELD_SIZEX / 2 - 1 - x]
                   [Define::FIELD_SIZEY - y - 1] == enumMino::jammer) {
          for (int y2 = y; y2 < Define::FIELD_SIZEY; y2++) {
            for (int x2 = 1; x2 < Define::FIELD_SIZEX - 1; x2++) {
              if (y2 == Define::FIELD_SIZEY - 1) {
                m_field[x2][Define::FIELD_SIZEY - y2 - 1] = enumMino::none;
              } else {
                m_field[x2][Define::FIELD_SIZEY - y2 - 1] =
                    m_field[x2][Define::FIELD_SIZEY - y2 - 2];
              }
            }
          }
          y -= 1;
          break;
        }
      }
    }
  }

  return true;
}

void Field::reset() {
  // �S�Ă�none�ŏ�����
  for (int x = 0; x < TetrisDefine::FIELD_X; x++) {
    for (int y = 0; y < TetrisDefine::FIELD_Y; y++) {
      m_field[x][y] = enumMino::none;
    }
  }

  // �ǂ𐶐�����
  for (int i = 0; i < TetrisDefine::FIELD_Y; i++) {
    m_field[0][i] = enumMino::wall;
    m_field[TetrisDefine::FIELD_X - 1][i] = enumMino::wall;
  }

  // ���𐶐�����
  for (int l = 0; l < TetrisDefine::FIELD_X; l++) {
    m_field[l][TetrisDefine::FIELD_Y - 1] = enumMino::wall;
  }

  m_tspin_flag = false;
  m_anime_counter = 0;
}