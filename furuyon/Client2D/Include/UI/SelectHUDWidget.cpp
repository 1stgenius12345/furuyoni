#include "SelectHUDWidget.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/GameMap.h"
#include "Scene/SceneManager.h"
#include "UI/Text.h"
#include "UI/Image.h"
#include "UI/NumberWidget.h"
#include "Input.h"
#include "Timer.h"

CSelectHUDWidget::CSelectHUDWidget() :
	m_Deckindex(0)
{
}

CSelectHUDWidget::CSelectHUDWidget(const CSelectHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CSelectHUDWidget::~CSelectHUDWidget()
{
}

bool CSelectHUDWidget::Init()
{

	CWidgetWindow::Init();
	
	m_Deckindex = 1;

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	m_firstHero = CreateWidget<CButton>("firstHero");

	m_firstHero->SetPos(50.f, 648.f);
	m_firstHero->SetSize(341.f/5.3f, 387.f/ 5.3f);
	switch (CClientManager::GetInst()->Getfirst())
	{
	case 1:
		m_firstHero->SetStateTexture("Yurina_Button", TEXT("Yurina_Button.png"));
		break;
	case 3:
		m_firstHero->SetStateTexture("Saine_Button", TEXT("Saine_Button.png"));
		break;
	case 8:
		m_firstHero->SetStateTexture("tokoyo", TEXT("tokoyo.png"));
		break;
	default:
		break;
	}
	m_firstHero->SetInteractionSound(Button_Sound_State::Click, "HeroSelectButoon");
	m_firstHero->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_firstHero->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_firstHero->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_firstHero->SetClickCallback<CSelectHUDWidget>(this, &CSelectHUDWidget::FirstHeroClick);
	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");
	m_secondHero = CreateWidget<CButton>("secondHero");

	m_secondHero->SetPos(115.f, 648.f);
	m_secondHero->SetSize(341.f/ 5.3f, 387.f/ 5.3f);
	switch (CClientManager::GetInst()->Getsecond())
	{
	case 1:
		m_secondHero->SetStateTexture("Yurina_Button", TEXT("Yurina_Button.png"));
		break;
	case 3:
		m_secondHero->SetStateTexture("Saine_Button", TEXT("Saine_Button.png"));
		break;
	case 8:
		m_secondHero->SetStateTexture("tokoyo", TEXT("tokoyo.png"));
		break;
	default:
		break;
	}
	m_secondHero->SetInteractionSound(Button_Sound_State::Click, "HeroSelectButoon");
	m_secondHero->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
	m_secondHero->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
	m_secondHero->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f ,1.f);
	m_secondHero->SetClickCallback<CSelectHUDWidget>(this, &CSelectHUDWidget::SecondHeroClick);
	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");
	// 
	// HeroSelectButoon
	// 일반카드
	m_PageName = CreateWidget<CButton>("NormalCard");
	m_PageName->SetPos(800.f, 418.f);
	m_PageName->SetSize(132.f / 1.8f, 359.f / 1.8f);
	m_PageName->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_PageName->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_PageName->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_PageName->SetClickCallback<CSelectHUDWidget>(this, &CSelectHUDWidget::StartClick);
	m_PageName->SetInteractionSound(Button_Sound_State::Click, "NormalHeroChange");
	// 영웅 카드
 //   m_PageNext = CreateWidget<CButton>("HeroCard");
	//m_PageNext->SetPos(802.f, 428.f - 290.f * 720.f / 905.f);
	//m_PageNext->SetSize(205.f * 1280.f / 1603.f, 290.f * 720.f / 905.f);
	//m_PageNext->SetStateTexture(Button_State::Normal, "HeroCard", TEXT("button/HeroCard_Button.png"));
	//m_PageNext->SetStateTexture(Button_State::MouseOn, "HeroCard", TEXT("button/HeroCard_Button.png"));
	//m_PageNext->SetStateTexture(Button_State::Click, "HeroCard", TEXT("button/HeroCard_Button.png"));
	//m_PageNext->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	//m_PageNext->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	//m_PageNext->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	//m_PageNext->SetClickCallback<CSelectHUDWidget>(this, &CSelectHUDWidget::StartClick);



	m_ImageNormal = CreateWidget<CImage>("NormalInfo");

	m_ImageNormal->SetTexture("NormalInfo2", TEXT("Hero_Select.png"));
	m_ImageNormal->SetPos(1264.f * 1280.f / 1603.f, 58.f * 720.f / 905.f+40.f);
	m_ImageNormal->SetSize(201.f, 359.f * (201.f / 254.f));
	
	m_NormalCardIN = CreateWidget<CNumberWidget>("NormalCardIn");
	m_NormalCardIN->SetPos(1006.f, 496.f);
	m_NormalCardIN->SetNumberSize(150.f/1.2f, 134.f / 1.2f);
	m_NormalCardIN->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	m_NormalCardIN->SetNumber(0);
	m_NormalCardIN->SetFrameCount(10, 4);
	m_NormalCardIN->SetZOrder(3);

	m_ImageHero = CreateWidget<CImage>("HeroInfo");
	m_ImageHero->SetTexture("HeroInfo2", TEXT("Normal_Select.png"));
	m_ImageHero->SetPos(1264.f * 1280.f / 1603.f, 437.f * 720.f / 905.f+40.f);
	m_ImageHero->SetSize(201.f, 359.f * (201.f / 254.f));


	m_HeroCardIN = CreateWidget<CNumberWidget>("HeroCardIn");
	m_HeroCardIN->SetPos(1006.f, 186.f);
	m_HeroCardIN->SetNumberSize(150.f / 1.2f, 134.f / 1.2f);
	m_HeroCardIN->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	m_HeroCardIN->SetNumber(0);
	m_HeroCardIN->SetFrameCount(10, 4);
	m_HeroCardIN->SetZOrder(3);




	




	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	//  준비 완료
	m_Ready = CreateWidget<CButton>("ReadyButton");
	m_Ready->SetPos(Center.x + 310.f, Center.y-370.f);
	m_Ready->SetSize(317.f/1.3f, 105.f / 1.3f);
	m_Ready->SetStateTexture(Button_State::Normal, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTexture(Button_State::MouseOn, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTexture(Button_State::Click, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetStateTint(Button_State::MouseOn, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetClickCallback<CSelectHUDWidget>(this, &CSelectHUDWidget::Next);








	return true;
}

void CSelectHUDWidget::Update(float DeltaTime)
{
	if (m_HeroCardIN->GetNumber() == 3 && m_NormalCardIN->GetNumber() == 7)
	{
		m_Ready->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
		m_Ready->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.f);
		m_Ready->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	}
	else
	{
		m_Ready->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 1.f);
		m_Ready->SetStateTint(Button_State::MouseOn, 0.6f, 0.6f, 0.6f, 1.f);
		m_Ready->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	}
	CWidgetWindow::Update(DeltaTime);
}

void CSelectHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CSelectHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CSelectHUDWidget* CSelectHUDWidget::Clone()
{
	return new CSelectHUDWidget(*this);
}

void CSelectHUDWidget::StartClick()
{
	if (m_Deckindex == 1)
	{
		if (m_Deck->GetRendernormal())
		{
			m_PageName->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));

			//m_PageNext->SetStateTexture(Button_State::Normal, "HeroCard", TEXT("button/HeroCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::MouseOn, "HeroCard", TEXT("button/HeroCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::Click, "HeroCard", TEXT("button/HeroCard_Button.png"));
		}
		else
		{
			m_PageName->SetStateTexture(Button_State::Normal, "HeroCard", TEXT("button/HeroCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::MouseOn, "HeroCard", TEXT("button/HeroCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::Click, "HeroCard", TEXT("button/HeroCard_Button.png"));

			//m_PageNext->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));
		}

		m_Deck->SelectSetting();
		m_Deck2->SelectOtherSetting();
		
	}
	else if (m_Deckindex == 2)
	{
		if (m_Deck2->GetRendernormal())
		{
			m_PageName->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));

			//m_PageNext->SetStateTexture(Button_State::Normal, "HeroCard", TEXT("button/HeroCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::MouseOn, "HeroCard", TEXT("button/HeroCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::Click, "HeroCard", TEXT("button/HeroCard_Button.png"));
		}
		else
		{
			m_PageName->SetStateTexture(Button_State::Normal, "HeroCard", TEXT("button/HeroCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::MouseOn, "HeroCard", TEXT("button/HeroCard_Button.png"));
			m_PageName->SetStateTexture(Button_State::Click, "HeroCard", TEXT("button/HeroCard_Button.png"));

			//m_PageNext->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
			//m_PageNext->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));
		}

		m_Deck2->SelectSetting();
		m_Deck->SelectOtherSetting();
	
	}

}

void CSelectHUDWidget::ExitClick()
{
	
}

void CSelectHUDWidget::FirstHeroClick()
{
	m_Deck->SetRendernormal(false);
	m_Deckindex = 1;
	m_Deck->SelectSetting();
	m_Deck2->SelectOtherSetting();
	StartClick();

	SetDecktitle(m_Deck);

	m_firstHero->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_firstHero->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_firstHero->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_secondHero->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
	m_secondHero->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
	m_secondHero->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);


}

