#pragma once
#include "GraphicShader.h"
class CUILogShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CUILogShader();
    virtual ~CUILogShader();

public:
    virtual bool Init();
};

