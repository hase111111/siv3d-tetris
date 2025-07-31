#include "Error.h"

#include <DxLib.h>

void Error::errorMessage(const std::string _err, const LPCSTR _file,
                         const LPCSTR _func, const int _line) {
  clsDx();
  printfDx("�G���[�����I�E�B���h�E�́~�{�^���������ďI�����Ă�������\n\n");
  printfDx("�G���[����\n�E%s\n\n", _err.c_str());
  printfDx("�G���[�����������t�@�C��\n�E%s\n\n", _file);
  printfDx("�G���[�����������֐�\n�E%s(%d�s��)", _func, _line);

  while (!ProcessMessage()) {
    ClearDrawScreen();
    ScreenFlip();
  }
  DxLib_End();
  exit(99);
}