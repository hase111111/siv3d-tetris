#pragma once
#include <memory>

#include "AbstractScene.h"
#include "TetrisMain.h"

class GameScene : public AbstractScene {
 public:
  GameScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

  void update() override;
  void draw() const override;
  void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

 private:
  TetrisMain m_tetris;
  bool you_end_init = false;
};
