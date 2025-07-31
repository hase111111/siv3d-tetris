#pragma once
#include"SceneEnum.h"
#include"Parameter.h"
#include"AbstractScene.h"

class SceneChangeListenerInterface {
public:
	SceneChangeListenerInterface() = default;
	virtual ~SceneChangeListenerInterface() = default;

	virtual void addNewScene(const enumScene _sceneName, const Parameter& parameter) = 0;
	virtual void deleteNowScene(const Parameter& parameter) = 0;
};