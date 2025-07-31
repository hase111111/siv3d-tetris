#include "TetroMino.h"

#include "DxLib.h"
#include "Keyboard.h"
#include "dxlib_assert.h"

TetroMino::TetroMino()
    : m_fieldx(5),
      m_fieldy(2),
      m_roll(0),
      m_counter(TetrisDefine::MINO_FALL_COUNT[1]),
      m_rock_counter(0),
      m_rock_operation_counter(0),
      m_rock(false),
      m_mino(enumMino::none) {
  for (int x = 0; x < TetrisDefine::FIELD_X; x++) {
    for (int y = 0; y < TetrisDefine::FIELD_Y; y++) {
      m_fielddate[x][y] = enumMino::none;
    }
  }
}

void TetroMino::update(const int _speed) {
  if (m_mino == enumMino::none) ASSERT_MUST_NOT_REACH_HERE();

  mf_moveHardDrop();        // ��{�^���������ꂽ���̏���
  mf_moveSoftDrop();        // ���{�^���������ꂽ���̏���
  mf_moveHorizontal();      // ���E�{�^���������ꂽ���̑���
  mf_moveTurn();            // ��]����
  mf_moveFreeDrop(_speed);  // ���R����
}

void TetroMino::reset(const enumMino _mino) {
  // �S�Ẵ����o�ϐ�������������
  m_mino = _mino;
  m_roll = 0;
  m_counter = TetrisDefine::MINO_FALL_COUNT[1];
  m_rock_counter = 0;
  m_rock_operation_counter = 0;
  m_rock = false;

  switch (_mino) {
    case enumMino::O:
      m_fieldx = 5;
      m_fieldy = 1;
      break;
    case enumMino::S:
    case enumMino::T:
    case enumMino::Z:
    case enumMino::L:
    case enumMino::J:
    case enumMino::I:
      m_fieldx = 4;
      m_fieldy = 1;
      break;
    default:
      ASSERT_MUST_NOT_REACH_HERE();
      break;
  }
}

void TetroMino::setFieldDate(
    const enumMino (&_date)[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y]) {
  for (int x = 0; x < TetrisDefine::FIELD_X; x++) {
    for (int y = 0; y < TetrisDefine::FIELD_Y; y++) {
      // �󂯎�����f�[�^��ύX����
      m_fielddate[x][y] = _date[x][y];
    }
  }
}

void TetroMino::mf_moveTurn() {
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) == 1) {
    // ��]�����̂Ȃ�ΌŒ蒆����J�E���^���񂵌Œ�J�E���^������������
    if (mf_moveUniqueTurn(true)) {
      m_rock_operation_counter++;
      m_rock_counter = 0;
    }
  } else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_D) == 1) {
    // ��]�����̂Ȃ�ΌŒ蒆����J�E���^���񂵌Œ�J�E���^������������
    if (mf_moveUniqueTurn(false)) {
      m_rock_operation_counter++;
      m_rock_counter = 0;
    }
  }
}

void TetroMino::mf_moveHorizontal() {
  // ���{�^���������ꂽ��
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) >= 1) {
    // �����ꂽ�u�Ԃ܂��́i�C���^�[�o�����Ԉȏ㉟����Ă��邩���������ԁ[�C���^�[�o�����Ԋ���J�E���^�̗]�肪�O�j
    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 ||
        (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) >
             TetrisDefine::MINO_HORIZONTAL_INTERVAL &&
         (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) -
          TetrisDefine::MINO_HORIZONTAL_INTERVAL) %
                 TetrisDefine::MINO_HORIZONTAL_COUNT ==
             0)) {
      // �ړ�����
      if (mf_canSetMinoInField(m_fieldx - 1, m_fieldy)) {
        m_fieldx -= 1;       // �ړ��\�Ȃ�Έړ�����
        m_rock_counter = 0;  // �Œ�J�E���^������������

        // �n�ʂɑ���t�����܂܂Ȃ�Α���J�E���^����
        if (!mf_canSetMinoInField(m_fieldx + 1, m_fieldy + 1) &&
            !mf_canSetMinoInField(m_fieldx, m_fieldy + 1))
          m_rock_operation_counter++;
      }
    }
  } else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) >= 1) {
    // �����ꂽ�u�Ԃ܂��́i�C���^�[�o�����Ԉȏ㉟����Ă��邩���������ԁ[�C���^�[�o�����Ԋ���J�E���^�̗]�肪�O�j
    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1 ||
        (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) >
             TetrisDefine::MINO_HORIZONTAL_INTERVAL &&
         (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) -
          TetrisDefine::MINO_HORIZONTAL_INTERVAL) %
                 TetrisDefine::MINO_HORIZONTAL_COUNT ==
             0)) {
      // �ړ�����
      if (mf_canSetMinoInField(m_fieldx + 1, m_fieldy)) {
        m_fieldx += 1;       // �ړ��\�Ȃ�Έړ�����
        m_rock_counter = 0;  // �Œ�J�E���^������������

        // �n�ʂɑ���t�����܂܂Ȃ�Α���J�E���^����
        if (!mf_canSetMinoInField(m_fieldx + 1, m_fieldy + 1) &&
            !mf_canSetMinoInField(m_fieldx, m_fieldy + 1))
          m_rock_operation_counter++;
      }
    }
  }
}

void TetroMino::mf_moveHardDrop() {
  // ��{�^���������ꂽ�u�ԂłȂ���ΏI������
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) != 1) {
    return;
  }

  m_rock = true;  // �n�ʂɌŒ�

  // �������u���b�N�łȂ����胋�[�v
  int loop_jammer = 0;
  while (mf_canSetMinoInField(m_fieldx, m_fieldy + 1)) {
    m_fieldy += 1;  // ���ɉ�����

    loop_jammer++;
    if (TetrisDefine::FIELD_Y < loop_jammer) {
      ASSERT_MUST_NOT_REACH_HERE();
    }
  }
}

void TetroMino::mf_moveSoftDrop() {
  // ���L�[��������Ă���Ȃ��
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) > 0) {
    // 20�{�̑��x�ŗ�������
    m_counter += 19;
  }
}

void TetroMino::mf_moveFreeDrop(int speed) {
  // �����\
  if (mf_canSetMinoInField(m_fieldx, m_fieldy + 1)) {
    m_rock_counter = 0;  // �Œ�J�E���^������������
    m_counter++;         // �����J�E���^����

    if (speed > 9 || speed < 0) {
      speed = 9;
    }  // 9������Ȃ��9�Ɋۂ߂�

    if (m_counter > TetrisDefine::MINO_FALL_COUNT[speed]) {
      m_fieldy += 1;
      m_counter = 0;
    }
  }
  // �����s�\
  else {
    m_counter = 0;     // �����J�E���^������������
    m_rock_counter++;  // �Œ�J�E���^�����Z

    // �������ɒB�����̂Ȃ�ΌŒ�
    if (m_rock_operation_counter >= 15) m_rock = true;

    // �Œ莞�ԂɒB�����̂Ȃ��
    if (m_rock_counter > TetrisDefine::MINO_ROCK_COUNT) m_rock = true;
    ;
  }
}
