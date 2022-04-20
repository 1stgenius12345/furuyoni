#pragma once

#include "GraphicShader.h"

class CStandard2DLog :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CStandard2DLog();
    virtual ~CStandard2DLog();

public:
    virtual bool Init();
};

