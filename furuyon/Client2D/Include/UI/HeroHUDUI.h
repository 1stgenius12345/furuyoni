#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/Image.h"
class CHeroHUDUI :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CHeroHUDUI();
    CHeroHUDUI(const CHeroHUDUI& widget);
    virtual ~CHeroHUDUI();

private:
    CSharedPtr<CButton>    m_HeroDeckButton;

  //  CSharedPtr<CImage>    m_HeroDeckBack;

    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    bool m_OpenEnd;
    bool m_CloseEnd;

    class CGameMapObj* m_GameMapObj;
public:
    bool GetOpen() const
    {
        return m_Open;
    }
    void SetGameMapObj(class CGameMapObj* gameMapObj)
    {
        m_GameMapObj = gameMapObj;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CHeroHUDUI* Clone();

public:
    void OpenWidget();
    void CloseWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
    void ClickForward();
    void ClickBackward();
    void ClickOra();
    void ClickMana();
};

