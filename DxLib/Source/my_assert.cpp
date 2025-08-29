
//! @file my_assert.cpp
//! @brief
//! Copyright(c) 2024-2025 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#include "my_assert.h"

#include <DxLib.h>

#include <format>
#include <string>
#include <vector>

namespace mytetris::assert_internal {

static std::string GetFileName(const std::string& file_path) {
  // �t�@�C���p�X����t�@�C�������擾����D
  auto pos = file_path.find_last_of("/\\");
  if (pos != std::string::npos) {
    return file_path.substr(pos + 1);
  }
  return file_path;  // �p�X��؂蕶����������Ȃ��ꍇ�͂��̂܂ܕԂ��D
}

static std::string GetFuncName(const std::string& func_name) {
  // ( �������āC��������k�� " " �܂ł̕�������擾����D
  // �Ȃ���΂��̂܂ܕԂ��D
  auto pos = func_name.find('(');
  if (pos != std::string::npos) {
    auto start_pos = func_name.rfind(' ', pos);
    if (start_pos != std::string::npos) {
      return func_name.substr(start_pos + 1, pos - start_pos - 1);
    }
  }
  return func_name;  // ( ��������Ȃ��ꍇ�͂��̂܂ܕԂ��D
}

static std::string EraseNameSpaceName(const std::string& func_name) {
  // mytetris:: �̖��O��Ԗ������ׂč폜����D
  std::string result = func_name;
  const std::string namespace_name = "mytetris::";
  size_t pos = 0;
  while ((pos = result.find(namespace_name, pos)) != std::string::npos) {
    result.erase(pos, namespace_name.length());
  }
  return result;
}

static std::string ErasePrefix(const std::string& func_name) {
  // �֐����̐擪�ɂ��� "class" �� "struct" �� "���ׂ�" �폜����D
  std::string result = func_name;
  const std::vector<std::string> prefix_name = {"class ", "struct "};
  for (const auto& prefix : prefix_name) {
    size_t pos = 0;
    while ((pos = result.find(prefix, pos)) != std::string::npos) {
      result.erase(pos, prefix.length());
    }
  }
  return result;
}

static std::string EraseCallingConvention(const std::string& func_name) {
  // �֐����̖����ɂ��� Calling Convention ���폜����D
  // ��: __cdecl, __stdcall, __fastcall, __thiscall
  std::string result = func_name;
  const std::vector<std::string> calling_conventions = {
      "__cdecl", "__stdcall", "__fastcall", "__thiscall"};
  for (const auto& conv : calling_conventions) {
    size_t pos = 0;
    while ((pos = result.find(conv, pos)) != std::string::npos) {
      result.erase(pos, conv.length());
    }
  }
  return result;
}

static std::string CollapseTemplate(const std::string& func_name) {
  // �e���v���[�g�̕�����<~>�ɂ܂Ƃ߂�D
  // ������o������ꍇ�́C��ԊO���ɑΉ�������̂��܂Ƃ߂�D
  // ��: std::vector<int, std::allocator<int>> -> std::vector<~>
  std::string result = func_name;
  size_t start_pos = result.find('<');
  int count = 0;  // �l�X�g�̐[�����J�E���g����

  if (start_pos == std::string::npos) {
    return result;  // < ��������Ȃ��ꍇ�͂��̂܂ܕԂ��D
  }

  for (size_t i = start_pos; i < result.length(); ++i) {
    if (result[i] == '<') {
      count++;
    } else if (result[i] == '>') {
      count--;
      if (count == 0) {
        // �ŏ��̑Ή����� '>' ����������C���̕����� <~> �ɒu��������D
        result.replace(start_pos, i - start_pos + 1, "<~>");
        break;
      }
    }
  }

  return result;
}

bool IsDxLibInitialized() { return DxLib_IsInit() == TRUE; }

void ErrorAssert(const std::string& conditional_expression,
                 const std::string& error_mes, const std::string& file,
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
  DxLib::printfDx("%s",
                  std::format("File Name : {}\n\n", GetFileName(file)).c_str());

  const std::string func_name_detail = CollapseTemplate(
      EraseCallingConvention(ErasePrefix(EraseNameSpaceName(func))));
  const std::string func_name = GetFuncName(func_name_detail);
  DxLib::printfDx("%s",
                  std::format("Function Name : {}\n\n", func_name).c_str());
  DxLib::printfDx(
      "%s",
      std::format("Function Name Detail : \n{}\n\n", func_name_detail).c_str());
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

}  // namespace mytetris::assert_internal
