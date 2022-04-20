#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include  "UI/Image.h"


class CPlayerLogHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CPlayerLogHUDWidget();
    CPlayerLogHUDWidget(const CPlayerLogHUDWidget& widget);
    virtual ~CPlayerLogHUDWidget();

private:
    CSharedPtr<CImage>    m_UseCard;
    CSharedPtr<CImage>   m_TargetCard;
    CSharedPtr<CImage>     m_PlayerImage;

    bool m_UseCardBig;
    bool m_TargetCardBig;
 
public:
   
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerLogHUDWidget* Clone();

public:
    void CreateTex(int HeroIndex, int CardIndex, int CardClass);
    void CreateTex2(int HeroIndex, int CardIndex, int CardClass);

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
    void AiDaeugLog(int HeroIndex, int CardIndex, int CardClass, int HeroIndex2, int CardIndex2, int CardClass2);
    void AiBackCardLog(int focus);
    void AiFocusLog(int focus);
    void AiRefreshLog();
    void AiDrawLog();
    void AiUseLog(int HeroIndex, int CardIndex, int CardClass);
    void PlayerDaeugLog(int HeroIndex, int CardIndex, int CardClass, int HeroIndex2, int CardIndex2, int CardClass2);
    void PlayerBackCardLog(int focus);
    void PlayerFocusLog(int focus);
    void PlayerRefreshLog();
    void PlayerDrawLog();
    void PlayerUseLog(int HeroIndex, int CardIndex, int CardClass);
    void PlayerJaegiLog(int HeroIndex, int CardIndex, int CardClass);
    void AiJaegiLog(int HeroIndex, int CardIndex, int CardClass);
    void PlayerBurnLog(int HeroIndex, int CardIndex, int CardClass);
    void AiBurnLog(int HeroIndex, int CardIndex, int CardClass);

private:
    void ClickUse();
    void ClickBack();

};

