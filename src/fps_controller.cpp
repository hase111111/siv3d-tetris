//! @file fps_controller.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "fps_controller.h"

#if defined(DXLIB_COMPILE)
#include <Dxlib.h>
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include <cmath>
#include <string>

#include "game_const.h"

namespace mytetris {

FpsController::FpsController(const int target_fps)
    : target_fps_value_(target_fps),
      one_frame_time_(static_cast<int>(1000.0 / target_fps)),
      list_max_(target_fps * 2),
      need_skip_draw_screen_(false) {}

void FpsController::Wait() {
  if (!TargetFpsIsValid()) {
    return;
  }

  // �҂ׂ����Ԃ��擾���đ҂D
  int wait_time = 0;

  if (CheckNeedSkipDrawScreen(&wait_time)) {
#if defined(DXLIB_COMPILE)
    WaitTimer(wait_time);  // �擾�������ԕ��҂D

    RegisterTime(GetNowCount());  // ���݂̎������L�^����D

#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

    s3d::System::Sleep(wait_time);
    RegisterTime(
        static_cast<int>(s3d::Time::GetMillisec()));  // ���݂̎������L�^����D

#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

  } else {
    // ���ԃI�[�o�[���Ă���̂ŁC�R�}�����̏���������D

    // ���̃t���[���͗��z�I�ȏ������������̂Ƃ��āC�L�^����D
    RegisterTime(time_list_.back() + one_frame_time_);

    need_skip_draw_screen_ = true;  // �`����΂��t���O�𗧂Ă�D
  }
}

bool FpsController::SkipDrawScene() {
  if (!TargetFpsIsValid()) {
    return false;
  }

  // �X�L�b�v�t���O�������Ă���Ȃ�΁C���̃t���O��܂�C�V�[�����X�L�b�v����D
  if (need_skip_draw_screen_) {
    need_skip_draw_screen_ = false;
    return true;
  }

  return false;
}

void FpsController::RegisterTime(const int now_time) {
  time_list_.push_back(now_time);  // ���݂̎������L���D

  if (time_list_.size() > list_max_) {
    // �킩��R�ꂽ��폜����D
    time_list_.pop_front();
  }
}

bool FpsController::CheckNeedSkipDrawScreen(int* time) const {
  // �������������D
  (*time) = 0;

  // �������X�g����Ȃ�CWait���Ԃ�0�b�D
  if (time_list_.empty()) {
    (*time) = 0;
    return true;
  }

  // ���ۂɂ����������Ԃ����߂�D
#if defined DXLIB_COMPILE
  int actually_took_time = GetNowCount() - time_list_.back();
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
  int actually_took_time =
      static_cast<int>(s3d::Time::GetMillisec()) - time_list_.back();
#endif  // defined DXLIB_COMPILE

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

bool FpsController::TargetFpsIsValid() const {
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
