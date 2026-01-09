#pragma once

#if defined DXLIB_COMPILE

#include <string>

namespace mytetris {

//! @brief DXライブラリを使用してエラーメッセージボックスを表示する.
//! @param message 表示するエラーメッセージ.
void ShowErrorBox(const std::string& message);

}  // namespace mytetris

#endif  // defined DXLIB_COMPILE
