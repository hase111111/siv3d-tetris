#include "DxLib.h"
#include "SystemMain.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  SystemMain _sys;

  if (_sys.initialize()) {
    _sys.main();
  } else {
    MessageBox(
        NULL,
        TEXT("関数:DxLibInitがエラーを起こしたため\n緊急終了しました。\nP.S "
             "このアプリは二重起動できません"),
        TEXT("報告"), MB_ICONERROR);
  }

  _sys.finalize();

  return 0;
}