#include"Image.h"
#include"DxLib.h"
#include"Error.h"

void Image::release() 
{
}

int Image::myLoadGraph(std::string str) {
	//���ɓǂݍ��ݍς݂Ȃ��
	if (m_images.count(str) != 0) { return m_images.at(str); }

	//�����łȂ���Ή摜��ǂݍ���
	const int temp_gr_handle = LoadGraph(str.c_str());

	if (temp_gr_handle == -1) { ERR("�摜�̓ǂݍ��݂Ɏ��s���܂���"); }

	//�L�^
	m_images[str] = temp_gr_handle;
	return temp_gr_handle;
}