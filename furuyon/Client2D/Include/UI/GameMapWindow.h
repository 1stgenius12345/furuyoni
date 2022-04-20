#pragma once
#define RangeNumber 1
#define DustNumber 2
#define Player1LifeNumber 3
#define Player1ShiledNumber 4
#define Player1ManaNumber 5
#define Player1FocusNumber 6
#define Player1DeckNumber 7
#define Player2LifeNumber 8
#define Player2ShiledNumber 9
#define Player2ManaNumber 10
#define Player2FocusNumber 11
#define Player2DeckNumber 12
#define DalinNumber 13
#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/Image.h"
#include "UI/NumberWidget.h"
class CGameMapWindow :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CGameMapWindow();
    CGameMapWindow(const CGameMapWindow& widget);
    virtual ~CGameMapWindow();
private:
 
    CSharedPtr<CNumberWidget>    m_Range_Number;

    CSharedPtr<CNumberWidget>    m_Dust_Number;

    //player1
  
    CSharedPtr<CNumberWidget>    m_Player1_Life_Number;

    CSharedPtr<CNumberWidget>    m_Player1_Shiled_Number;
  
    CSharedPtr<CNumberWidget>    m_Player1_Mana_Number;

    CSharedPtr<CNumberWidget>    m_Player1_Focus_Number;

    CSharedPtr<CNumberWidget>    m_Player1_Deck_Number;

    //player2
  
    CSharedPtr<CNumberWidget>    m_Player2_Life_Number;
   
    CSharedPtr<CNumberWidget>    m_Player2_Shiled_Number;
  
    CSharedPtr<CNumberWidget>    m_Player2_Mana_Number;

    CSharedPtr<CNumberWidget>    m_Player2_Focus_Number;

    CSharedPtr<CNumberWidget>    m_Player2_Deck_Number;

    CSharedPtr<CNumberWidget>    m_Dalin_Number;

    CSharedPtr<CText>            m_FPS;

    CSharedPtr<CImage>     m_Player1Press;

    CSharedPtr<CImage>     m_Player2Press;

    class CGameMapObj* m_GameMapObj;

    bool m_Animation;
    float m_AnimationTime;
    std::queue<int> m_que_Animation;

public:
    void PushAnimation(int i)
    {
        m_que_Animation.push(i);
    }
    void SetGameMapObj(class CGameMapObj* gameMap)
    {
        m_GameMapObj = gameMap;
    }

public:
    const TCHAR* StringToTCHAR(std::string& s)
    {
       // tstring tstr;
        size_t temp;
        const char* all = s.c_str();
        int len = 1 + strlen(all);
        wchar_t* t = new wchar_t[len];
        if (NULL == t) throw std::bad_alloc();
        mbstowcs_s(&temp,t, len, s.c_str(), _TRUNCATE);
        return (TCHAR*)t;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CGameMapWindow* Clone();

private:
    void StartClick();
    void ExitClick();
    void CreateTextANDNumber(const std::string& Numbername,  CSharedPtr<CNumberWidget>& Number, Vector2 pos, const TCHAR* name, int num, float size);
    void AddNumberSizePlus(float delta, int index);
    void SetNumberSizePlus(float delta, int index);
};

