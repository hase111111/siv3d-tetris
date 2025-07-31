#pragma once
#include "Singleton.h"
#include <map>
#include<string>

class Image final : public Singleton<Image> {

public:
    Image() {};
    ~Image() = default;

    void release();
    int myLoadGraph(std::string str);

private:
    std::map<std::string, int> m_images;
};