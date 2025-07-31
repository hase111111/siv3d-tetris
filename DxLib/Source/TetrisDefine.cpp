#include "TetrisDefine.h"

const          int TetrisDefine::MINO_SIZE = 22;
const unsigned int TetrisDefine::MINO_ROCK_COUNT = 30;
const          int TetrisDefine::MINO_HORIZONTAL_INTERVAL = 6;
const          int TetrisDefine::MINO_HORIZONTAL_COUNT = 5;
const unsigned int TetrisDefine::MINO_FALL_COUNT[10] = { 60,50,40,30,20, 15,10,5,2,0 };

const int TetrisDefine::TETRIS_SINGLE_SCORE = 1000 * 1;
const int TetrisDefine::TETRIS_DOUBLE_SCORE = 1000 * 2;
const int TetrisDefine::TETRIS_TRIPLE_SCORE = 1000 * 3;
const int TetrisDefine::TETRIS_TETRIS_SCORE = 1000 * 5;
const int TetrisDefine::TETRIS_TSPIN_SINGLE_SCORE = 1000 * 3;
const int TetrisDefine::TETRIS_TSPIN_DOUBLE_SCORE = 1000 * 5;
const int TetrisDefine::TETRIS_TSPIN_TRIPLE_SCORE = 1000 * 7;