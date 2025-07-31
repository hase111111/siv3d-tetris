#include "DxLib.h"
#include "SystemMain.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  SystemMain _sys;

  if (_sys.initialize()) {
    _sys.main();
  } else {
    MessageBox(
        NULL,
        TEXT("�֐�:DxLibInit���G���[���N����������\n�ً}�I�����܂����B\nP.S "
             "���̃A�v���͓�d�N���ł��܂���"),
        TEXT("��"), MB_ICONERROR);
  }

  _sys.finalize();

  return 0;
}