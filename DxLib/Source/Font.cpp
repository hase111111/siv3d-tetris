#include "Font.h"

#include <DxLib.h>

bool Font::LoadFont() {
  font_handle = LoadFontDataToHandle(FONT_PATH.c_str(), 0);

  // 読み込みに失敗していたなら-1が返る
  if (font_handle == -1) {
    return false;
  }
  return true;
}

int Font::getFontHandle() { return font_handle; }

void Font::releaseFont() {
  if (font_handle == 0 || font_handle == 1) {
    return;
  }

  DeleteFontToHandle(font_handle);
}