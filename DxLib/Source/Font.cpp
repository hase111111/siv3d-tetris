#include "Font.h"

#include <DxLib.h>

bool Font::LoadFont() {
  font_handle = LoadFontDataToHandle(FONT_PATH.c_str(), 0);

  // �ǂݍ��݂Ɏ��s���Ă����Ȃ�-1���Ԃ�
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