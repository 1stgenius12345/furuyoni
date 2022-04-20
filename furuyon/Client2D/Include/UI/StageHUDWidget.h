#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"

class CStageHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CStageHUDWidget();
    CStageHUDWidget(const CStageHUDWidget& widget);
    virtual ~CStageHUDWidget();

private:

    std::vector<CSharedPtr<CButton>> m_vecMenuButton;
    class CButton* m_MirrorMenuButton;
    class CButton* m_StageMenuButton;


  

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CStageHUDWidget* Clone();

private:
    void StartClick();
    void ExitClick();
    void StageExitClick();
    void Nothing();
    void SetSelectButton();
};

