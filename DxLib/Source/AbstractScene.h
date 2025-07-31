#pragma once
#include"Parameter.h"
#include"SceneChangeListenerInterface.h"

class SceneChangeListenerInterface;

class AbstractScene
{
protected:
    SceneChangeListenerInterface* mp_listenerInterface;
public:
    //&�����邱�ƂŃR�s�[��j�~
    AbstractScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);
    virtual ~AbstractScene() = default;
    virtual void update()     = 0;
    virtual void draw() const = 0;
    virtual void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) = 0;
};