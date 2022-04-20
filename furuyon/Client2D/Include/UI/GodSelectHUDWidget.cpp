#include "GodSelectHUDWidget.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/GameMap.h"
#include "Scene/SceneManager.h"
#include "UI/Text.h"
#include "UI/Image.h"
#include "UI/NumberWidget.h"
#include "Input.h"
#include "Timer.h"
#include "../SceneMode/MainScene.h"
#include "Resource/ResourceManager.h"
#include "../Object/GodSelectObj.h"
CGodSelectHUDWidget::CGodSelectHUDWidget() :
	m_FirstDeckIndex(0),
	m_SecondDeckIndex(0),
	m_Deckindex(0)
{
}

CGodSelectHUDWidget::CGodSelectHUDWidget(const CGodSelectHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CGodSelectHUDWidget::~CGodSelectHUDWidget()
{
}

bool CGodSelectHUDWidget::Init()
{

	CWidgetWindow::Init();

	m_Deckindex = 1;

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	CSharedPtr<CButton> firstHero = CreateWidget<CButton>("firstHero");
	firstHero->SetPos(50.f, 648.f);
	firstHero->SetSize(341.f / 5.3f, 387.f / 5.3f);
	firstHero->SetStateTexture(Button_State::Normal, "Yurina_Button", TEXT("Yurina_Button.png"));
	firstHero->SetStateTexture(Button_State::MouseOn, "Yurina_Button", TEXT("Yurina_Button.png"));
	firstHero->SetStateTexture(Button_State::Click, "Yurina_Button", TEXT("Yurina_Button.png"));
	firstHero->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	firstHero->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	firstHero->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	firstHero->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::FirstHeroClick);
	firstHero->SetInteractionSound(Button_Sound_State::Click, "HeroSelectButoon");
	m_vec_HeroButton.push_back(firstHero);
	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");
	CSharedPtr<CButton>secondHero = CreateWidget<CButton>("secondHero");
	secondHero->SetPos(115.f, 648.f);
	secondHero->SetSize(341.f / 5.3f, 387.f / 5.3f);
	secondHero->SetStateTexture(Button_State::Normal, "Saine_Button", TEXT("Saine_Button.png"));
	secondHero->SetStateTexture(Button_State::MouseOn, "Saine_Button", TEXT("Saine_Button.png"));
	secondHero->SetStateTexture(Button_State::Click, "Saine_Button", TEXT("Saine_Button.png"));
	secondHero->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
	secondHero->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
	secondHero->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	secondHero->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::SecondHeroClick);
	secondHero->SetInteractionSound(Button_Sound_State::Click, "HeroSelectButoon");
	m_vec_HeroButton.push_back(secondHero);
	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");
	CSharedPtr<CButton> thirdHero = CreateWidget<CButton>("thirdHero");
	thirdHero->SetPos(50.f + m_vec_HeroButton.size() * 65.f, 648.f);
	thirdHero->SetSize(341.f / 5.3f, 387.f / 5.3f);
	thirdHero->SetStateTexture(Button_State::Normal, "tokoyo", TEXT("tokoyo.png"));
	thirdHero->SetStateTexture(Button_State::MouseOn, "tokoyo", TEXT("tokoyo.png"));
	thirdHero->SetStateTexture(Button_State::Click, "tokoyo", TEXT("tokoyo.png"));
	thirdHero->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
	thirdHero->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
	thirdHero->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	thirdHero->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::tokoyoHeroClick);
	thirdHero->SetInteractionSound(Button_Sound_State::Click, "HeroSelectButoon");
	m_vec_HeroButton.push_back(thirdHero);
	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_HeroSelect = CreateWidget<CButton>("m_HeroSelect");
	m_HeroSelect->SetPos(640.f, 20.f);
	m_HeroSelect->SetSize(283.f, 55.f);
	m_HeroSelect->SetStateTexture(Button_State::Normal, "선택", TEXT("선택.png"));
	m_HeroSelect->SetStateTexture(Button_State::MouseOn, "선택", TEXT("선택.png"));
	m_HeroSelect->SetStateTexture(Button_State::Click, "선택", TEXT("선택.png"));
	m_HeroSelect->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_HeroSelect->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_HeroSelect->SetStateTint(Button_State::Click, 0.8f, 0.8f, 0.8f, 0.8f);
	m_HeroSelect->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::Select);
	m_HeroSelect->SetZOrder(3);
	m_HeroSelect->SetInteractionSound(Button_Sound_State::Click, "Select");
	// 
	// 
	// 
	// 일반카드
	m_PageName = CreateWidget<CButton>("NormalCard");
	m_PageName->SetPos(800.f, 418.f);
	m_PageName->SetSize(132.f/1.8f, 359.f/1.8f);
	m_PageName->SetStateTexture(Button_State::Normal, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTexture(Button_State::MouseOn, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTexture(Button_State::Click, "NormalCard", TEXT("button/NormalCard_Button.png"));
	m_PageName->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_PageName->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_PageName->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_PageName->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::StartClick);
	m_PageName->SetInteractionSound(Button_Sound_State::Click, "NormalHeroChange");


	m_ImageNormal = CreateWidget<CImage>("NormalInfo");

	m_ImageNormal->SetTexture("NormalInfo", TEXT("card/megami/0.png"));
	m_ImageNormal->SetPos(1264.f * 1280.f / 1603.f -100.f-30.f , 58.f * 720.f / 905.f + 40.f);
	m_ImageNormal->SetSize(685.f/3.5f, 1344.f / 3.5f);



	m_ImageHero = CreateWidget<CImage>("HeroInfo");
	m_ImageHero->SetTexture("HeroInfo", TEXT("card/megami/0.png"));
	m_ImageHero->SetPos(1264.f * 1280.f / 1603.f + 100.f - 30.f, 58.f * 720.f / 905.f + 40.f);
	m_ImageHero->SetSize(685.f / 3.5f, 1344.f / 3.5f);




	


	//m_SelectHero = CreateWidget<CImage>("m_SelectHero");
	//m_SelectHero->SetTexture("card/megami/1.png", TEXT("card/megami/1.png"));
	//m_SelectHero->SetPos(100.f, 200.f);
	//m_SelectHero->SetSize(685.f / 3.5f, 1344.f / 3.5f);

	

	//Button->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//Button->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	//  준비 완료
	m_Ready = CreateWidget<CButton>("ReadyButton");
	m_Ready->SetPos(Center.x + 310.f, Center.y - 370.f);
	m_Ready->SetSize(317.f / 1.3f, 105.f / 1.3f);
	m_Ready->SetStateTexture(Button_State::Normal, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTexture(Button_State::MouseOn, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTexture(Button_State::Click, "ReadyButton", TEXT("준비완료2.png"));
	m_Ready->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetStateTint(Button_State::MouseOn, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ready->SetClickCallback<CGodSelectHUDWidget>(this, &CGodSelectHUDWidget::Next);

	




	

	return true;
}

void CGodSelectHUDWidget::Update(float DeltaTime)
{
	if (m_FirstDeckIndex!= 0 && m_SecondDeckIndex != 0)
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

void CGodSelectHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CGodSelectHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CGodSelectHUDWidget* CGodSelectHUDWidget::Clone()
{
	return new CGodSelectHUDWidget(*this);
}

void CGodSelectHUDWidget::StartClick()
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

	m_Deck->SelectSelectSetting();


	

}

void CGodSelectHUDWidget::ExitClick()
{

}

void CGodSelectHUDWidget::FirstHeroClick()
{
	m_HeroText->SetText(TEXT("유리나"));
	m_Deckindex = 1;
	m_Deck->SetTexByHeroIndex(1);
	m_SelectCard->SetMegami3(m_Deckindex);
	SetAllGrayButton(0);
}

void CGodSelectHUDWidget::SecondHeroClick()
{
	m_HeroText->SetText(TEXT("사이네"));
	m_Deckindex = 3;
	m_Deck->SetTexByHeroIndex(3);
	m_SelectCard->SetMegami3(m_Deckindex);
	SetAllGrayButton(1);
}

void CGodSelectHUDWidget::tokoyoHeroClick()
{
	m_HeroText->SetText(TEXT("토코요"));
	m_Deckindex = 8;
	m_Deck->SetTexByHeroIndex(8);
	m_SelectCard->SetMegami3(m_Deckindex);
	SetAllGrayButton(2);
}

void CGodSelectHUDWidget::Next()
{
	if (m_FirstDeckIndex == 0 || m_SecondDeckIndex == 0)
		return;

	CClientManager::GetInst()->Setfirst(m_FirstDeckIndex);
	CClientManager::GetInst()->Setsecond(m_SecondDeckIndex);

		CSceneManager::GetInst()->CreateNextScene();

		CSceneManager::GetInst()->SetSceneMode<CMainScene>(false);
	

}

void CGodSelectHUDWidget::Select()
{	
	if (m_FirstDeckIndex == m_Deckindex || m_SecondDeckIndex == m_Deckindex)
		return;

	if (m_FirstDeckIndex == 0 && m_SecondDeckIndex == 0)
		m_FirstDeckIndex = m_Deckindex;
	else if (m_FirstDeckIndex != 0 && m_SecondDeckIndex == 0)
		m_SecondDeckIndex = m_Deckindex;
	else
	{
		m_FirstDeckIndex = m_SecondDeckIndex;
		m_SecondDeckIndex = m_Deckindex;
	}
	if (m_Deckindex == 1)
	{
		CResourceManager::GetInst()->SoundPlay("yurinaselect");
	}
	else if (m_Deckindex == 3)
	{
		CResourceManager::GetInst()->SoundPlay("saineselect");
	}
	else if (m_Deckindex == 8)
	{
		CResourceManager::GetInst()->SoundPlay("tokoyoselect");
	}
	SetMegami();
	SetMegami2();
}

void CGodSelectHUDWidget::SetDeck(CDeck* deck)
{

	m_Deck = deck;

	m_Deck->SelectSelectSetting();
	m_Deck->SetTexByHeroIndex(8);
	m_Deck->SetTexByHeroIndex(3);
	m_Deck->SetTexByHeroIndex(1);
	m_HeroText = CreateWidget<CText>("HeroText");
	SetDecktitle(m_Deck);
	m_HeroText->SetPos(450.f, 20.f);
	m_HeroText->SetSize(200.f, 50.f);
	m_HeroText->SetFontSize(40.f);
	m_HeroText->SetShadowEnable(true);
	m_HeroText->SetShadowColor(0.f, 0.f, 0.f);
	m_HeroText->SetShadowAlphaEnable(true);
	m_HeroText->SetShadowOpacity(0.8f);
	m_HeroText->SetAlignH(TEXT_ALIGN_H::Center);
	m_HeroText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_HeroText->SetZOrder(3);
}


void CGodSelectHUDWidget::SetDecktitle(CDeck* deck)
{
	int tempforswitch = deck->GetHeroIndex();
	switch (tempforswitch)
	{
	case 1:
		m_HeroText->SetText(TEXT("유리나"));
		break;
	case 2:
		m_HeroText->SetText(TEXT(""));
		break;
	case 3:
		m_HeroText->SetText(TEXT("사이네"));
		break;
	case 8:
		m_HeroText->SetText(TEXT("토코요"));
		break;
	default:
		m_HeroText->SetText(TEXT(""));
		break;
	}
}


void CGodSelectHUDWidget::SetLookUp(bool b)
{


}

void CGodSelectHUDWidget::SetAllGrayButton(int index)
{
	for (int i = 0; i < m_vec_HeroButton.size(); ++i)
	{
		if (i == index)
		{
			m_vec_HeroButton[i]->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
			m_vec_HeroButton[i]->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
			m_vec_HeroButton[i]->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
			continue;
		}
		m_vec_HeroButton[i]->SetStateTint(Button_State::Normal, 0.6f, 0.6f, 0.6f, 0.6f);
		m_vec_HeroButton[i]->SetStateTint(Button_State::MouseOn, 0.8f, 0.8f, 0.8f, 0.8f);
		m_vec_HeroButton[i]->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	}
}

void CGodSelectHUDWidget::SetMegami()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_FirstDeckIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_FirstDeckIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_ImageNormal->SetTexture(std_str, tex);
}

void CGodSelectHUDWidget::SetMegami2()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_SecondDeckIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_SecondDeckIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_ImageHero->SetTexture(std_str, tex);
}
