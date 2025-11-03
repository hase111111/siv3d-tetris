//! @file log_print.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#if defined(DXLIB_COMPILE)
#include <Dxlib.h>
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include "log_print.h"

namespace mytetris {

void LogPrintInternal::PrintString([[maybe_unused]] const std::string str) {
#if defined(DXLIB_COMPILE)
  setPrintColorDx(GetColor(255, 0, 0), GetColor(0, 255, 0));
  printfDx("%s", str.c_str());
#elif defined(SIV3D_COMPILE)
  s3d::String s3d_str = s3d::String{str.begin(), str.end()};
  s3d::Print << s3d_str;
#endif  //! defined(DXLIB_COMPILE)
}

}  // namespace mytetris
