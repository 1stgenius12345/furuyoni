#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"
class CAlRamWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CAlRamWidget();
    CAlRamWidget(const CAlRamWidget& widget);
    virtual ~CAlRamWidget();

private:
    CSharedPtr<CImage>           m_ProfileImage;
    CSharedPtr<CImage>           m_TitleImage;


    float m_floattime;

public:
    void OtherTexture(const std::string& Name, const TCHAR* FileName)
    {
        m_TitleImage->SetTexture(Name, FileName);
     }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CAlRamWidget* Clone();

private:
    void StartClick();
    void ExitClick();
};

