#pragma once
#include<stack>
#include<memory>
#include"SceneChangeListenerInterface.h"

class SceneManger final : public SceneChangeListenerInterface{
public:
	SceneManger();
	~SceneManger() = default;

	void updateTopScene();
	void drawTopScene() const;

	void addNewScene(const enumScene _sceneName, const Parameter& parameter) override;
	void deleteNowScene(const Parameter& parameter) override;
private:
	std::stack<std::unique_ptr<AbstractScene>> m_uniqueSceneStack;
};