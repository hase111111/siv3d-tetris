#include"TetrisMain.h"
#include"DxLib.h"
#include"Field.h"
#include"Image.h"
#include"Keyboard.h"
#include"Font.h"

TetrisMain::TetrisMain() :
	m_game_mode(enumGameMode::endless),
	m_mino_image_handle(Image::getIns()->myLoadGraph("dat/img/blocks.png")),
	m_wall_image_handle(Image::getIns()->myLoadGraph("dat/img/wall.png")),
	m_posx(Define::WIN_SIZEX / 2 - TetrisDefine::MINO_SIZE * (TetrisDefine::FIELD_X / 2 + 1)),
	m_posy(TetrisDefine::MINO_SIZE * 3 / 2 + 1),
	m_hold(enumMino::none),m_hold_rock(true),
	m_game_level(0),m_line(0),m_score(0),
	m_btob_flag(false),
	m_tspin_flag(false),
	m_counter(0), m_tetris_flag(false)
{
	m_mino.reset(m_next.getTopMino());
}

void TetrisMain::update()
{
	//ゲーム開始前
	if (m_game_start == false) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) == 1) {
			m_game_start = true;
		}
		return;
	}

	//リセット処理
	if (m_game_start == true && Keyboard::getIns()->getPressingCount(KEY_INPUT_R) == 1) {
		reset();
		return;
	}

	//ゲームオーバー
	if (m_game_over) {
		return;
	}

	//クリア処理
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::sprint && m_line >= 40 && m_field.anime() == false) {
		m_mino.reset(enumMino::O);
		return;
	}
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::ultra && m_counter >= 10800 && m_field.anime() == false) {
		m_mino.reset(enumMino::O);
		return;
	}
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::marathon && m_line >= 150 && m_field.anime() == false) {
		m_mino.reset(enumMino::O);
		return;
	}

	//ゲームカウンタを回す
	m_counter += 1;

	//フィールドデータを取得
	enumMino _field[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y];
	m_field.getField(_field);
	m_mino.setFieldDate(_field);

	//アニメ中ならここで中断
	if (m_field.anime()) { return; }

	//ホールド切り替え
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_W) == 1 && m_hold_rock) {
		enumMino _temp = m_mino.getMinoType();
		if (m_hold == enumMino::none) { m_hold = m_next.getTopMino(); }
		m_mino.reset(m_hold);
		m_hold = _temp;
		m_hold_rock = false;
	}

	//動かすまたは回す
	m_mino.update(m_line / 20);
	m_game_level = m_line / 20 + 1;
	if (m_game_level > 10)m_game_level = 10;

	//固定フラグが立ったならば
	if (m_mino.getFlagRockMino()) {
		int _mino[4][2];
		m_mino.getMinoPos(_mino);

		//この関数がfalseを返したならゲームオーバー
		m_game_over = !m_field.setMino(m_mino.getMinoType(), _mino);

		//ライン消去
		enumDeleteLine _line = m_field.deleteLine();
		if (_line != enumDeleteLine::zero && m_btob_flag == true) { m_score += TetrisDefine::TETRIS_SINGLE_SCORE; }
		m_tetris_flag = false;
		m_tspin_flag = false;

		if (_line == enumDeleteLine::oneline) {
			m_line += 1;
			if (m_field.getTspinFlag() == true) { m_score += TetrisDefine::TETRIS_TSPIN_SINGLE_SCORE; m_btob_flag = true; m_tspin_flag = true;}
			else { m_score += TetrisDefine::TETRIS_SINGLE_SCORE; m_btob_flag = false;}
		}
		else if (_line == enumDeleteLine::twoline) {
			m_line += 2;
			if (m_field.getTspinFlag() == true) { m_score += TetrisDefine::TETRIS_TSPIN_DOUBLE_SCORE; m_btob_flag = true; m_tspin_flag = true;}
			else { m_score += TetrisDefine::TETRIS_DOUBLE_SCORE; m_btob_flag = false;}
		}
		else  if (_line == enumDeleteLine::threeline) {
			m_line += 3;
			if (m_field.getTspinFlag() == true) { m_score += TetrisDefine::TETRIS_TSPIN_TRIPLE_SCORE; m_btob_flag = true; m_tspin_flag = true; }
			else { m_score += TetrisDefine::TETRIS_TRIPLE_SCORE; m_btob_flag = false;}
		}
		else if (_line == enumDeleteLine::tetris) {
			m_line += 4; 
			m_score += TetrisDefine::TETRIS_TETRIS_SCORE;
			m_btob_flag = true;
			m_tetris_flag = true;
		}

		m_mino.reset(m_next.getTopMino());
		m_hold_rock = true;
	}
}

