#pragma once

#include "GraphicShader.h"

class CStandard2DtitleShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CStandard2DtitleShader();
    virtual ~CStandard2DtitleShader();

public:
    virtual bool Init();
};

