#include "CardUseHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
#include "../Object/BuildingCard.h"
#include "Scene/SceneManager.h"
#include "../SceneMode/MainScene.h"
CCardUseHUDWidget::CCardUseHUDWidget() :
	m_Open(false),
	m_Close(false),
	m_OpenStartCheck(false),
	m_GameMapObj(nullptr),
	m_valuex(0.f),
	m_valuey(0.f),
	m_Nab(0),
	m_Chozo(0)

{
}

CCardUseHUDWidget::CCardUseHUDWidget(const CCardUseHUDWidget& widget)
{
}

CCardUseHUDWidget::~CCardUseHUDWidget()
{
}

bool CCardUseHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_DrawButton = CreateWidget<CButton>("Draw");
	m_DrawButton->SetPos(Center.x - 520.f, Center.y - Center.y * 2.f);

	m_DrawButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.4f, 1.4f, 1.4f, 1.f);
	m_DrawButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);

	m_DrawButton->SetSize(700.f / 7.f, 298.f / 7.f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "사용", TEXT("button/사용.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "사용1", TEXT("button/사용1.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "사용1", TEXT("button/사용1.png"));
	m_DrawButton->SetClickCallback<CCardUseHUDWidget>(this, &CCardUseHUDWidget::ClickUse);
	m_DrawButton->SetZOrder(5);
	//m_DrawButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_DrawButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_RefreshButton = CreateWidget<CButton>("Refresh");
	m_RefreshButton->SetPos(m_DrawButton->GetPos().x+ 536.f / 7.f, m_DrawButton->GetPos().y);
	m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.4f, 1.4f, 1.4f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);



	m_RefreshButton->SetSize(700.f / 7.f, 298.f / 7.f);
	m_RefreshButton->SetStateTexture(Button_State::Normal, "덮기", TEXT("button/덮기.png"));
	m_RefreshButton->SetStateTexture(Button_State::MouseOn, "덮기1", TEXT("button/덮기1.png"));
	m_RefreshButton->SetStateTexture(Button_State::Click, "덮기1", TEXT("button/덮기1.png"));
	m_RefreshButton->SetClickCallback<CCardUseHUDWidget>(this, &CCardUseHUDWidget::ClickBack);

	m_RefreshButton->SetZOrder(5);









	return true;
}

void CCardUseHUDWidget::Update(float DeltaTime)
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

void CCardUseHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CCardUseHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CCardUseHUDWidget* CCardUseHUDWidget::Clone()
{
	return new CCardUseHUDWidget(*this);
}

void CCardUseHUDWidget::OpenWidget(float x, float y,int i,int index)
{
	if (m_GameMapObj->Player1FocusCheck() == false)
		return;

	m_GameMapObj->CardClickSound();
	if (index == 0)
	{
		if (i == 1)
		{
			m_DrawButton->SetPos(x - 112.f, y);
			m_RefreshButton->SetPos(m_DrawButton->GetPos().x + 700.f / 7.f, m_DrawButton->GetPos().y);
			m_RefreshButton->SetSize(700.f / 1600.f, 298.f / 1600.f);
			m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 1.f);
			m_DrawButton->SetStateTexture(Button_State::Normal, "사용", TEXT("button/사용.png"));
			m_DrawButton->SetStateTexture(Button_State::MouseOn, "사용1", TEXT("button/사용1.png"));
			m_DrawButton->SetStateTexture(Button_State::Click, "사용1", TEXT("button/사용1.png"));
		}
		else if (i == 2)
		{
			m_DrawButton->SetPos(x - 72.f, y);
			m_RefreshButton->SetPos(0.f, -1200.f);
			m_RefreshButton->SetSize(0.f, 0.f);
			m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
			m_DrawButton->SetStateTexture(Button_State::Normal, "비장패사용", TEXT("button/비장패사용.png"));
			m_DrawButton->SetStateTexture(Button_State::MouseOn, "비장패사용1", TEXT("button/비장패사용1.png"));
			m_DrawButton->SetStateTexture(Button_State::Click, "비장패사용1", TEXT("button/비장패사용1.png"));

		}
	}
	else if (index == 1)
	{
		if (i == 1)
		{
			m_DrawButton->SetPos(x - 2000.f, y);
			m_DrawButton->SetSize(0.f, 0.f);
			m_DrawButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
			m_RefreshButton->SetPos(x-20.f, y);
			m_RefreshButton->SetSize(700.f / 1600.f, 298.f / 1600.f);
			m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 1.f);
			
		}
		else if (i == 2)
		{
			m_DrawButton->SetPos(0.f, -1200.f);
			m_DrawButton->SetSize(0.f, 0.f);
			m_DrawButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
			m_RefreshButton->SetPos(0.f, -1200.f);
			m_RefreshButton->SetSize(0.f, 0.f);
			m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
			

		}
	}


	m_DrawButton->SetColorTint(1.f, 1.f, 1.f, 1.f);

	m_valuex = x;
	m_valuey = y;
	m_GameMapObj->SetSelectUSEANDBACK(true);
	
	m_DrawButton->SetSize(700.f / 1600.f, 298.f / 1600.f);





	m_Open = true;
	m_Close = false;
	m_OpenStartCheck = true;

}

void CCardUseHUDWidget::CloseWidget()
{
	m_DrawButton->SetPos(0.f, -1200.f);
	m_RefreshButton->SetPos(m_DrawButton->GetPos().x + 536.f / 7.f, m_DrawButton->GetPos().y);
	m_DrawButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 0.f);;
	m_GameMapObj->SetSelectUSEANDBACK(false);

	m_Open = false;
	m_OpenStartCheck = false;
	m_Close = true;

}

void CCardUseHUDWidget::StartClick()
{
}

void CCardUseHUDWidget::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	float Ratio = m_DrawButton->GetSize().y / m_DrawButton->GetSize().x;
	Vector2 StartPoint = Vector2(m_valuex, m_valuey+110.f);
	StartPoint = StartPoint - m_DrawButton->GetPos();
	std::vector<CSharedPtr<CCard>> vecDaueg = m_GameMapObj->GetPlayer1DauegCard();

	if (StartPoint.y >= 0.f && m_OpenStartCheck)
	{
		m_DrawButton->AddSize(Vector2(StartPoint.y * (DeltaTime * 15.f ), Ratio* StartPoint.y*(DeltaTime * 15.f )));
		m_RefreshButton->AddSize(Vector2(StartPoint.y * (DeltaTime * 15.f ), Ratio * StartPoint.y * (DeltaTime * 15.f)));
		m_DrawButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_RefreshButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		
	}
	else
	{
		m_Open = false;
	}





}

void CCardUseHUDWidget::Close(float DeltaTime)
{

	
}

void CCardUseHUDWidget::ClickUse()
{
	
	m_GameMapObj->PlayerCardToUse();
	CloseWidget();
}

void CCardUseHUDWidget::ClickBack()
{
	
	m_GameMapObj->Player1CardToBack();
	CloseWidget();
}

