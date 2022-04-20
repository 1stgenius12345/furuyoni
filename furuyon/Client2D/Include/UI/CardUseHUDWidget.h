#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include  "UI/Image.h"


class CCardUseHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CCardUseHUDWidget();
    CCardUseHUDWidget(const CCardUseHUDWidget& widget);
    virtual ~CCardUseHUDWidget();

private:
    CSharedPtr<CButton>    m_DrawButton;
    CSharedPtr<CButton>    m_RefreshButton;
   
    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    class CGameMapObj* m_GameMapObj;
    class CCard* m_DaeugCard;
    float m_valuex;
    float m_valuey;
    int m_Nab;
    int m_Chozo;




public:
    void SetGameMapObj(class CGameMapObj* gameMapObj)
    {
        m_GameMapObj = gameMapObj;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CCardUseHUDWidget* Clone();

public:
    void OpenWidget(float x, float y, int i, int index);
    void CloseWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
public:
  


private:
    void ClickUse();
    void ClickBack();
   
};

