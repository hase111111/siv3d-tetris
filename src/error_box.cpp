//! @file error_box.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#if defined DXLIB_COMPILE
#include "error_box.h"

#include <DxLib.h>

namespace mytetris {

void mytetris::ShowErrorBox(const std::string& message) {
  MessageBox(NULL, TEXT(message.c_str()), TEXT("Error"), MB_ICONERROR);
}

}  // namespace mytetris

#endif  // defined DXLIB_COMPILE
