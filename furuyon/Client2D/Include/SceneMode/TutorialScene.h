#pragma once

#include "Scene/SceneMode.h"

class CTutorialScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CTutorialScene();
    virtual ~CTutorialScene();

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateParticle();
};


