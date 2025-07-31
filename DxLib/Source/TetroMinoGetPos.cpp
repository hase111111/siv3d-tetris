#include"TetroMino.h"

void TetroMino::getMinoPos(int(&_meta)[4][2], const bool _get_gost) const
{
	int _fieldx = m_fieldx;
	int _fieldy = m_fieldy;

	//ÉSÅ[ÉXÉgèàóù
	if (_get_gost) {
		while (mf_canSetMinoInField(_fieldx, _fieldy + 1))
		{
			_fieldy += 1;
		}
	}

	switch (m_mino){
	case enumMino::O:
		_meta[0][0] = _fieldx + 0;_meta[0][1] = _fieldy + 0;
		_meta[1][0] = _fieldx + 1;_meta[1][1] = _fieldy + 0;
		_meta[2][0] = _fieldx + 0;_meta[2][1] = _fieldy + 1;
		_meta[3][0] = _fieldx + 1;_meta[3][1] = _fieldy + 1;
		break;
	case enumMino::S:
		if (m_roll % 4 == 0) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy;
		}
		else if (m_roll % 4 == 1) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 2) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 2;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 3) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 0; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 1; _meta[3][1] = _fieldy + 2;
		}
		break;
	case enumMino::Z:
		if (m_roll % 4 == 0) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 0;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 1) {
			_meta[0][0] = _fieldx + 2; _meta[0][1] = _fieldy;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 1; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 2) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 3) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 0; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 0; _meta[3][1] = _fieldy + 2;
		}
		break;
	case enumMino::L:
		if (m_roll % 4 == 0) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 0;
		}
		else if (m_roll % 4 == 1) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 2) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 0; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 3) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 0; _meta[3][1] = _fieldy + 0;
		}
		break;
	case enumMino::J:
		if (m_roll % 4 == 0) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 0; _meta[3][1] = _fieldy + 0;
		}
		else if (m_roll % 4 == 1) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 0;
		}
		else if (m_roll % 4 == 2) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 3) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 0; _meta[3][1] = _fieldy + 2;
		}
		break;
	case enumMino::T:
		_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 1;

		if (m_roll % 4 == 0) {
			_meta[1][0] = _fieldx; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 1) {
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 2) {
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 2;
			_meta[2][0] = _fieldx; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 3) {
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy;
			_meta[2][0] = _fieldx; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 1; _meta[3][1] = _fieldy + 2;
		}
		break;
	case enumMino::I:
		if (m_roll % 4 == 0) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 1;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 1;
			_meta[3][0] = _fieldx + 3; _meta[3][1] = _fieldy + 1;
		}
		else if (m_roll % 4 == 1) {
			_meta[0][0] = _fieldx + 2; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 2; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 2; _meta[3][1] = _fieldy + 3;
		}
		else if (m_roll % 4 == 2) {
			_meta[0][0] = _fieldx + 0; _meta[0][1] = _fieldy + 2;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 2;
			_meta[2][0] = _fieldx + 2; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 3; _meta[3][1] = _fieldy + 2;
		}
		else if (m_roll % 4 == 3) {
			_meta[0][0] = _fieldx + 1; _meta[0][1] = _fieldy + 0;
			_meta[1][0] = _fieldx + 1; _meta[1][1] = _fieldy + 1;
			_meta[2][0] = _fieldx + 1; _meta[2][1] = _fieldy + 2;
			_meta[3][0] = _fieldx + 1; _meta[3][1] = _fieldy + 3;
		}
		break;
	default:
		break;
	}
}
