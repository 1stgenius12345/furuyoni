#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"

class CFocusHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CFocusHUDWidget();
    CFocusHUDWidget(const CFocusHUDWidget& widget);
    virtual ~CFocusHUDWidget();

private:
    CSharedPtr<CButton>    m_Forward;
    CSharedPtr<CButton>    m_Backward;
    CSharedPtr<CButton>    m_Ora;
    CSharedPtr<CButton>    m_Mana;

    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    int m_index;

    class CGameMapObj* m_GameMapObj;
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
    virtual CFocusHUDWidget* Clone();

public:
    void OpenWidget(int i);
    void CloseWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
    void ClickForward();
    void ClickBackward();
    void ClickOra();
    void ClickMana();
    void Clickital();
};

