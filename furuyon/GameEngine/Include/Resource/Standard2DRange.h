#pragma once

#include "GraphicShader.h"

class CStandard2DRange :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CStandard2DRange();
    virtual ~CStandard2DRange();

public:
    virtual bool Init();
};

