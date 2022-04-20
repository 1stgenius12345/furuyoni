#include "PhaseHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
#include "../Object/BuildingCard.h"
CPhaseHUDWidget::CPhaseHUDWidget() :
	m_Open(false),
	m_Close(false),
	m_OpenStartCheck(false),
	m_valuex(0),
	m_valuey(0),
	m_Nab(0),
	m_Chozo(0),
	m_ReturnTime(0.f),
	m_PhaseType(PhaseType::None)
{
}

CPhaseHUDWidget::CPhaseHUDWidget(const CPhaseHUDWidget& widget)
{
}

CPhaseHUDWidget::~CPhaseHUDWidget()
{
}

bool CPhaseHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_DrawButton = CreateWidget<CButton>("Phase");
	m_DrawButton->SetPos(1280.f-283.f-15.f,720.f-50.f );

	m_DrawButton->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_DrawButton->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);

	m_DrawButton->SetSize(283.f/ 1.3f, 55.f/ 1.3f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "멀리건", TEXT("button/멀리건.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "멀리건", TEXT("button/멀리건.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "멀리건", TEXT("button/멀리건.png"));
	m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::DrawButton);
	m_DrawButton->SetZOrder(5);
	//m_DrawButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_DrawButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");


	//m_RefreshButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_RefreshButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");



	return true;
}

void CPhaseHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_ReturnTime >= 1.5f)
	{
		OpenWidget();
		
	}



	if (m_Open)
	{
		Open(DeltaTime);
		m_ReturnTime = 0;
	}
	else if (m_Close)
	{
		Close(DeltaTime);
		m_ReturnTime += DeltaTime;
	}
}

void CPhaseHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPhaseHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CPhaseHUDWidget* CPhaseHUDWidget::Clone()
{
	return new CPhaseHUDWidget(*this);
}

void CPhaseHUDWidget::OpenWidget()
{
	m_Open = true;
	m_Close = false;
	m_OpenStartCheck = true;
	// 화면에 알파블랙 설치용도
	m_GameMapObj->SetSelectTiming(false);
	if (m_PhaseType == PhaseType::Player1Exit)
		m_GameMapObj->SetPlayer1End(true);
	else if (m_PhaseType == PhaseType::Player1Main)
	{
		m_GameMapObj->SetPlayer1Main(true);
		m_DrawButton->SetStateTexture(Button_State::Click, "턴 종료하기", TEXT("button/턴 종료하기.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "턴 종료하기", TEXT("button/턴 종료하기.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::Player1TurnEnd);
	}
	else if (m_PhaseType == PhaseType::Player2Main)
	{
		m_GameMapObj->SetPlayer2Main(true);
	}
	else if (m_PhaseType == PhaseType::Player2Exit)
	{
		m_GameMapObj->SetPlayer2End(true);
	}
	else if (m_PhaseType == PhaseType::Player1Gaeshi)
	{
		m_GameMapObj->SetPlayer1Gaesi(true);
	}
	else if (m_PhaseType == PhaseType::Player2Gasehi)
	{
		m_GameMapObj->SetPlayer2Gaesi(true);
	}
}

void CPhaseHUDWidget::CloseWidget()
{
	// 화면에 알파블랙 설치용도
	m_GameMapObj->SetSelectTiming(true);
	m_Open = false;
	m_OpenStartCheck = false;
	m_Close = true;

}

void CPhaseHUDWidget::StartClick()
{
}

void CPhaseHUDWidget::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	float ratio = m_DrawButton->GetSize().y / m_DrawButton->GetSize().x;
	Vector2 StartPoint = Vector2(1280.f - 283.f - 15.f, 720.f - 50.f);
	StartPoint = StartPoint - m_DrawButton->GetPos();

	if (StartPoint.x >= 0.f && m_OpenStartCheck)
	{
		m_DrawButton->AddPos( Vector2(StartPoint.x * DeltaTime * 10.f, StartPoint.x * DeltaTime * 5.f));
		m_DrawButton->AddSize( Vector2(StartPoint.x * DeltaTime * -3.5f, StartPoint.x * DeltaTime * -3.5f * ratio));

	}
	else
		m_OpenStartCheck = false;




}

void CPhaseHUDWidget::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	float ratio = m_DrawButton->GetSize().y / m_DrawButton->GetSize().x;
	Vector2 StartPoint = Vector2(Center.x-230.f , Center.y-110.f );
	StartPoint = StartPoint - m_DrawButton->GetPos();

	if (StartPoint.x <= 0.f)
	{
		m_DrawButton->AddPos( Vector2(StartPoint.x * DeltaTime * 10.f, StartPoint.x * DeltaTime * 5.f));
		m_DrawButton->AddSize(Vector2(StartPoint.x * DeltaTime * -3.5f, StartPoint.x * DeltaTime * -3.5f * ratio));

	}
}

void CPhaseHUDWidget::CreatePhaseUI(PhaseType type)
{
	m_PhaseType = type;
	switch (type)
	{
	case PhaseType::None:
		break;
	case PhaseType::Player1Gaeshi:
		m_DrawButton->SetStateTexture(Button_State::Normal, "플레이어 개시", TEXT("button/플레이어 개시.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "플레이어 개시", TEXT("button/플레이어 개시.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "플레이어 개시", TEXT("button/플레이어 개시.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::DrawButton);
		
		CloseWidget();
		break;
	case PhaseType::Player1Main:
		m_DrawButton->SetStateTexture(Button_State::Normal, "플레이어 메인", TEXT("button/플레이어 메인.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "플레이어 메인", TEXT("button/플레이어 메인.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "플레이어 메인", TEXT("button/플레이어 메인.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::Player1TurnEnd);
	
		break;
	case PhaseType::Player1Exit:
		m_DrawButton->SetStateTexture(Button_State::Normal, "플레이어 종료", TEXT("button/플레이어 종료.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "플레이어 종료", TEXT("button/플레이어 종료.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "플레이어 종료", TEXT("button/플레이어 종료.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::DrawButton);
		break;
	case PhaseType::Player2Gasehi:
		m_DrawButton->SetStateTexture(Button_State::Normal, "AI개시", TEXT("button/AI개시.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "AI개시", TEXT("button/AI개시.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "AI개시", TEXT("button/AI개시.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::DrawButton);
		break;
	case PhaseType::Player2Main:
		m_DrawButton->SetStateTexture(Button_State::Normal, "AI메인", TEXT("button/AI메인.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "AI메인", TEXT("button/AI메인.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "AI메인", TEXT("button/AI메인.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::Player1TurnEnd);
		break;
	case PhaseType::Player2Exit:
		m_DrawButton->SetStateTexture(Button_State::Normal, "AI종료", TEXT("button/AI종료.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "AI종료", TEXT("button/AI종료.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "AI종료", TEXT("button/AI종료.png"));
		m_DrawButton->SetClickCallback<CPhaseHUDWidget>(this, &CPhaseHUDWidget::DrawButton);
		break;
	case PhaseType::End:
		break;
	default:
		break;
	}
	CloseWidget();
}


void CPhaseHUDWidget::DrawButton()
{
	
	


}

void CPhaseHUDWidget::RefreshButton()
{
	m_GameMapObj->RefreshDeck();

	CloseWidget();
}

void CPhaseHUDWidget::Player1TurnEnd()
{	
	if (m_GameMapObj->GetSelectTiming() == false)
	{
		if (m_PhaseType == PhaseType::Player1Main)
		{
			m_GameMapObj->SetPlayer1MainEnd(true);
			m_GameMapObj->SetTestDelayTime(1.9f);
			m_GameMapObj->TurnEndSound();
		}
			
		
	}
	
}
