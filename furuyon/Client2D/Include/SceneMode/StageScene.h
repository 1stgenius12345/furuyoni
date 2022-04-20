#pragma once

#include "Scene/SceneMode.h"

class CStageScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CStageScene();
    virtual ~CStageScene();

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateParticle();
};


