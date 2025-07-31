
//! @file main.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

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
        "DxLibÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩÅDã≠êßèIóπÇµÇ‹Ç∑ÅD\n\n"
        "Initialization of DxLib failed. Force quit.");
  }

  return 0;
}
