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

  enumGameMode m_game_mode;  // ゲームモードはどれか初期値practice
  int m_game_level;          // スピードの度合い
  unsigned int m_line;       // 今まで消したライン
  unsigned int m_score;      // スコア

  int m_mino_image_handle;  // テトリミノの画像ハンドル
  int m_wall_image_handle;  // 壁の画像ハンドル
  int m_posx, m_posy;       // フィールドを描画する座標

  bool m_btob_flag;        // Back To Backフラグ
  bool m_tetris_flag;      // テトリスのアニメーションを表示
  bool m_tspin_flag;       // T-spinのアニメーションを表示
  enumMino m_hold;         // ホールド
  bool m_hold_rock;        // ホールドロック
  unsigned int m_counter;  // アニメーションカウンタ

  bool m_game_start = false;  // ゲーム開始前
  bool m_game_over = false;   // ゲームオーバー

  void mf_drawMino(const int _cx, const int _cy, const enumMino _mino) const;
  void mf_drawTetroMino(int _cx, const int _cy, const enumMino _mino) const;
};