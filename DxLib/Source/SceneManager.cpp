#include"SceneManager.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"Error.h"

SceneManger::SceneManger()
{
	Parameter tempParam;
	m_uniqueSceneStack.push(std::make_unique<TitleScene>(this, tempParam));
}

void SceneManger::updateTopScene()
{
	m_uniqueSceneStack.top()->update();
}

void SceneManger::drawTopScene() const
{
	m_uniqueSceneStack.top()->draw();
}

void SceneManger::addNewScene(const enumScene _sceneName, const Parameter& parameter)
{
	switch (_sceneName)
	{
	case enumScene::title:
		m_uniqueSceneStack.push(std::make_unique<TitleScene>(this, parameter));
		break;

	case enumScene::game:
		m_uniqueSceneStack.push(std::make_unique<GameScene>(this, parameter));
		break;

	default:
		ERR("存在していないシーンの追加依頼が出されました");
		break;
	}
}

void SceneManger::deleteNowScene(const Parameter& parameter)
{
	m_uniqueSceneStack.pop();
	if (m_uniqueSceneStack.empty())ERR("シーンが存在していません");

	m_uniqueSceneStack.top()->receiveParameterInCaseOfDeleteScene(parameter);
}