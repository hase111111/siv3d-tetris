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

  mf_moveHardDrop();        // 上ボタンが押された時の処理
  mf_moveSoftDrop();        // 下ボタンが押された時の処理
  mf_moveHorizontal();      // 左右ボタンが押された時の操作
  mf_moveTurn();            // 回転処理
  mf_moveFreeDrop(_speed);  // 自由落下
}

void TetroMino::reset(const enumMino _mino) {
  // 全てのメンバ変数を初期化する
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
      // 受け取ったデータを変更する
      m_fielddate[x][y] = _date[x][y];
    }
  }
}

void TetroMino::mf_moveTurn() {
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) == 1) {
    // 回転したのならば固定中操作カウンタを回し固定カウンタを初期化する
    if (mf_moveUniqueTurn(true)) {
      m_rock_operation_counter++;
      m_rock_counter = 0;
    }
  } else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_D) == 1) {
    // 回転したのならば固定中操作カウンタを回し固定カウンタを初期化する
    if (mf_moveUniqueTurn(false)) {
      m_rock_operation_counter++;
      m_rock_counter = 0;
    }
  }
}

void TetroMino::mf_moveHorizontal() {
  // 左ボタンが押された時
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) >= 1) {
    // 押された瞬間または（インターバル時間以上押されているかつ押した時間ーインターバル時間割るカウンタの余りが０）
    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 ||
        (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) >
             TetrisDefine::MINO_HORIZONTAL_INTERVAL &&
         (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) -
          TetrisDefine::MINO_HORIZONTAL_INTERVAL) %
                 TetrisDefine::MINO_HORIZONTAL_COUNT ==
             0)) {
      // 移動処理
      if (mf_canSetMinoInField(m_fieldx - 1, m_fieldy)) {
        m_fieldx -= 1;       // 移動可能ならば移動する
        m_rock_counter = 0;  // 固定カウンタを初期化する

        // 地面に足を付けたままならば操作カウンタを回す
        if (!mf_canSetMinoInField(m_fieldx + 1, m_fieldy + 1) &&
            !mf_canSetMinoInField(m_fieldx, m_fieldy + 1))
          m_rock_operation_counter++;
      }
    }
  } else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) >= 1) {
    // 押された瞬間または（インターバル時間以上押されているかつ押した時間ーインターバル時間割るカウンタの余りが０）
    if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1 ||
        (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) >
             TetrisDefine::MINO_HORIZONTAL_INTERVAL &&
         (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) -
          TetrisDefine::MINO_HORIZONTAL_INTERVAL) %
                 TetrisDefine::MINO_HORIZONTAL_COUNT ==
             0)) {
      // 移動処理
      if (mf_canSetMinoInField(m_fieldx + 1, m_fieldy)) {
        m_fieldx += 1;       // 移動可能ならば移動する
        m_rock_counter = 0;  // 固定カウンタを初期化する

        // 地面に足を付けたままならば操作カウンタを回す
        if (!mf_canSetMinoInField(m_fieldx + 1, m_fieldy + 1) &&
            !mf_canSetMinoInField(m_fieldx, m_fieldy + 1))
          m_rock_operation_counter++;
      }
    }
  }
}

void TetroMino::mf_moveHardDrop() {
  // 上ボタンが押された瞬間でなければ終了する
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) != 1) {
    return;
  }

  m_rock = true;  // 地面に固定

  // 足元がブロックでない限りループ
  int loop_jammer = 0;
  while (mf_canSetMinoInField(m_fieldx, m_fieldy + 1)) {
    m_fieldy += 1;  // 下に下げる

    loop_jammer++;
    if (TetrisDefine::FIELD_Y < loop_jammer) {
      ASSERT_MUST_NOT_REACH_HERE();
    }
  }
}

void TetroMino::mf_moveSoftDrop() {
  // 下キーが押されているならば
  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) > 0) {
    // 20倍の速度で落下する
    m_counter += 19;
  }
}

void TetroMino::mf_moveFreeDrop(int speed) {
  // 落下可能
  if (mf_canSetMinoInField(m_fieldx, m_fieldy + 1)) {
    m_rock_counter = 0;  // 固定カウンタを初期化する
    m_counter++;         // 落下カウンタを回す

    if (speed > 9 || speed < 0) {
      speed = 9;
    }  // 9を上回るならば9に丸める

    if (m_counter > TetrisDefine::MINO_FALL_COUNT[speed]) {
      m_fieldy += 1;
      m_counter = 0;
    }
  }
  // 落下不可能
  else {
    m_counter = 0;     // 落下カウンタを初期化する
    m_rock_counter++;  // 固定カウンタを加算

    // 操作上限に達したのならば固定
    if (m_rock_operation_counter >= 15) m_rock = true;

    // 固定時間に達したのならば
    if (m_rock_counter > TetrisDefine::MINO_ROCK_COUNT) m_rock = true;
    ;
  }
}
