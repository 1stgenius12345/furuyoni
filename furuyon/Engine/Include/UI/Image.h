#pragma once

#include "Widget.h"
#include "../Resource/Texture.h"

class CImage :
    public CWidget
{
    friend class CViewport;
    friend class CScene;
    friend class CWidgetWindow;

protected:
    CImage();
    CImage(const CImage& widget);
    virtual ~CImage();

protected:
    CSharedPtr<CTexture>    m_Texture;
    const TCHAR* m_FileName;
    int m_ShaderIndex;

public:
    const std::string& GetTextureName() const
    {
        return m_Texture->GetName();
    }
    const TCHAR* GetFileName() const
    {
        return m_FileName;
    }
    void SetTexture(CTexture* Texture)
    {
        m_Texture = Texture;
    }

    void SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CImage* Clone();
};

