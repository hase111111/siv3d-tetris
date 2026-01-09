
//! @file main.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#if defined DXLIB_COMPILE
#include <DxLib.h>

#include "error_box.h"
#include "system_main.h"

#pragma warning(disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  using mytetris::ShowErrorBox;
  using mytetris::SystemMain;

  SystemMain system_main;

  if (system_main.Initialize()) {
    system_main.Main();
    system_main.Finalize();
  } else {
    ShowErrorBox(
        "DxLibの初期化に失敗しました．強制終了します．\n\n"
        "Initialization of DxLib failed. Force quit.");
  }

  return 0;
}

#elif defined SIV3D_COMPILE || defined(__EMSCRIPTEN__)

#include <Siv3D.hpp>

#include "system_main.h"

#if defined(__EMSCRIPTEN__)
#include "siv3d_touch.h"

EM_JS(void, setupMultiTouchHandler, (), {
  // グローバル変数を定義
  window.myTouches = [];

  // タッチイベントの処理を設定
  const canvas = Module['canvas'];

  function updateTouches(e) {
    window.myTouches = Array.from(e.touches);
    // e.preventDefault(); // 任意：スクロール防止など
  }

  canvas.addEventListener("touchstart", updateTouches, false);
  canvas.addEventListener("touchmove", updateTouches, false);
  canvas.addEventListener("touchend", updateTouches, false);
});

#endif  // defined(__EMSCRIPTEN__)

void Main() {
  using mytetris::SystemMain;

#if defined(__EMSCRIPTEN__)
  // JavaScriptのタッチイベントハンドラをセットアップ
  setupMultiTouchHandler();
#endif  // defined(__EMSCRIPTEN__)

  SystemMain system_main;

  if (system_main.Initialize()) {
    system_main.Main();
    system_main.Finalize();
  } else {
  }
}

#endif
