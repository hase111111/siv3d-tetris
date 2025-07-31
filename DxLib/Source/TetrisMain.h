#pragma once
#include <memory>

#include "EnumTetris.h"
#include "Field.h"
#include "Next.h"
#include "TetroMino.h"

class TetrisMain final {
 public:
  TetrisMain();

  void update();
  void draw() const;
  void init(const enumGameMode _mode = enumGameMode::endless);
  void reset();

 private:
  Field m_field;
  TetroMino m_mino;
  Next m_next;

  enumGameMode m_game_mode;  // �Q�[�����[�h�͂ǂꂩ�����lpractice
  int m_game_level;          // �X�s�[�h�̓x����
  unsigned int m_line;       // ���܂ŏ��������C��
  unsigned int m_score;      // �X�R�A

  int m_mino_image_handle;  // �e�g���~�m�̉摜�n���h��
  int m_wall_image_handle;  // �ǂ̉摜�n���h��
  int m_posx, m_posy;       // �t�B�[���h��`�悷����W

  bool m_btob_flag;        // Back To Back�t���O
  bool m_tetris_flag;      // �e�g���X�̃A�j���[�V������\��
  bool m_tspin_flag;       // T-spin�̃A�j���[�V������\��
  enumMino m_hold;         // �z�[���h
  bool m_hold_rock;        // �z�[���h���b�N
  unsigned int m_counter;  // �A�j���[�V�����J�E���^

  bool m_game_start = false;  // �Q�[���J�n�O
  bool m_game_over = false;   // �Q�[���I�[�o�[

  void mf_drawMino(const int _cx, const int _cy, const enumMino _mino) const;
  void mf_drawTetroMino(int _cx, const int _cy, const enumMino _mino) const;
};