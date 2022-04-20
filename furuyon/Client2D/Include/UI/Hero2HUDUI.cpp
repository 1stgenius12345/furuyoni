#include "Hero2HUDUI.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
CHero2HUDUI::CHero2HUDUI() :
	m_Open(false),
	m_Close(true),
	m_OpenStartCheck(false),
	m_OpenEnd(false),
	m_CloseEnd(false)
{
}

CHero2HUDUI::CHero2HUDUI(const CHero2HUDUI& widget)
{
}

CHero2HUDUI::~CHero2HUDUI()
{
}

bool CHero2HUDUI::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_HeroDeckButton = CreateWidget<CButton>("Hero2Deck");
	m_HeroDeckButton->SetPos(1280.f- 70.f * 1280.f / 1606.f, 450.f);
	m_HeroDeckButton->SetSize(56.f * 1280.f / 1606.f, 308.f * 720.f / 903.f);
	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
	m_HeroDeckButton->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	m_HeroDeckButton->SetClickCallback<CHero2HUDUI>(this, &CHero2HUDUI::ClickForward);



	/*m_HeroDeckBack = CreateWidget<CImage>("HeroBackDeck");
	m_HeroDeckBack->SetTexture("HeroDeckBack", TEXT("HeroDeckBack.png"));
	m_HeroDeckBack->SetPos(-621.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f);
	m_HeroDeckBack->SetSize(600.f * 1280.f / 1606.f, 308.f * 720.f / 903.f);*/



	return true;
}

void CHero2HUDUI::Update(float DeltaTime)
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

void CHero2HUDUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CHero2HUDUI::Render()
{
	CWidgetWindow::Render();
}

CHero2HUDUI* CHero2HUDUI::Clone()
{
	return new CHero2HUDUI(*this);
}

void CHero2HUDUI::OpenWidget()
{

	m_Open = true;
	m_Close = false;
	m_OpenEnd = true;
	m_OpenStartCheck = true;
}

void CHero2HUDUI::CloseWidget()
{
	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer2Backvector();

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

void CHero2HUDUI::StartClick()
{
}

void CHero2HUDUI::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer2Backvector();
	size_t vecSize = vecPlayer1Deck.size();
	CSharedPtr<CSpriteComponent> spriteBackGround = m_GameMapObj->GetPlayer2BackGround();

	Vector2 StartPoint = Vector2((1280.f - 70.f * 1280.f / 1606.f)- (584.f * 1280.f / 1606.f), 450.f);
	StartPoint = StartPoint - m_HeroDeckButton->GetPos();

	if (StartPoint.x <= 0.002f)
	{
		m_HeroDeckButton->AddPos(StartPoint * Vector2(DeltaTime * 15.f, 0)+Vector2(DeltaTime*15.f,0.f));
		//	m_HeroDeckBack->AddPos(StartPoint * Vector2(DeltaTime * 10.f, 0));
		Vector3 vecTemp = Vector3((StartPoint * Vector2(DeltaTime * 15.f, 0)).x + Vector2(DeltaTime * 15.f, 0.f).x, 0.f, 0.f);
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
		std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer2Backvector();

		size_t vecsize = vecPlayer1Deck.size();

		for (int i = 0; i < vecsize; ++i)
		{
			vecPlayer1Deck[i]->SetMove(true);
			vecPlayer1Deck[i]->SetLookable(true);
		}

		m_OpenStartCheck = false;
		if (m_OpenEnd)
		{

			m_GameMapObj->HeroDeckSorting();
			m_OpenEnd = false;
		}

	}




	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "Hero2Deck_Close", TEXT("Hero2Deck_Close.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "Hero2Deck_Close", TEXT("Hero2Deck_Close.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "Hero2Deck_Close", TEXT("Hero2Deck_Close.png"));


}

void CHero2HUDUI::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	std::vector<CSharedPtr<CCard>> vecPlayer1Deck = m_GameMapObj->GetPlayer2Backvector();
	CSharedPtr<CSpriteComponent> spriteBackGround = m_GameMapObj->GetPlayer2BackGround();
	size_t vecSize = vecPlayer1Deck.size();

	Vector2 StartPoint = Vector2(1280.f - 70.f * 1280.f / 1606.f, 450.f);
	StartPoint = StartPoint - m_HeroDeckButton->GetPos();

	if (StartPoint.x >= 0.002f)
	{
		m_HeroDeckButton->AddPos(StartPoint * Vector2(DeltaTime * 15.f, 0) + Vector2(DeltaTime * 15.f, 0.f));
		//	m_HeroDeckBack->AddPos(StartPoint * Vector2(DeltaTime * 10.f, 0));
		Vector3 vecTemp = Vector3((StartPoint * Vector2(DeltaTime * 15.f, 0)).x + Vector2(DeltaTime * 15.f, 0.f).x, 0.f, 0.f);
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
			m_GameMapObj->HeroDeckSorting();
			m_CloseEnd = false;
		}
	}
	m_HeroDeckButton->SetStateTexture(Button_State::Normal, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::MouseOn, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
	m_HeroDeckButton->SetStateTexture(Button_State::Click, "Hero2Deck_Open", TEXT("Hero2Deck_Open.png"));
}

void CHero2HUDUI::ClickForward()
{
	if (m_Open)
	{
		CloseWidget();
	}
	else
	{
		OpenWidget();
	}

}

void CHero2HUDUI::ClickBackward()
{

}

void CHero2HUDUI::ClickOra()
{

}

void CHero2HUDUI::ClickMana()
{

}
