#include "HeroHUDUI.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
CHeroHUDUI::CHeroHUDUI() :
	m_Open(false),
	m_Close(true),
	m_OpenStartCheck(false),
	m_OpenEnd(false),
	m_CloseEnd(false)
{
}

CHeroHUDUI::CHeroHUDUI(const CHeroHUDUI& widget)
{
}

CHeroHUDUI::~CHeroHUDUI()
{
}

bool CHeroHUDUI::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_HeroDeckButton = CreateWidget<CButton>("HeroDeck");
	m_HeroDeckButton->SetPos(-21.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f);
	m_HeroDeckButton->SetSize(56.f * 1280.f / 1606.f, 308.f * 720.f / 903.f);
	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
	m_HeroDeckButton->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetClickCallback<CHeroHUDUI>(this, &CHeroHUDUI::ClickForward);



	/*m_HeroDeckBack = CreateWidget<CImage>("HeroBackDeck");
	m_HeroDeckBack->SetTexture("HeroDeckBack", TEXT("HeroDeckBack.png"));
	m_HeroDeckBack->SetPos(-621.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f);
	m_HeroDeckBack->SetSize(600.f * 1280.f / 1606.f, 308.f * 720.f / 903.f);*/



	return true;
}

void CHeroHUDUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_Open)
	{
		Open(DeltaTime);
	}
	else if (m_Close)
	{
		Close(DeltaTime);
	}
}

void CHeroHUDUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CHeroHUDUI::Render()
{
	CWidgetWindow::Render();
}

CHeroHUDUI* CHeroHUDUI::Clone()
{
	return new CHeroHUDUI(*this);
}

void CHeroHUDUI::OpenWidget()
{
	
	m_Open = true;
	m_Close = false;
	m_OpenEnd = true;
	m_OpenStartCheck = true;
}

void CHeroHUDUI::CloseWidget()
{
	
	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer1Backvector();

	size_t vecsize = vecPlayer1Deck.size();

	for (int i = 0; i < vecsize; ++i)
	{
		vecPlayer1Deck[i]->SetMove(false);
		vecPlayer1Deck[i]->SetLookable(false);
	}
	m_Open = false;
	m_OpenStartCheck = false;
	m_CloseEnd = true;
	m_Close = true;
}

void CHeroHUDUI::StartClick()
{
}

void CHeroHUDUI::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer1Backvector();
	size_t vecSize = vecPlayer1Deck.size();
	CSharedPtr<CSpriteComponent> spriteBackGround = m_GameMapObj->GetPlayer1BackGround();
	
	Vector2 StartPoint = Vector2(563.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f);
	StartPoint = StartPoint - m_HeroDeckButton->GetPos();

	if (StartPoint.x >= 0.002f)
	{
		
		m_HeroDeckButton->AddPos(StartPoint * Vector2(DeltaTime * 15.f, 0)+ Vector2(DeltaTime * 15.f, 0));
	//	m_HeroDeckBack->AddPos(StartPoint * Vector2(DeltaTime * 10.f, 0));
		Vector3 vecTemp = Vector3((StartPoint * Vector2(DeltaTime * 15.f, 0)).x+ Vector2(DeltaTime * 15.f, 0).x, 0.f, 0.f);
		spriteBackGround->AddRelativePos(vecTemp);
		for (int i = 0; i < vecSize; ++i)
		{
			vecPlayer1Deck[i]->AddRelativePos(vecTemp);
			vecPlayer1Deck[i]->SetStartHandPos(vecPlayer1Deck[i]->GetRelativePos());
			vecPlayer1Deck[i]->SetLookable(false);
			//vecPlayer1Deck[i]->SetLookable(true);
		}

	}
	else
	{
		std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer1Hero();

		size_t vecsize = vecPlayer1Deck.size();

		
	
		m_OpenStartCheck = false;
		if (m_OpenEnd)
		{
			m_HeroDeckButton->SetClickCallback<CHeroHUDUI>(this, &CHeroHUDUI::ClickForward);
			m_GameMapObj->HeroDeckSorting();
		//	m_GameMapObj->HeroDeckSorting();
			m_OpenEnd = false;
		}

	}
		

	

	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "HeroDeck_Close", TEXT("HeroDeck_Close.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "HeroDeck_Close", TEXT("HeroDeck_Close.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "HeroDeck_Close", TEXT("HeroDeck_Close.png"));


}

void CHeroHUDUI::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer1Backvector(); 
	CSharedPtr<CSpriteComponent> spriteBackGround = m_GameMapObj->GetPlayer1BackGround();
	size_t vecSize = vecPlayer1Deck.size();

	Vector2 StartPoint = Vector2(-21.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f);
	StartPoint = StartPoint - m_HeroDeckButton->GetPos();

	if (StartPoint.x <= 0.0001f)
	{
	
		m_HeroDeckButton->AddPos(StartPoint * Vector2(DeltaTime * 15.f, 0)+ Vector2(DeltaTime * 15.f, 0));
	//	m_HeroDeckBack->AddPos(StartPoint * Vector2(DeltaTime * 10.f, 0));
		Vector3 vecTemp = Vector3((StartPoint * Vector2(DeltaTime * 15.f, 0)).x+ Vector2(DeltaTime * 15.f, 0).x, 0.f, 0.f);
		spriteBackGround->AddRelativePos(vecTemp);
		for (int i = 0; i < vecSize; ++i)
		{
			vecPlayer1Deck[i]->AddRelativePos(vecTemp);
			vecPlayer1Deck[i]->SetStartHandPos(vecPlayer1Deck[i]->GetRelativePos());
		}
	}
	else
	{
		
		if (m_CloseEnd)
		{
			m_HeroDeckButton->SetClickCallback<CHeroHUDUI>(this, &CHeroHUDUI::ClickForward);
			m_GameMapObj->HeroDeckSorting();
			m_CloseEnd = false;
		}
	}
	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "HeroDeck_Open", TEXT("HeroDeck_Open.png"));
}

void CHeroHUDUI::ClickForward()
{
	if (m_Open)
	{

		m_GameMapObj->CardUseCloseWidget();
		CloseWidget();
	}
	else
	{
		m_GameMapObj->CardUseCloseWidget();
		OpenWidget();
	}
	
}

void CHeroHUDUI::ClickBackward()
{

}

void CHeroHUDUI::ClickOra()
{
	
}

void CHeroHUDUI::ClickMana()
{

}
