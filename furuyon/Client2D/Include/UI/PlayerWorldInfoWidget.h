#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
#include "UI/NumberWidget.h"
#include "UI/image.h"

class CPlayerWorldInfoWidget :
    public CWidgetWindow
{
public:
    CPlayerWorldInfoWidget();
    CPlayerWorldInfoWidget(const CPlayerWorldInfoWidget& widget);
    virtual ~CPlayerWorldInfoWidget();

private:
    CSharedPtr<CText>   m_NameText;
    CSharedPtr<CText>   m_ContentsText;
    CSharedPtr<CText>   m_RangeTilde;
  //  CSharedPtr<CProgressBar>    m_HPBar;
    CSharedPtr<CNumberWidget>    m_AttackShield_NumberWidget;
    CSharedPtr<CNumberWidget>    m_AttackLife_NumberWidget;
    CSharedPtr<CNumberWidget>    m_RangeMin;
    CSharedPtr<CNumberWidget>    m_RangeMax;
    CSharedPtr<CImage>           m_ProfileImage;
    CSharedPtr<CImage>           m_CardImage;
public:
   
    const std::string& GetTextureName() const
    {
        return m_ProfileImage->GetTextureName();
    }
    int GetRangeMax() const
    {
        return m_RangeMax->GetNumber();
    }
    void SetRangeMax(int num)
    {
        m_RangeMax->SetNumber(num);
    }
    int GetRangeMin() const
    {
        return m_RangeMin->GetNumber();
    }
    void SetRangeMin(int num)
    {
        m_RangeMin->SetNumber(num);
    }
    int GetAttackLife() const
    {
        return m_AttackLife_NumberWidget->GetNumber();
    }
    void SetAttackLife(int num)
    {
        m_AttackLife_NumberWidget->SetNumber(num);
    }
    int GetAttackShield() const
    {
       return m_AttackShield_NumberWidget->GetNumber();
    }
    void SetAttackShield(int num)
    {
        m_AttackShield_NumberWidget->SetNumber(num);
    }

    const TCHAR* GetFileName() const
    {
        return m_ProfileImage->GetFileName();
    }
    void SetTexture(const std::string& Name,const TCHAR* Texture)
    {
        m_ProfileImage->SetTexture(Name, Texture);
    }
    const TCHAR* GetCardName() const
    {
        return m_NameText->GetText();
    }
    void SetCardName(const TCHAR* Text)
    {
        m_NameText->SetText(Text);
    }

    //CSharedPtr<CNumberWidget>    m_Check_PosX;
    //CSharedPtr<CNumberWidget>    m_Check_PosY;




public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerWorldInfoWidget* Clone();

public:
    void ClickCallback();
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void UpdatePosANDScale();


};

