#pragma once
#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include  "UI/Image.h"

enum class PhaseType
{
    None,
    Player1Gaeshi,
    Player1Main,
    Player1Exit,
    Player2Gasehi,
    Player2Main,
    Player2Exit,
    End,
};
class CPhaseHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CPhaseHUDWidget();
    CPhaseHUDWidget(const CPhaseHUDWidget& widget);
    virtual ~CPhaseHUDWidget();

private:
    CSharedPtr<CButton>    m_DrawButton;


    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    class CGameMapObj* m_GameMapObj;

    int m_valuex;
    int m_valuey;
    int m_Nab;
    int m_Chozo;
    float m_ReturnTime;
    PhaseType m_PhaseType;
    bool m_ButtonTriger;

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
    virtual CPhaseHUDWidget* Clone();

public:
    void OpenWidget();
    void CloseWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
public:
   void CreatePhaseUI(PhaseType type);
private:
    void DrawButton();
    void RefreshButton();
    void Player1TurnEnd();
};

