#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Image.h"
#include "UI/NumberWidget.h"

class CBuildingHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

public:
    CBuildingHUDWidget();
    CBuildingHUDWidget(const CBuildingHUDWidget& widget);
    virtual ~CBuildingHUDWidget();

private:
    CSharedPtr<CNumberWidget>    m_BuildingNumber;

    class CBuildingCard* m_OwnerCard;

public:
    void SetBuildingCard(class CBuildingCard* card)
    {
        m_OwnerCard = card;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CBuildingHUDWidget* Clone();
    void UseNabRenderUpdate();
    void UnUseNabRenderUpdate();

};

