//! @file error_box.h
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#if defined DXLIB_COMPILE

#include <string>

namespace mytetris {

//! @brief DXライブラリを使用してエラーメッセージボックスを表示する.
//! @param message 表示するエラーメッセージ.
void ShowErrorBox(const std::string& message);

}  // namespace mytetris

#endif  // defined DXLIB_COMPILE
