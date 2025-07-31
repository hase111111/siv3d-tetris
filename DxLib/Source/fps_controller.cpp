
#include "fps_controller.h"

#include <Dxlib.h>

#include <cmath>
#include <string>

#include "game_const.h"

namespace mytetris {

FpsController::FpsController(const int target_fps)
    : target_fps_value_(target_fps),
      one_frame_time_(static_cast<int>(1000.0 / target_fps)),
      list_max_(target_fps * 2),
      need_skip_draw_screen_(false) {}

void FpsController::wait() {
  if (!targetFpsIsValid()) {
    return;
  }

  // �҂ׂ����Ԃ��擾���đ҂D
  int wait_time = 0;

  if (checkNeedSkipDrawScreen(&wait_time)) {
    WaitTimer(wait_time);  // �擾�������ԕ��҂D
    // Sleep(wait_time);    // windows API�ŁD

    registerTime(GetNowCount());  // ���݂̎������L�^����D
  } else {
    // ���ԃI�[�o�[���Ă���̂ŁC�R�}�����̏���������D

    // ���̃t���[���͗��z�I�ȏ������������̂Ƃ��āC�L�^����D
    registerTime(time_list_.back() + one_frame_time_);

    need_skip_draw_screen_ = true;  // �`����΂��t���O�𗧂Ă�D
  }
}

bool FpsController::skipDrawScene() {
  if (!targetFpsIsValid()) {
    return false;
  }

  // �X�L�b�v�t���O�������Ă���Ȃ�΁C���̃t���O��܂�C�V�[�����X�L�b�v����D
  if (need_skip_draw_screen_) {
    need_skip_draw_screen_ = false;
    return true;
  }

  return false;
}

double FpsController::getCurrentFps() const {
  if (!targetFpsIsValid()) {
    return -1.0;
  }

  // ���݂�FPS�����߂�D
  if (time_list_.size() < 2) {
    return -1.0;
  }

  const double duration = (time_list_.back() - time_list_.front()) /
                          static_cast<double>(list_max_ - 1);

  return 1000.0 / duration;
}

void FpsController::registerTime(const int now_time) {
  time_list_.push_back(now_time);  // ���݂̎������L���D

  if (time_list_.size() > list_max_) {
    // �킩��R�ꂽ��폜����D
    time_list_.pop_front();
  }
}

bool FpsController::checkNeedSkipDrawScreen(int* time) const {
  // �������������D
  (*time) = 0;

  // �������X�g����Ȃ�CWait���Ԃ�0�b�D
  if (time_list_.empty()) {
    (*time) = 0;
    return true;
  }

  // ���ۂɂ����������Ԃ����߂�D
  int actually_took_time = GetNowCount() - time_list_.back();

  // �v�Z�ォ����ׂ����� - ���ۂɂ����������ԁ@�͂��Ȃ킿�҂ׂ����ԁD
  int wait_time = one_frame_time_ - actually_took_time;

  if (wait_time >= 0) {
    // �҂����Ԃ����̒l�ł���Ƃ��C
    // (�܂�C������ׂ����Ԃ����ۂɂ����������Ԃ���������)�͂��̂܂ܒl��Ԃ��D

    (*time) = wait_time;
    return true;
  } else {
    // �҂����Ԃ����̒l�ł���Ƃ��D

    if (static_cast<int>(abs(wait_time)) < one_frame_time_) {
      // �P�t���[���ȏ�x��Ă��Ȃ��Ȃ�΁C�������s���D
      return false;
    }
  }

  // �ǂ�ɂ�����������Ȃ������ꍇ�O��Ԃ��D
  (*time) = 0;
  return true;
}

bool FpsController::targetFpsIsValid() const {
  // �}�C�i�X�̒l�͋��e���Ȃ��D
  if (target_fps_value_ <= 0) {
    return false;
  }

  // �P�b�ԂɂP�t���[���ȏ�͋��e���Ȃ��D
  if (target_fps_value_ > 60) {
    return false;
  }

  return true;
}

}  // namespace mytetris