void TetrisMain::draw() const
{
	//フィールドデータを取得
	enumMino _field[TetrisDefine::FIELD_X][TetrisDefine::FIELD_Y];
	m_field.getField(_field);

	//テトリミノを取得
	enumMino _minotype = m_mino.getMinoType();
	int _mino[4][2];
	m_mino.getMinoPos(_mino);
	int _mino_ghost[4][2];
	m_mino.getMinoPos(_mino_ghost, true);

	//フィールドを描画
	int _cx, _cy;
	for (int y = 2; y < TetrisDefine::FIELD_Y; y++) {
		for (int x = -7; x < TetrisDefine::FIELD_X + 10; x++) {
			_cx = x * TetrisDefine::MINO_SIZE;
			_cy = y * TetrisDefine::MINO_SIZE;
			if (x == -7 || x == TetrisDefine::FIELD_X + 4 || x == TetrisDefine::FIELD_X + 9 || y == 2 || y == TetrisDefine::FIELD_Y - 1 || (y == 8 && x > TetrisDefine::FIELD_X + 4)) {
				mf_drawMino(_cx + m_posx, _cy - m_posy, enumMino::wall);
			}
			else {
				mf_drawMino(_cx + m_posx, _cy - m_posy, enumMino::none);
			}
		}
	}

	for (int y = 3; y < TetrisDefine::FIELD_Y; y++) {
		for (int x = 0; x < TetrisDefine::FIELD_X; x++) {
			_cx = x * TetrisDefine::MINO_SIZE;
			_cy = y * TetrisDefine::MINO_SIZE;
			mf_drawMino(_cx + m_posx, _cy - m_posy, _field[x][y]);
		}
	}

	//テトリミノを描画
	for (int i = 0; i < 4; i++) {
		_cx = _mino[i][0] * TetrisDefine::MINO_SIZE;
		_cy = _mino[i][1] * TetrisDefine::MINO_SIZE;
		if (_mino[i][1] != 0 && _mino[i][1] != 1 && _mino[i][1] != 2)mf_drawMino(_cx + m_posx, _cy - m_posy, _minotype);

		if (m_game_start == true) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			_cx = _mino_ghost[i][0] * TetrisDefine::MINO_SIZE;
			_cy = _mino_ghost[i][1] * TetrisDefine::MINO_SIZE;
			mf_drawMino(_cx + m_posx, _cy - m_posy, _minotype);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	//ネクスト
	enumMino _next[6];
	m_next.getDrawMino(_next);
	for (int i = 0; i < 6; i++)
	{
		mf_drawTetroMino(TetrisDefine::FIELD_X * TetrisDefine::MINO_SIZE + m_posx, (2 + i * 3) * TetrisDefine::MINO_SIZE + m_posy, _next[i]);
	}
	DrawFormatStringToHandle(TetrisDefine::FIELD_X * TetrisDefine::MINO_SIZE + m_posx,  m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "NEXT");

	//ホールド
	DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "HOLD");
	if(!m_hold_rock){ SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); }
	mf_drawTetroMino((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 2 * TetrisDefine::MINO_SIZE + m_posy, m_hold);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//スコア
	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 0 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "GAMEMODE");
	if (m_game_mode == enumGameMode::endless) { DrawFormatStringToHandle(-11 * TetrisDefine::MINO_SIZE / 2 + m_posx, 1 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "ENDLESS"); }
	else if (m_game_mode == enumGameMode::sprint) { DrawFormatStringToHandle(-5 * TetrisDefine::MINO_SIZE + m_posx, 1 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "SPRINT"); }
	else if (m_game_mode == enumGameMode::ultra) { DrawFormatStringToHandle(-5 * TetrisDefine::MINO_SIZE + m_posx, 1 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "ULTRA"); }
	else if (m_game_mode == enumGameMode::marathon) { DrawFormatStringToHandle(-5 * TetrisDefine::MINO_SIZE + m_posx - 10, 1 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "MARATHON"); }

	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 3 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "SCORE");
	DrawFormatStringToHandle(-5 * TetrisDefine::MINO_SIZE + m_posx, 4 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "%07d", m_score);

	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 6 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "TIME", m_counter);
	DrawFormatStringToHandle(-5 * TetrisDefine::MINO_SIZE + m_posx, 7 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "%d:%02d:%02d", m_counter/3600%3600, m_counter/60%60 , (m_counter%60)*100/60);

	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 9 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "LINE:%d",m_line);

	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 11 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "LEVEL:%2d", m_game_level);

	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 15 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "GAME END", m_game_level);
	DrawFormatStringToHandle(-4 * TetrisDefine::MINO_SIZE + m_posx, 16 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "C-KEY", m_game_level);

	if (m_game_start == false) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); }
	DrawFormatStringToHandle(-6 * TetrisDefine::MINO_SIZE + m_posx, 17 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "RESET", m_game_level);
	DrawFormatStringToHandle(-4 * TetrisDefine::MINO_SIZE + m_posx, 18 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "R-KEY", m_game_level);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_btob_flag && m_counter % 10 > 5) {
		DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 6 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "Back");
		DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 7 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "to");
		DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 8 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "Back");
	}
	if (m_tspin_flag && m_counter % 10 > 5) {
		DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 12 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "T-Spin");
	}
	if (m_tetris_flag && m_counter % 10 > 5) {
		DrawFormatStringToHandle((TetrisDefine::FIELD_X + 5) * TetrisDefine::MINO_SIZE + m_posx, 10 * TetrisDefine::MINO_SIZE + m_posy, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "Tetris");
	}

	//その他システムメッセ
	if (m_game_start == false) {
		DrawFormatStringToHandle(m_posx + 30, 240, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "PUSH A TO START");
	}
	//ゲームオーバー処理
	if (m_game_over == true) {
		DrawFormatStringToHandle(m_posx + 60, m_posy + 30, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "GAME OVER!");
		DrawFormatStringToHandle(m_posx + 50, m_posy + 60, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "PUSH C OR R");
	}
	//クリア処理
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::sprint && m_line >= 40) {
		DrawFormatStringToHandle(m_posx + 30, m_posy + 30, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "FINISH!");
		DrawFormatStringToHandle(m_posx + 30, m_posy + 60, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "YOUR SCORE");
		DrawFormatStringToHandle(m_posx + 50, m_posy + 90, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "%d:%02d:%02d", m_counter / 3600 % 3600, m_counter / 60 % 60, (m_counter % 60) * 100 / 60);
		DrawFormatStringToHandle(m_posx + 30, m_posy + 120, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "PUSH C OR R");
	}
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::ultra && m_counter >= 10800) {
		DrawFormatStringToHandle(m_posx + 30, m_posy + 30, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "FINISH!");
		DrawFormatStringToHandle(m_posx + 30, m_posy + 60, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "YOUR SCORE");
		DrawFormatStringToHandle(m_posx + 50, m_posy + 90, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "%d", m_score);
		DrawFormatStringToHandle(m_posx + 30, m_posy + 120, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "PUSH C OR R");
	}
	if (m_game_over == false && m_game_start == true && m_game_mode == enumGameMode::marathon && m_line >= 150 ) {
		DrawFormatStringToHandle(m_posx + 30, m_posy + 30, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "FINISH!");
		DrawFormatStringToHandle(m_posx + 30, m_posy + 60, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "YOUR SCORE");
		DrawFormatStringToHandle(m_posx + 50, m_posy + 90, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "%d", m_score);
		DrawFormatStringToHandle(m_posx + 30, m_posy + 120, GetColor(255, 255, 255), Font::getIns()->getFontHandle(), "PUSH C OR R");
	}
}

