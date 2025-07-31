#include "TitleScene.h"

#include <DxLib.h>

#include "Define.h"
#include "Font.h"
#include "Keyboard.h"

TitleScene::TitleScene(SceneChangeListenerInterface* pScli,
                       const Parameter& parameter)
    : AbstractScene(pScli, parameter) {
  m_image_handle = Image::getIns()->myLoadGraph("dat/img/title.png");
  m_image_handle2 = Image::getIns()->myLoadGraph("dat/img/wall.png");
  m_image_handle3 = Image::getIns()->myLoadGraph("dat/img/pointer.png");
}

void TitleScene::update() {
  m_anime_counter++;

  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
    m_mode_counter++;
  } else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
    m_mode_counter += 3;
  }

  if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) > 0) {
    Parameter _param;
    _param.setParam("mode", m_mode_counter % 4);
    mp_listenerInterface->addNewScene(enumScene::game, _param);
  }
}

void TitleScene::draw() const {
  DrawRotaGraph(Define::WIN_SIZEX / 2, Define::WIN_SIZEY / 2 - 120, 1.0, 0.0,
                m_image_handle, true);

  for (int i = 0; i < 24; i++) {
    DrawRotaGraph(12, 24 * i - 12, 1.2, 0.0, m_image_handle2, true);
    DrawRotaGraph(Define::WIN_SIZEX - 12, 24 * i - 12, 1.2, 0.0,
                  m_image_handle2, true);
  }

  int _len = 0;
  _len = GetDrawNStringWidthToHandle("ENDLESS Mode", strlen("ENDLESS Mode"),
                                     Font::getIns()->getFontHandle()) /
         2;
  DrawStringToHandle(Define::WIN_SIZEX / 2 - _len, Define::WIN_SIZEY / 2 + 30,
                     "ENDLESS Mode", GetColor(255, 255, 255),
                     Font::getIns()->getFontHandle());
  if (m_mode_counter % 4 == 0)
    DrawRotaGraph(Define::WIN_SIZEX / 2 - _len - 20,
                  Define::WIN_SIZEY / 2 + 30 + 11,
                  1.0 + 0.15 * sin(m_anime_counter * 3.14 / 30), 0.0,
                  m_image_handle3, true);

  _len = GetDrawNStringWidthToHandle("Sprint Mode", strlen("Sprint Mode"),
                                     Font::getIns()->getFontHandle()) /
         2;
  DrawStringToHandle(Define::WIN_SIZEX / 2 - _len, Define::WIN_SIZEY / 2 + 80,
                     "Sprint Mode", GetColor(255, 255, 255),
                     Font::getIns()->getFontHandle());
  if (m_mode_counter % 4 == 1)
    DrawRotaGraph(Define::WIN_SIZEX / 2 - _len - 20,
                  Define::WIN_SIZEY / 2 + 80 + 11,
                  1.0 + 0.15 * sin(m_anime_counter * 3.14 / 30), 0.0,
                  m_image_handle3, true);

  _len = GetDrawNStringWidthToHandle("Ultra Mode", strlen("Ultra Mode"),
                                     Font::getIns()->getFontHandle()) /
         2;
  DrawStringToHandle(Define::WIN_SIZEX / 2 - _len, Define::WIN_SIZEY / 2 + 130,
                     "Ultra Mode", GetColor(255, 255, 255),
                     Font::getIns()->getFontHandle());
  if (m_mode_counter % 4 == 2)
    DrawRotaGraph(Define::WIN_SIZEX / 2 - _len - 20,
                  Define::WIN_SIZEY / 2 + 130 + 11,
                  1.0 + 0.15 * sin(m_anime_counter * 3.14 / 30), 0.0,
                  m_image_handle3, true);

  _len = GetDrawNStringWidthToHandle("Marathon Mode", strlen("Marathon Mode"),
                                     Font::getIns()->getFontHandle()) /
         2;
  DrawStringToHandle(Define::WIN_SIZEX / 2 - _len, Define::WIN_SIZEY / 2 + 180,
                     "Marathon Mode", GetColor(255, 255, 255),
                     Font::getIns()->getFontHandle());
  if (m_mode_counter % 4 == 3)
    DrawRotaGraph(Define::WIN_SIZEX / 2 - _len - 20,
                  Define::WIN_SIZEY / 2 + 180 + 11,
                  1.2 + 0.15 * sin(m_anime_counter * 3.14 / 30), 0.0,
                  m_image_handle3, true);
}

void TitleScene::receiveParameterInCaseOfDeleteScene(
    const Parameter& parameter) {}
