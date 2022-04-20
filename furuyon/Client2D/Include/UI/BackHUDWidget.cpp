
#include "BackHUDWidget.h"
#include "Device.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "../SceneMode/StartScene.h"
#include "UI/Image.h"
#include "Render/RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Input.h"
#include "../ClientManager.h"
CBackHUDWidget::CBackHUDWidget()
{
	m_hide = true;
}

CBackHUDWidget::CBackHUDWidget(const CBackHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CBackHUDWidget::~CBackHUDWidget()
{
	SAFE_RELEASE(m_first2Hero);
}

bool CBackHUDWidget::Init()
{
	CWidgetWindow::Init();
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_ProfileImage = CreateWidget<CImage>("AlphaBlack22");
	m_ProfileImage->SetTexture("AlphaBlack", TEXT("AlphaBlack.png"));
	m_ProfileImage->SetPos(0.f, 0.f);
	m_ProfileImage->SetSize(0.f, 0.f);
	m_ProfileImage->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_ProfileImage->SetZOrder(2);

	m_first2Hero = CreateWidget<CButton>("BackButton22");
	m_first2Hero->SetPos(Center.x - 201.5f, Center.y - 36.5f);
	m_first2Hero->SetSize(0.f, 0.f);
	m_first2Hero->SetStateTexture(Button_State::Normal, "BackButton", TEXT("BackButton.png"));
	m_first2Hero->SetStateTexture(Button_State::MouseOn, "BackButton", TEXT("BackButton.png"));
	m_first2Hero->SetStateTexture(Button_State::Click, "BackButton", TEXT("BackButton.png"));
	m_first2Hero->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_first2Hero->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_first2Hero->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_first2Hero->SetClickCallback<CBackHUDWidget>(this, &CBackHUDWidget::BackButton);
	m_first2Hero->SetZOrder(4);




	return true;
}

void CBackHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	


}

void CBackHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBackHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CBackHUDWidget* CBackHUDWidget::Clone()
{
	return new CBackHUDWidget(*this);
}

void CBackHUDWidget::BackButton()
{
	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->SetSceneMode<CStartScene>(false);
}

void CBackHUDWidget::Show(float Deltatime)
{




	if (m_hide)
	{
		if (m_ProfileImage != nullptr)
			m_ProfileImage->SetSize(1280.f, 720.f);
		if(m_first2Hero != nullptr)
			m_first2Hero->SetSize(403.f, 73.f);
		m_hide = false;
	}
	else
	{
		if (m_ProfileImage != nullptr)
			m_ProfileImage->SetSize(0.f, 0.f);
		if (m_first2Hero != nullptr)
			m_first2Hero->SetSize(0.f, 0.f);
		m_hide = true;
	}
}
