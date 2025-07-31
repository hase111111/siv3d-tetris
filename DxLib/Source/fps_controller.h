
//! @file fps_controller.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <list>

namespace mytetris {

//! @class FpsController
//! @brief FPS�����ɃL�[�v���邽�߂̃N���X�D
//! @details
//! ��{�I�ɂ͉������Ȃ��Ƃ�FPS�͈��ɂȂ�̂����C
//! 144Fps��240Fps���x�̃Q�[�~���O���j�^�[���g���Ă���ꍇ�C
//! ��ʂ����������Ȃ邱�Ƃ�����D
//! @n ����Ă��̃N���X���g����FPS�𐧌䂷��D
//! FPS�� Frames per Second�F1�b������̉�ʍX�V�񐔂̂��ƁD
//! First Person Shooting�̂��Ƃł͂Ȃ��D
//! @n
//! ������PC�̃��j�^�[�̖��Ȃ̂ŁC�K�v�Ȃ��Ȃ�Ώ����Ă��܂��Ă����܂�Ȃ����C
//! �������Ƃ���Ŗ��͂Ȃ��̂ŕ��u���Ă����Ă�����č\��Ȃ��D
class FpsController final {
 public:
  FpsController() = delete;
  explicit FpsController(int target_fps);

  //! @brief ��������������ꍇ�CFPS�����ɂ��邽�߂ɑ҂D
  void wait();

  //! @brief 60Hz�ȏ�̃��j�^�[�g�p���ɏ������l�܂��ĉ�ʂ�������Ȃ��悤�ɁC
  //! �`�揈�����X�L�b�v���邩�ǂ����𔻒肷��D
  //! @return �������l�܂��ĕ`����΂������Ƃ���
  //!  true ��Ԃ��D���̌�t���O�� false �ɂ���D
  bool skipDrawScene();

  //! @brief ���݂�FPS��Ԃ��֐��D
  //! @return ���݂�FPS�D
  double getCurrentFps() const;

 private:
  //! @brief ���݂̎������L�^����֐��D
  //! @param[in] now_time ���݂̎���(�~���b)
  void registerTime(int now_time);

  //! @brief �ǂꂾ���҂Ă΂悢���Ԃ��֐��D
  //! �܂��C�R�}�������Ă��邩�ǂ��������肷��D
  //! @note �@�\��2����̂ŕ������ق����悢�D
  //! @param[out] wait_time �҂ׂ����� (�~���b)�D
  //! @return �R�}�������Ă���ꍇ�� false�D
  bool checkNeedSkipDrawScreen(int* wait_time) const;

  //! @brief �ڕW��FPS�����������ǂ����𔻒肷��֐��D
  //! @return ���̒l�C�܂���60���傫���l�ł���� false�D
  bool targetFpsIsValid() const;

  //! �ڕW��FPS�C�����l�� 60 or 30�DDxLib �̎g�p�� 60 ������l�𐄏����Ȃ��D
  const int target_fps_value_;

  //! 1�t���[��������ɂ����鎞��(�~���b)
  const int one_frame_time_;

  //! ���X�g��2�b���̃t���[�����Ƃɂ����������Ԃ��L�^���邽�߁C
  //! ���X�g�̍ő�T�C�Y�����߂�D
  const int list_max_;

  //! 1�t���[�����Ƃɂ����������Ԃ��L�^���郊�X�g�D
  std::list<int> time_list_;

  //! �R�}�������������邽�߂̃t���O�D
  //! true�ł���� 1�t���[���`����΂��C���̌�t���O��܂�
  bool need_skip_draw_screen_;
};

}  // namespace mytetris
