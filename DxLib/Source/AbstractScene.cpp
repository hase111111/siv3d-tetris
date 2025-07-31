#include "AbstractScene.h"

AbstractScene::AbstractScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) :
	mp_listenerInterface(pScli)
{
}