void TetrisMain::init(const enumGameMode _mode)
{
	m_score = 0;
	m_line = 0;
	m_game_level = 0;
	m_counter = 0;
	m_game_mode = _mode;
}

void TetrisMain::reset()
{
	m_field.reset();
	m_next.reset();
	m_mino.reset(m_next.getTopMino());

	m_game_level =	0;
	m_line       =	0;
	m_score      =	0;
	m_counter    =	0;
	m_game_start =	false;
	m_game_over  =	false;
	m_btob_flag  =	false;
	m_tspin_flag =	false;
	m_hold_rock  =	true;
	m_hold = enumMino::none;

}

void TetrisMain::mf_drawMino(const int _cx, const int _cy, const enumMino _mino) const
{
	double ex_rate = (double)TetrisDefine::MINO_SIZE / (double)TetrisDefine::MINO_IMAGE_SIZE;

	switch (_mino) {
	case enumMino::wall:
		DrawRotaGraph(_cx, _cy, ex_rate, 0.0, m_wall_image_handle, false);
		break;
	case enumMino::Z:
		DrawRectRotaGraph(_cx, _cy, 0, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::S:
		DrawRectRotaGraph(_cx, _cy, 20, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::J:
		DrawRectRotaGraph(_cx, _cy, 40, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::L:
		DrawRectRotaGraph(_cx, _cy, 60, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::I:
		DrawRectRotaGraph(_cx, _cy, 80, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::O:
		DrawRectRotaGraph(_cx, _cy, 100, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::T:
		DrawRectRotaGraph(_cx, _cy, 120, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::jammer:
		DrawRectRotaGraph(_cx, _cy, 140, 0, TetrisDefine::MINO_IMAGE_SIZE, TetrisDefine::MINO_IMAGE_SIZE, ex_rate, 0.0, m_mino_image_handle, true);
		break;
	case enumMino::none:
		DrawBox(_cx - TetrisDefine::MINO_SIZE / 2, _cy - TetrisDefine::MINO_SIZE / 2, _cx + TetrisDefine::MINO_SIZE / 2, _cy + TetrisDefine::MINO_SIZE / 2, GetColor(30, 30, 30), true);
		break;
	default:
		break;
	}
}

void TetrisMain::mf_drawTetroMino(int _cx, const int _cy, const enumMino _mino) const
{
	switch (_mino)
	{
	case enumMino::I:
		mf_drawMino(_cx, _cy, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy, _mino);
		mf_drawMino(_cx + 3 * TetrisDefine::MINO_SIZE, _cy, _mino);
		break;
	case enumMino::O:
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		break;
	case enumMino::Z:
		_cx += TetrisDefine::MINO_SIZE / 2;
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		break;
	case enumMino::S:
		_cx += TetrisDefine::MINO_SIZE / 2;
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		break;
	case enumMino::T:
		_cx += TetrisDefine::MINO_SIZE / 2;
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		break;
	case enumMino::L:
		_cx += TetrisDefine::MINO_SIZE / 2;
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		break;
	case enumMino::J:
		_cx += TetrisDefine::MINO_SIZE / 2;
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 0 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 0 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 1 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		mf_drawMino(_cx + 2 * TetrisDefine::MINO_SIZE, _cy + 1 * TetrisDefine::MINO_SIZE, _mino);
		break;
	default:
		break;
	}
}
