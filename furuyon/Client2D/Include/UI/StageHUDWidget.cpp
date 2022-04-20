
#include "StageHUDWidget.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/MainScene.h"
#include "../SceneMode/GodSelectScene.h"
#include "../SceneMode/LoadingScene.h"
#include "../SceneMode/StageScene.h"
#include "Scene/SceneManager.h"
#include "../Object/StartMapObj.h"
#include "UI/Image.h"
#include "Render/RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Input.h"

CStageHUDWidget::CStageHUDWidget()
{
	
}

CStageHUDWidget::CStageHUDWidget(const CStageHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CStageHUDWidget::~CStageHUDWidget()
{
}

bool CStageHUDWidget::Init()
{
	CWidgetWindow::Init();






	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;




	m_MirrorMenuButton = CreateWidget<CButton>("StartButton");

	m_MirrorMenuButton->SetPos(100.f,500.f);
	m_MirrorMenuButton->SetSize(200.f,100.f);
	m_MirrorMenuButton->SetStateTexture(Button_State::Normal, "stage1", TEXT("stage1.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::MouseOn, "stage1", TEXT("stage1.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::Click, "stage1", TEXT("stage1.png"));
	m_MirrorMenuButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_MirrorMenuButton->SetClickCallback<CStageHUDWidget>(this, &CStageHUDWidget::StartClick);
	m_MirrorMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");

	m_MirrorMenuButton->SetZOrder(5);
	m_vecMenuButton.push_back(m_MirrorMenuButton);



	m_StageMenuButton = CreateWidget<CButton>("m_StageMenuButton");
	m_StageMenuButton->SetPos(300.f,500.f);
	m_StageMenuButton->SetSize(200.f, 100.f);
	m_StageMenuButton->SetStateTexture(Button_State::Normal, "stage1", TEXT("stage1.png"));
	m_StageMenuButton->SetStateTexture(Button_State::MouseOn, "stage1", TEXT("stage1.png"));
	m_StageMenuButton->SetStateTexture(Button_State::Click, "stage1", TEXT("stage1.png"));
	m_StageMenuButton->SetStateTint(Button_State::Normal, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::MouseOn, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::Click, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetClickCallback<CStageHUDWidget>(this, &CStageHUDWidget::StageExitClick);
	m_StageMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");

	m_StageMenuButton->SetZOrder(5);
	m_vecMenuButton.push_back(m_StageMenuButton);
	









	return true;
}

void CStageHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	

}

void CStageHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStageHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CStageHUDWidget* CStageHUDWidget::Clone()
{
	return new CStageHUDWidget(*this);
}

void CStageHUDWidget::StartClick()
{
	// 다음 장면으로 넘어간다.

}

void CStageHUDWidget::ExitClick()
{
	
}

void CStageHUDWidget::StageExitClick()
{

}

void CStageHUDWidget::Nothing()
{
}

void CStageHUDWidget::SetSelectButton()
{


}
