
#include <DxLib.h>

#include "system_main.h"

#pragma warning(disable : 28251)

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  using mytetris::SystemMain;
  SystemMain system_main;

  if (system_main.initialize()) {
    system_main.main();
    system_main.finalize();
  } else {
    MessageBox(
        NULL,
        TEXT("関数:DxLibInitがエラーを起こしたため\n緊急終了しました。\nP.S "
             "このアプリは二重起動できません"),
        TEXT("報告"), MB_ICONERROR);
  }

  return 0;
}