#pragma once
#include"SceneManager.h"
#include<memory>
#include"Fps.h"

class Looper {
public:
	Looper() = default;
	~Looper() = default;

	bool loop();

private:
	SceneManger m_sceneMgr;
	Fps _fps;
};