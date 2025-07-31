#pragma once
#include <map>
#include <string>

#include "Singleton.h"

class Image final : public Singleton<Image> {
 public:
  Image(){};
  ~Image() = default;

  void release();
  int myLoadGraph(std::string str);

 private:
  std::map<std::string, int> m_images;
};