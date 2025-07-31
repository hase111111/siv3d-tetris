
//! @file system_main.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "system_main.h"

#include <DxLib.h>

#include "game_const.h"
#include "game_main_loop.h"

namespace mytetris {

bool SystemMain::Initialize() {
  // 設定ファイルを読み込む．
  game_setting_record_ptr_ = std::make_shared<GameSettingRecord>();

  // icon.rcで設定したアイコンファイルをセットする．
  DxLib::SetWindowIconID(333);

  DxLib::SetUseCharCodeFormat(
      DX_CHARCODEFORMAT_UTF8);             // 文字コードをUTF-8に設定する．
  SetWindowText(GameConst::kWindowTitle);  // ウィンドウタイトルを付ける．
  DxLib::SetAlwaysRunFlag(TRUE);  // ウィンドウがノンアクティブでも実行．
  DxLib::SetOutApplicationLogValidFlag(FALSE);  // ログ出力しない．
  DxLib::SetDoubleStartValidFlag(FALSE);        // 二重起動を許可しない．
  DxLib::SetMainWindowClassName(
      kWindowClassName.c_str());  // ウィンドウのクラス名を設定する．

  // ゲーム画面の解像度を設定する．
  // 色の bit 数。通常32で良いが軽くするなら16にする．
  const int color_bit = 32;
  DxLib::SetGraphMode(GameConst::kResolutionX, GameConst::kResolutionY,
                      color_bit);

  // フルスクリーン設定．
  if (true) {
    // ウィンドウモードで起動する場合．
    DxLib::ChangeWindowMode(TRUE);

    // ウィンドウサイズを自由に変更できるようにする．
    DxLib::SetWindowSizeChangeEnableFlag(FALSE, FALSE);

    // 画面サイズ設定．
    const double ex_rate = 960.0 / static_cast<double>(GameConst::kResolutionX);

    // ウィンドウサイズを変更したい時はここに倍率を指定する．
    DxLib::SetWindowSizeExtendRate(ex_rate);
  }

  // DXライブラリ初期化処理．
  if (DxLib::DxLib_Init() < 0) {
    // 異常終了したら即座にやめる．
    return false;
  }

  DxLib::SetSysCommandOffFlag(TRUE);     // ALTを無効にする．
  DxLib::SetDrawScreen(DX_SCREEN_BACK);  // 裏画面処理を設定する．

  return true;
}

void SystemMain::Finalize() const {
  // DxLibの終了処理を呼ぶ．
  DxLib::DxLib_End();
}

void SystemMain::Main() const {
  GameMainLoop game_main_loop(game_setting_record_ptr_);

  // メインループ．
  while (!DxLib::ProcessMessage()) {
    if (!game_main_loop.Loop()) {
      break;
    }
  }
}

}  // namespace mytetris
