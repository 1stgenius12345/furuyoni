#pragma once

#include "Scene\SceneMode.h"

class CGameMap :
    public CSceneMode
{
    friend class CScene;

protected:
    CGameMap();
    virtual ~CGameMap();

public:
    virtual bool Init();
};