void CSelectHUDWidget::SecondHeroClick()
{
	m_Deck2->SetRendernormal(false);
	m_Deckindex = 2;
	m_Deck->SelectOtherSetting();
	m_Deck2->SelectSetting();
	StartClick();

	SetDecktitle(m_Deck2);
	m_secondHero->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_secondHero->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_secondHero->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_firstHero->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
	m_firstHero->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
	m_firstHero->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);

}

void CSelectHUDWidget::Next()
{	
	if (m_HeroCardIN->GetNumber() == 3 && m_NormalCardIN->GetNumber() == 7)
	{
		// 다음 장면으로 넘어간다.

		m_Deck->ReadyForBattle1();
		m_Deck2->ReadyForBattle2();

		CSceneManager::GetInst()->CreateNextScene();

		CSceneManager::GetInst()->SetSceneMode<CGameMap>(false);
	}
	
}

void CSelectHUDWidget::SetDeck(CDeck* deck)
{

	m_Deck = deck;


	m_HeroText = CreateWidget<CText>("HeroText");
	SetDecktitle(m_Deck);
	m_HeroText->SetPos(170.f, 630.f);
	m_HeroText->SetSize(200.f, 50.f);
	m_HeroText->SetFontSize(40.f);
	m_HeroText->SetShadowEnable(false);
	m_HeroText->SetShadowColor(1.f, 1.f, 0.f);
	m_HeroText->SetShadowAlphaEnable(true);
	m_HeroText->SetShadowOpacity(0.5f);
	m_HeroText->SetAlignH(TEXT_ALIGN_H::Center);
	m_HeroText->SetAlignV(TEXT_ALIGN_V::Bottom);
	
}

