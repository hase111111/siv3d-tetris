#pragma once

class TetrisDefine{
public:
	static const int MINO_SIZE;
	static const unsigned int MINO_FALL_COUNT[10];
	static const unsigned int MINO_ROCK_COUNT;
	static const int MINO_HORIZONTAL_INTERVAL;
	static const int MINO_HORIZONTAL_COUNT;

	static const int TETRIS_SINGLE_SCORE;
	static const int TETRIS_DOUBLE_SCORE;
	static const int TETRIS_TRIPLE_SCORE;
	static const int TETRIS_TETRIS_SCORE;
	static const int TETRIS_TSPIN_SINGLE_SCORE;
	static const int TETRIS_TSPIN_DOUBLE_SCORE;
	static const int TETRIS_TSPIN_TRIPLE_SCORE;
private:
	//インスタンスを生成させない
	TetrisDefine() = default;

public:
	//以下変更不可の定数
	enum{
		FIELD_X = 12,
		FIELD_Y = 24
	};

	static const int GAMR_OVER_Y = 21;
	static const int MINO_IMAGE_SIZE = 20;
};
