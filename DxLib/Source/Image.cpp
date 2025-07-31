#include"Image.h"
#include"DxLib.h"
#include"Error.h"

void Image::release() 
{
}

int Image::myLoadGraph(std::string str) {
	//Šù‚É“Ç‚İ‚İÏ‚İ‚È‚ç‚Î
	if (m_images.count(str) != 0) { return m_images.at(str); }

	//‚»‚¤‚Å‚È‚¯‚ê‚Î‰æ‘œ‚ğ“Ç‚İ‚Ş
	const int temp_gr_handle = LoadGraph(str.c_str());

	if (temp_gr_handle == -1) { ERR("‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½"); }

	//‹L˜^
	m_images[str] = temp_gr_handle;
	return temp_gr_handle;
}