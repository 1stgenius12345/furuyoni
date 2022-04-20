#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include  "UI/Image.h"
enum class GameMapButtonType
{
    None,
    Gaeshi,
    Building,
    Attacked,
    Chozo,
    Player1Win,
    Player2Win,
    Player1AttackSelect,
    Player1Daeung,
    Player1DustRange,
    Player1Hero3Card6,
    Player1Hero8card3,
    Player1Hero8card4,
    CardBurn,
    End

};

class CGaeSiPhaseHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CGaeSiPhaseHUDWidget();
    CGaeSiPhaseHUDWidget(const CGaeSiPhaseHUDWidget& widget);
    virtual ~CGaeSiPhaseHUDWidget();

private:
    CSharedPtr<CButton>    m_DrawButton;
    CSharedPtr<CButton>    m_RefreshButton;
    CSharedPtr<CButton>    m_HideButton;
    CSharedPtr<CImage>     m_Arrow;
    CSharedPtr<CNumberWidget> m_OraNumberWidget;
    CSharedPtr<CNumberWidget> m_LifeNumberWidget;
    bool m_Open;
    bool m_Close;
    bool m_OpenStartCheck;
    class CGameMapObj* m_GameMapObj;
    class CAttackCard* m_AttackCard;
    class CBuildingCard* m_BuildingCard;
    class CCard* m_DaeugCard;
    int m_valuex;
    int m_valuey;
    int m_Nab;
    int m_Chozo;
    GameMapButtonType m_Type;
    bool m_Hide;
    class CCard* m_firstSellectCard;
    class CCard* m_secondSellectCard;
    class CCard* m_TempCard;
    
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
    virtual CGaeSiPhaseHUDWidget* Clone();

public:
    void OpenWidget();
    void CloseWidget();

private:
    void StartClick();
    void Open(float DeltaTime);
    void Close(float DeltaTime);
public:
    void ClickForwardBytype(GameMapButtonType type,class CCard* card,int x,int y);
    void ClickDaeung(class CAttackCard* card, bool b);
    void ClickCardBurn(int index);
    

private:
    void DrawButton();
    void RefreshButton();
    void ClickOra();
    void ClickMana();
    void ShieldNab();
    void DustNab();
    void CloseBuildingWidget();
    void ChozoOra();
    void ChozoLife();
    void Player1winbutton();
    void Player1winResult();
    void Player2winButton();
    void Player2winResult();
    void Player1AttackSelectShield();
    void Player1AttackSelectLife();
    void Player1Daueg();
    void Player1DauegExit();
    void MouseOnLeftForRightArrow();
    void MouseOnRightForLeftArrow();
    void DustToRange();
    void RangeToDust();
    void Hero3Card6Left();
    void Hero3Card6Right();
    void HideButton();
    void Hero8Card3Left();
    void Heor8Card3Right();
    void Hero8Card4();
    void CardBurnLeft();
    void CardBurnRight();
};

