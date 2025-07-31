#pragma once
#include"EnumTetris.h"

class Next final {
public:
	Next();
	enumMino getTopMino();
	void getDrawMino(enumMino(&_mino)[6]) const;
	void reset();
private:
	enumMino m_minos[21];
	void mf_addNewMinoBack();
};
