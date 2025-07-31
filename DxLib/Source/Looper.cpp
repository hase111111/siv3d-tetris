#include "Looper.h"

#include "Keyboard.h"

bool Looper::loop() {
  Keyboard::getIns()->update();
  m_sceneMgr.updateTopScene();
  m_sceneMgr.drawTopScene();
  //_fps.draw();
  _fps.wait();

  return true;
}
