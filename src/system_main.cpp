
//! @file system_main.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "system_main.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif

#include "game_const.h"
#include "game_main_loop.h"

namespace mytetris {

#if defined DXLIB_COMPILE

bool SystemMain::Initialize() {
  // �ݒ�t�@�C����ǂݍ��ށD
  game_setting_record_ptr_ = std::make_shared<GameSettingRecord>();

  // icon.rc�Őݒ肵���A�C�R���t�@�C�����Z�b�g����D
  DxLib::SetWindowIconID(333);

  DxLib::SetUseCharCodeFormat(
      DX_CHARCODEFORMAT_UTF8);             // �����R�[�h��UTF-8�ɐݒ肷��D
  SetWindowText(GameConst::kWindowTitle);  // �E�B���h�E�^�C�g����t����D
  DxLib::SetAlwaysRunFlag(TRUE);  // �E�B���h�E���m���A�N�e�B�u�ł����s�D
  DxLib::SetOutApplicationLogValidFlag(FALSE);  // ���O�o�͂��Ȃ��D
  DxLib::SetDoubleStartValidFlag(FALSE);        // ��d�N���������Ȃ��D
  DxLib::SetMainWindowClassName(
      kWindowClassName.c_str());  // �E�B���h�E�̃N���X����ݒ肷��D

  // �Q�[����ʂ̉𑜓x��ݒ肷��D
  // �F�� bit ���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���D
  const int color_bit = 32;
  DxLib::SetGraphMode(GameConst::kResolutionX, GameConst::kResolutionY,
                      color_bit);

  // �t���X�N���[���ݒ�D
  if (true) {
    // �E�B���h�E���[�h�ŋN������ꍇ�D
    DxLib::ChangeWindowMode(TRUE);

    // �E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���D
    DxLib::SetWindowSizeChangeEnableFlag(FALSE, FALSE);

    // ��ʃT�C�Y�ݒ�D
    const double ex_rate = 960.0 / static_cast<double>(GameConst::kResolutionX);

    // �E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��D
    DxLib::SetWindowSizeExtendRate(ex_rate);
  }

  // DX���C�u���������������D
  if (DxLib::DxLib_Init() < 0) {
    // �ُ�I�������瑦���ɂ�߂�D
    return false;
  }

  DxLib::SetSysCommandOffFlag(TRUE);     // ALT�𖳌��ɂ���D
  DxLib::SetDrawScreen(DX_SCREEN_BACK);  // ����ʏ�����ݒ肷��D
  DxLib::SetLogFontSize(30);             // ���O�̃t�H���g�T�C�Y��ݒ肷��D
  return true;
}

void SystemMain::Finalize() const {
  // DxLib�̏I���������ĂԁD
  DxLib::DxLib_End();
}

void SystemMain::Main() const {
  if (DxLib::DxLib_IsInit() < 0) {
    // DxLib������������Ă��Ȃ��ꍇ�͉������Ȃ��D
    return;
  }

  GameMainLoop game_main_loop(game_setting_record_ptr_);

  // ���C�����[�v�D
  while (!(DxLib::ProcessMessage() > 0)) {
    if (!game_main_loop.Loop()) {
      break;
    }
  }
}

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

bool SystemMain::Initialize() {
  game_setting_record_ptr_ = std::make_shared<GameSettingRecord>();

  // �E�B���h�E�^�C�g����ݒ肷��D

  // �E�B���h�E�̃T�C�Y��ݒ肷��D
  Window::Resize(GameConst::kResolutionX, GameConst::kResolutionY);

  // �E�B���h�E�̔w�i�F��ݒ肷��D
  Scene::SetBackground(ColorF{0.0f, 0.0f, 0.0f});

#if !defined __EMSCRIPTEN__
  Graphics::SetVSyncEnabled(false);
#endif

  return true;
}

void SystemMain::Main() const {
  GameMainLoop game_main_loop(game_setting_record_ptr_);
  while (System::Update()) {
    if (!game_main_loop.Loop()) {
      break;
    }
  }
}

void SystemMain::Finalize() const {}

#endif

}  // namespace mytetris
