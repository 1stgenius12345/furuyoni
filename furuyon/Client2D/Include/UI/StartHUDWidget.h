#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"
class CStartHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CStartHUDWidget();
    CStartHUDWidget(const CStartHUDWidget& widget);
    virtual ~CStartHUDWidget();

private:
    CSharedPtr<CImage>           m_ProfileImage;
    CSharedPtr<CImage>           m_TitleImage;
    std::vector<CSharedPtr<CButton>> m_vecMenuButton;
    class CButton* m_tutorialButton;
    class CButton* m_MirrorMenuButton;
    class CButton* m_StageMenuButton;
    class CButton* m_Button2;
    class CStartMapObj* m_MapObj;
    class CButton* m_SelectButton;


    bool m_WhiteMaxState;
    float m_WhiteTime;
    float m_BlurCount;
    bool m_Stage2;
    bool m_StartstageWhiteDesolve;
    bool m_StartstageWhiteDesolveMax;
    float m_ExitStageCount;
    bool m_ExitStage;
    bool m_Stage;
    bool m_titlesound;
    int m_ButtonIndex;
    bool m_ButtonAnimationRight;
    bool m_ButtonAnimationLeft;
    float m_ButtonAnimationTime;
public:
    void SetMapObj(class CStartMapObj* MapObj)
    {
        m_MapObj = MapObj;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CStartHUDWidget* Clone();

private:
    void StartClick();
    void ExitClick();
    void StageExitClick();
    void Nothing();
    void SetSelectButton();
};

