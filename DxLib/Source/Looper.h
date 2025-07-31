#pragma once
#include <memory>

#include "Fps.h"
#include "SceneManager.h"

class Looper {
 public:
  Looper() = default;
  ~Looper() = default;

  bool loop();

 private:
  SceneManger m_sceneMgr;
  Fps _fps;
};