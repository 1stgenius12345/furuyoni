
#include "TutorialWidget.h"
#include "Device.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "../Object/StartMapObj.h"
#include "UI/Image.h"
#include "Render/RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Input.h"

CTutorialWidget::CTutorialWidget()
{

}

CTutorialWidget::CTutorialWidget(const CTutorialWidget& widget) :
	CWidgetWindow(widget)
{
}

CTutorialWidget::~CTutorialWidget()
{
}

bool CTutorialWidget::Init()
{
	CWidgetWindow::Init();






	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;




	m_MirrorMenuButton = CreateWidget<CButton>("BackArrow");

	m_MirrorMenuButton->SetPos(0.f, 0.f);
	m_MirrorMenuButton->SetSize(81.f/2.f, 130.f/2.f);
	m_MirrorMenuButton->SetStateTexture(Button_State::Normal, "BackArrow", TEXT("BackArrow.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::MouseOn, "BackArrow", TEXT("BackArrow.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::Click, "BackArrow", TEXT("BackArrow.png"));
	m_MirrorMenuButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_MirrorMenuButton->SetClickCallback<CTutorialWidget>(this, &CTutorialWidget::StartClick);
	m_MirrorMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");

	m_MirrorMenuButton->SetZOrder(5);




	m_StageMenuButton = CreateWidget<CButton>("FrontArrow");
	m_StageMenuButton->SetPos(1280.f- 81.f / 2.f, 0.f);
	m_StageMenuButton->SetSize(81.f/2.f, 130.f/2.f);
	m_StageMenuButton->SetStateTexture(Button_State::Normal, "FrontArrow", TEXT("FrontArrow.png"));
	m_StageMenuButton->SetStateTexture(Button_State::MouseOn, "FrontArrow", TEXT("FrontArrow.png"));
	m_StageMenuButton->SetStateTexture(Button_State::Click, "FrontArrow", TEXT("FrontArrow.png"));
	m_StageMenuButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_StageMenuButton->SetClickCallback<CTutorialWidget>(this, &CTutorialWidget::StageExitClick);
	m_StageMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");

	m_StageMenuButton->SetZOrder(5);











	return true;
}

void CTutorialWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);


}

void CTutorialWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTutorialWidget::Render()
{
	CWidgetWindow::Render();
}

CTutorialWidget* CTutorialWidget::Clone()
{
	return new CTutorialWidget(*this);
}

void CTutorialWidget::StartClick()
{
	m_TutorialObj->AddIndex(-1);
}

void CTutorialWidget::ExitClick()
{

}

void CTutorialWidget::StageExitClick()
{
	m_TutorialObj->AddIndex(1);

}

void CTutorialWidget::Nothing()
{
}

void CTutorialWidget::SetSelectButton()
{


}

