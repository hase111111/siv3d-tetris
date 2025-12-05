#if defined DXLIB_COMPILE
#include "error_box.h"

#include <DxLib.h>

namespace mytetris {

void mytetris::ShowErrorBox(const std::string& message) {
  MessageBox(NULL, TEXT(message.c_str()), TEXT("Error"), MB_ICONERROR);
}

}  // namespace mytetris

#endif  // defined DXLIB_COMPILE
