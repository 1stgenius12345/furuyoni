#pragma once

#include "GraphicShader.h"

class CStandard2DCard :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CStandard2DCard();
    virtual ~CStandard2DCard();

public:
    virtual bool Init();
};