void CSelectHUDWidget::SetDeck2(CDeck* deck)
{
	m_Deck2 = deck;
	deck->SelectOtherSetting();

}

void CSelectHUDWidget::SetDecktitle(CDeck* deck)
{
	int tempforswitch = deck->GetHeroIndex();
	switch (tempforswitch)
	{
	case 1:
		m_HeroText->SetText(TEXT(""));
		break;
	case 2:
		m_HeroText->SetText(TEXT(""));
		break;
	case 3:
		m_HeroText->SetText(TEXT(""));
		break;
	default:
		m_HeroText->SetText(TEXT(""));
		break;
	}
}

void CSelectHUDWidget::MoveUp(float DeltaTime)
{
	

	m_PageName->AddPos(Vector2(0.f, 20.f * DeltaTime));
	m_PageNext->AddPos(Vector2(0.f, 20.f * DeltaTime));
}

void CSelectHUDWidget::MoveDown(float DeltaTime)
{
	m_PageName->AddPos(Vector2(0.f, -20.f * DeltaTime));

	m_PageNext->AddPos(Vector2(0.f, -20.f * DeltaTime));
}

void CSelectHUDWidget::RotationZ(float DeltaTime)
{

	m_PageName->AddPos(Vector2(-20.f * DeltaTime, 0.f));
	m_PageNext->AddPos(Vector2(-20.f * DeltaTime, 0.f));
}

void CSelectHUDWidget::RotationZInv(float DeltaTime)
{
	m_PageName->AddPos(Vector2(20.f * DeltaTime, 0.f));
	m_PageNext->AddPos(Vector2(20.f * DeltaTime, 0.f));
}

void CSelectHUDWidget::SetLookUp(bool b)
{
	

}
