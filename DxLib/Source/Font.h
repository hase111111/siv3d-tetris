#pragma once
#include <string>

#include "Singleton.h"

class Font : public Singleton<Font> {
 private:
  friend Singleton<Font>;

 public:
  bool LoadFont();

  int getFontHandle();

  void releaseFont();

 private:
  // フォントデータが置いてあるパス
  const std::string FONT_PATH = "dat/font/dot_font.dft";

  // フォントのハンドル
  int font_handle = 0;
};
