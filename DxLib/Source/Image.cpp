#include "Image.h"

#include "DxLib.h"

void Image::release() {}

int Image::myLoadGraph(std::string str) {
  // 既に読み込み済みならば
  if (m_images.count(str) != 0) {
    return m_images.at(str);
  }

  // そうでなければ画像を読み込む
  const int temp_gr_handle = LoadGraph(str.c_str());

  if (temp_gr_handle == -1) {
    return -1;
  }

  // 記録
  m_images[str] = temp_gr_handle;
  return temp_gr_handle;
}