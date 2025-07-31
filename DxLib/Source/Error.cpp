#include "Error.h"

#include <DxLib.h>

void Error::errorMessage(const std::string _err, const LPCSTR _file,
                         const LPCSTR _func, const int _line) {
  clsDx();
  printfDx("エラー発生！ウィンドウの×ボタンを押して終了してください\n\n");
  printfDx("エラー原因\n・%s\n\n", _err.c_str());
  printfDx("エラーが発生したファイル\n・%s\n\n", _file);
  printfDx("エラーが発生した関数\n・%s(%d行目)", _func, _line);

  while (!ProcessMessage()) {
    ClearDrawScreen();
    ScreenFlip();
  }
  DxLib_End();
  exit(99);
}