
#include <DxLib.h>

#include "system_main.h"

#pragma warning(disable : 28251)

// �v���O������ WinMain ����n�܂�܂�
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
        TEXT("�֐�:DxLibInit���G���[���N����������\n�ً}�I�����܂����B\nP.S "
             "���̃A�v���͓�d�N���ł��܂���"),
        TEXT("��"), MB_ICONERROR);
  }

  return 0;
}