
#pragma once
#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "../Object/SelectCard.h"
#include "../Object/Deck.h"
class CSelectHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CSelectHUDWidget();
    CSelectHUDWidget(const CSelectHUDWidget& widget);
    virtual ~CSelectHUDWidget();
protected:
    CSharedPtr<CButton>          m_firstHero;
    CSharedPtr<CButton>          m_secondHero;
    CSharedPtr<CImage>           m_ImageNormal;
    CSharedPtr<CImage>           m_ImageHero;
    CSharedPtr<CButton>          m_PageName;
    CSharedPtr<CButton>          m_PageNext;
    CSharedPtr<CButton>          m_Ready;
    CSharedPtr<CNumberWidget>    m_HeroCardIN;
    CSharedPtr<CNumberWidget>    m_NormalCardIN;
    CSharedPtr<CText>            m_HeroText;
    CSharedPtr<CDeck>            m_Deck;
    CSharedPtr<CDeck>            m_Deck2;
    class CSelectCard*           m_SelectCard;
    int m_Deckindex;

public:
    int GetNormalCard() const
    {
        return m_NormalCardIN->GetNumber();
    }
    int GetHeroCard() const
    {
        return m_HeroCardIN->GetNumber();
    }
    void SetSelectCard(class CSelectCard* card)
    {
        m_SelectCard = card;
    }
    void AddHeroCard(int value)
    {
        m_HeroCardIN->AddNumber(value);
    }
    void AddNormalCard(int value)
    {
        m_NormalCardIN->AddNumber(value);
    }

    


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CSelectHUDWidget* Clone();

private:
    void StartClick();
    void ExitClick();
    void FirstHeroClick();
    void SecondHeroClick();
    void Next();

public:
    void SetDeck(CDeck* deck);
    void SetDeck2(CDeck* deck);
    void SetDecktitle(CDeck* deck);
public:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);
    void SetLookUp(bool b);
};

