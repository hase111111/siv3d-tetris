
//! @file error_box.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "error_box.h"

#if defined DXLIB_COMPILE
#include <DxLib.h>
#endif  // defined DXLIB_COMPILE

namespace mytetris {

void mytetris::ShowErrorBox(const std::string& message) {
#if defined DXLIB_COMPILE
  MessageBox(NULL, TEXT(message.c_str()), TEXT("Error"), MB_ICONERROR);
#endif  // defined DXLIB_COMPILE
}

}  // namespace mytetris
