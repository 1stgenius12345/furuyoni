#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"
class CBackHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CBackHUDWidget();
    CBackHUDWidget(const CBackHUDWidget& widget);
    virtual ~CBackHUDWidget();

private:
    CSharedPtr<CImage>           m_ProfileImage;
    class CButton*          m_first2Hero;

    bool m_hide;

public:
  
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CBackHUDWidget* Clone();

public:
    void BackButton();
    void Show(float Deltatime);
};

