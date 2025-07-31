#pragma once
#include"AbstractScene.h"
#include<memory>
#include"Image.h"

class TitleScene final : public AbstractScene {
public:
	TitleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	void update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	int m_image_handle;
	int m_image_handle2;
	int m_image_handle3;

	unsigned int m_anime_counter = 0;
	unsigned int m_mode_counter = 0;
};