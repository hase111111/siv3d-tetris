#pragma once
#include <Windows.h>

#include <string>

#define ERR(str) Error::errorMessage(str, __FILE__, __FUNCTION__, __LINE__)

class Error {
 public:
  static void errorMessage(const std::string _err, const LPCSTR _file,
                           const LPCSTR _func, const int _line);
};