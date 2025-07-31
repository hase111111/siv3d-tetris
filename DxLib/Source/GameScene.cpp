#include "GameScene.h"

#include "DxLib.h"
#include "Keyboard.h"
#include "dxlib_assert.h"

GameScene::GameScene(SceneChangeListenerInterface* pScli,
                     const Parameter& parameter)
    : AbstractScene(pScli, parameter) {
  if (parameter.getParam("mode") == Parameter::Error) {
    ASSERT_MUST_NOT_REACH_HERE();
  } else if (parameter.getParam("mode") == 0) {
    m_tetris.init(enumGameMode::endless);
  } else if (parameter.getParam("mode") == 1) {
    m_tetris.init(enumGameMode::sprint);
  } else if (parameter.getParam("mode") == 2) {
    m_tetris.init(enumGameMode::ultra);
  } else if (parameter.getParam("mode") == 3) {
    m_tetris.init(enumGameMode::marathon);
  }
}

void GameScene::update() {
  if (you_end_init == false) {
    // m_tetris.init();
    you_end_init = true;
  } else {
    m_tetris.update();
  }
}

void GameScene::draw() const {
  m_tetris.draw();

  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) > 0) {
    Parameter _param;
    mp_listenerInterface->deleteNowScene(_param);
  }
}

void GameScene::receiveParameterInCaseOfDeleteScene(
    const Parameter& parameter) {}
