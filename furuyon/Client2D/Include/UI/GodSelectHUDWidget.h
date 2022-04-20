
#pragma once
#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "../Object/SelectCard.h"
#include "../Object/Deck.h"
class CGodSelectHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CGodSelectHUDWidget();
    CGodSelectHUDWidget(const CGodSelectHUDWidget& widget);
    virtual ~CGodSelectHUDWidget();
protected:
    std::vector< CSharedPtr<CButton>> m_vec_HeroButton;
 
    int m_FirstDeckIndex;
    CSharedPtr<CImage>           m_ImageNormal;
    int m_SecondDeckIndex;
    CSharedPtr<CImage>           m_ImageHero;


    CSharedPtr<CButton>          m_PageName;
    CSharedPtr<CButton>          m_HeroSelect;
    CSharedPtr<CButton>          m_Ready;

    CSharedPtr<CText>            m_HeroText;
    CSharedPtr<CDeck>            m_Deck;

    class CGodSelectObj*    m_SelectCard;
    int m_Deckindex;
   // CSharedPtr<CImage>           m_SelectHero;


public:
   
   
    void SetSelectCard(class CGodSelectObj* card)
    {
        m_SelectCard = card;
    }
  
    const std::string TCHARToString(const TCHAR* ptsz)
    {
        int len = (int)wcslen((wchar_t*)ptsz);

        char* psz = new char[2 * len + 1];

        wcstombs_s(nullptr, psz, sizeof(wchar_t) * len, (wchar_t*)ptsz, 2 * len + 1);
        std::string s = psz;
        delete[] psz;

        return s;
    }



public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CGodSelectHUDWidget* Clone();

private:
    void StartClick();
    void ExitClick();
    void FirstHeroClick();
    void SecondHeroClick();
    void tokoyoHeroClick();
    void Next();
    void Select();

public:
    void SetDeck(CDeck* deck);
   
    void SetDecktitle(CDeck* deck);
public:
   
    void SetLookUp(bool b);

private:
    void SetAllGrayButton(int index);
    void SetMegami();
    void SetMegami2();

};

