#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"
#include "Excel.h"
class CGameMapAnimation :
    public CWidgetWindow
{
    friend class CViewport; 

public:
    CGameMapAnimation();
    CGameMapAnimation(const CGameMapAnimation& widget);
    virtual ~CGameMapAnimation();

private:
    CSharedPtr<CImage>           m_VS;
    CSharedPtr<CImage>           m_AlphaBlack;
    int     m_Player1firstindex;
    int     m_Player1secondindex;
    int     m_Player2firstindex;
    int     m_Player2secondindex;
    CSharedPtr<CImage>           m_Player1first;
    CSharedPtr<CImage>           m_Player1second;
    CSharedPtr<CImage>           m_Player2first;
    CSharedPtr<CImage>           m_Player2second;


    float m_firsttime;
    class CGameMapObj* m_GameMapObj;
    bool m_Turn;
    int m_WhoTrun;
    bool m_End;
    bool m_Triger1;
    bool m_Triger2;
public:
    void Set1secondindex(int i)
    {
        m_Player1secondindex = i;
        SetPlayer1second();
    }
    void Set2secondindex(int i)
    {
        m_Player2secondindex = i;
        SetPlayer2second();
    }
    void Set2firstindex(int i)
    {
        m_Player2firstindex = i;
        SetPlayer2first();
    }
    void Set1firstindex(int i)
    {
        m_Player1firstindex = i;
        SetPlayer1first();
    }
    void SetGameMapObj(class CGameMapObj* gameMap)
    {
        m_GameMapObj = gameMap;
    }
private:
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
    virtual CGameMapAnimation* Clone();

private:
    void StartClick();
    void ExitClick();
    void SetPlayer1first();
    void SetPlayer1second();
    void SetPlayer2first();
    void SetPlayer2second();

};

