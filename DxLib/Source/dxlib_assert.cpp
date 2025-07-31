
//! @file dxlib_assert.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "dxlib_assert.h"

#include <DxLib.h>

#include <format>

namespace mytetris {

void assert_internal::ErrorAssert(const std::string& conditional_expression,
                                  const std::string& error_mes,
                                  const std::string& file,
                                  const std::string& func, const int line) {
  // DxLib ���܂�����������Ă��Ȃ��ꍇ�́C�I������D
  if (DxLib::DxLib_IsInit() != TRUE) {
    return;
  }

  // �G���[���b�Z�[�W��\������D
  DxLib::clsDx();
  DxLib::printfDx(
      "Error! Please press the X button on the window to exit! \n\n");
  DxLib::printfDx(
      "%s",
      std::format("Error Condition : {}\n\n", conditional_expression).c_str());
  DxLib::printfDx("%s", std::format("Error Cause : {}\n\n", error_mes).c_str());
  DxLib::printfDx("%s", std::format("File Name : {}\n\n", file).c_str());
  DxLib::printfDx("%s", std::format("Function Name : {}\n\n", func).c_str());
  DxLib::printfDx("%s", std::format("Line Number : {}\n\n", line).c_str());

  // ���������ɑ҂D
  while (!DxLib::ProcessMessage()) {
    DxLib::ClearDrawScreen();
    DxLib::ScreenFlip();
  }

  DxLib::DxLib_End();

  // �v���O�������I������D
  exit(99);
}

}  // namespace mytetris
