#include "Fps.h"

#include "CalcUtils.h"
#include "Define.h"
#include "DxLib.h"

const static int LIST_LEN_MAX =
    120;  // �ő�120�t���[���őҋ@�������v�Z����(2�ȏ�ɂ���)
const static int FPS = 60;      // FPS
const static int UPINTVL = 60;  // 60�t���[���Ɉ�x�X�V����

Fps::Fps() : _counter(0), _fps(60.0f) {}

void Fps::wait() {
  _counter++;
  Sleep(getWaitTime());  // �҂ׂ����Ԃ��擾���đ҂�
  regist();
  if (_counter == UPINTVL) {  // �X�V�^�C�~���O��1�񕽋ϒl���X�V����
    updateAverage();
    _counter = 0;
  }
}

void Fps::draw() const {
  if (_fps == 0.0f) {
    return;
  }

  size_t _strlen = strlen("1000fps");
  int _strdxlen = GetDrawStringWidth("1000fps", (int)_strlen);
  DrawFormatString(Define::WIN_SIZEX - _strdxlen, Define::WIN_SIZEY - 15,
                   GetColor(255, 255, 255), "%04.1ffps", _fps);
}

void Fps::regist() {
  _list.push_back(GetNowCount());     // ���݂̎������L��
  if (_list.size() > LIST_LEN_MAX) {  // �킩��R�ꂽ��|�b�v
    _list.pop_front();
  }
}

unsigned Fps::getWaitTime() const {
  int len = (int)_list.size();
  if (len == 0) {
    return 0;
  }
  int shouldTookTime = (int)(1000 / 60.f * (len));  // �v�Z�ォ����ׂ�����
  int actuallyTookTime = GetNowCount() - _list.front();  // ���ۂɂ�����������
  int waitTime =
      shouldTookTime -
      actuallyTookTime;  // �v�Z�ォ����ׂ����� -
                         // ���ۂɂ����������ԁ@�͂��Ȃ킿�҂ׂ�����
  waitTime = waitTime > 0 ? waitTime : 0;
  return (unsigned)(waitTime);
}

void Fps::updateAverage() {
  int len = (int)_list.size();
  if (len <
      LIST_LEN_MAX) {  // �܂����ς��v�Z���郌�x���ɂ܂ł��܂��Ă��Ȃ���Όv�Z���Ȃ�
    return;
  }
  int tookTime =
      _list.back() - _list.front();  // LIST_LEN_MAX�t���[���ɂ�����������
  float average = (float)tookTime / (len - 1);  // ���ς����
  if (average == 0) {                           // 0����h�~
    return;
  }
  _fps = CalcUtils::roundPoint(1000 / average, 2);  // �����_��2�ʂŎl�̌ܓ�����
}
