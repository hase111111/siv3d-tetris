#pragma once
#include"Parameter.h"
#include"SceneChangeListenerInterface.h"

class SceneChangeListenerInterface;

class AbstractScene
{
protected:
    SceneChangeListenerInterface* mp_listenerInterface;
public:
    //&‚ğ‚Â‚¯‚é‚±‚Æ‚ÅƒRƒs[‚ğ‘j~
    AbstractScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);
    virtual ~AbstractScene() = default;
    virtual void update()     = 0;
    virtual void draw() const = 0;
    virtual void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) = 0;
};