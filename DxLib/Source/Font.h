#pragma once
#include"Singleton.h"
#include<string>

class Font : public Singleton<Font> {
private:
	friend Singleton<Font>;

public:
	bool LoadFont();

	int getFontHandle();

	void releaseFont();

private:
	//�t�H���g�f�[�^���u���Ă���p�X
	const std::string FONT_PATH = "dat/font/dot_font.dft";

	//�t�H���g�̃n���h��
	int font_handle = 0;
};
