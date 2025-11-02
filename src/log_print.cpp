#if defined(DXLIB_COMPILE)
#include <Dxlib.h>
#elif defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)
#include <Siv3D.hpp>
#endif  // defined(SIV3D_COMPILE) || defined(__EMSCRIPTEN__)

#include "log_print.h"

namespace mytetris {

void LogPrintInternal::PrintString(const std::string str) {
#if defined(DXLIB_COMPILE)
  setPrintColorDx(GetColor(255, 0, 0), GetColor(0, 255, 0));
  printfDx("%s", str.c_str());
#else
  s3d::String s3d_str = s3d::String{str.begin(), str.end()};
  s3d::Print << s3d_str;
#endif  //! defined(DXLIB_COMPILE)
}

}  // namespace mytetris
