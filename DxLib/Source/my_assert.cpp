
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
  // ファイルパスからファイル名を取得する．
  auto pos = file_path.find_last_of("/\\");
  if (pos != std::string::npos) {
    return file_path.substr(pos + 1);
  }
  return file_path;  // パス区切り文字が見つからない場合はそのまま返す．
}

static std::string GetFuncName(const std::string& func_name) {
  // ( を見つけて，そこから遡り " " までの文字列を取得する．
  // なければそのまま返す．
  auto pos = func_name.find('(');
  if (pos != std::string::npos) {
    auto start_pos = func_name.rfind(' ', pos);
    if (start_pos != std::string::npos) {
      return func_name.substr(start_pos + 1, pos - start_pos - 1);
    }
  }
  return func_name;  // ( が見つからない場合はそのまま返す．
}

static std::string EraseNameSpaceName(const std::string& func_name) {
  // mytetris:: の名前空間名をすべて削除する．
  std::string result = func_name;
  const std::string namespace_name = "mytetris::";
  size_t pos = 0;
  while ((pos = result.find(namespace_name, pos)) != std::string::npos) {
    result.erase(pos, namespace_name.length());
  }
  return result;
}

static std::string ErasePrefix(const std::string& func_name) {
  // 関数名の先頭にある "class" や "struct" を "すべて" 削除する．
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
  // 関数名の末尾にある Calling Convention を削除する．
  // 例: __cdecl, __stdcall, __fastcall, __thiscall
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
  // テンプレートの部分を<~>にまとめる．
  // 複数回出現する場合は，一番外側に対応するものをまとめる．
  // 例: std::vector<int, std::allocator<int>> -> std::vector<~>
  std::string result = func_name;
  size_t start_pos = result.find('<');
  int count = 0;  // ネストの深さをカウントする

  if (start_pos == std::string::npos) {
    return result;  // < が見つからない場合はそのまま返す．
  }

  for (size_t i = start_pos; i < result.length(); ++i) {
    if (result[i] == '<') {
      count++;
    } else if (result[i] == '>') {
      count--;
      if (count == 0) {
        // 最初の対応する '>' を見つけたら，その部分を <~> に置き換える．
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
  // DxLib がまだ初期化されていない場合は，終了する．
  if (DxLib::DxLib_IsInit() != TRUE) {
    return;
  }

  // エラーメッセージを表示する．
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

  // 何もせずに待つ．
  while (!DxLib::ProcessMessage()) {
    DxLib::ClearDrawScreen();
    DxLib::ScreenFlip();
  }

  DxLib::DxLib_End();

  // プログラムを終了する．
  exit(99);
}

}  // namespace mytetris::assert_internal
