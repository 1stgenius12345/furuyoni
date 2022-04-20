#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include  "UI/Image.h"

class CMulrigunHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CMulrigunHUDWidget();
    CMulrigunHUDWidget(const CMulrigunHUDWidget& widget);
    virtual ~CMulrigunHUDWidget();

private:
    CSharedPtr<CButton>    m_DrawButton;

    CSharedPtr<CButton>    m_Firstinfo;
    CSharedPtr<CButton>    m_Secondinfo;
    CSharedPtr<CButton>    m_Thirdinfo;

    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    bool m_CloseEndCheck;
    class CGameMapObj* m_GameMapObj;

    class CCard* m_firstCard;
    class CCard* m_SecondCard;
    class CCard* m_ThirdCard;

    bool m_HandCardBurn;


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
    virtual CMulrigunHUDWidget* Clone();

public:
    void OpenWidget();
    void CloseWidget();
    void ClosePlayer1EndWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
public:

private:
    void DrawButton();
    void BurnButton();
    void RefreshButton();

};

