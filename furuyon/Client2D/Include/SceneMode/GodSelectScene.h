#pragma once

#include "Scene/SceneMode.h"

class CGodSelectScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CGodSelectScene();
    virtual ~CGodSelectScene();

public:
    virtual bool Init();

private:

};


