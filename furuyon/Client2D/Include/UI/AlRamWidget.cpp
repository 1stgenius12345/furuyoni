
#include "AlRamWidget.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/MainScene.h"
#include "../SceneMode/GodSelectScene.h"
#include "../SceneMode/LoadingScene.h"
#include "Scene/SceneManager.h"
#include "../Object/StartMapObj.h"
#include "UI/Image.h"
#include "Render/RenderManager.h"
#include "Input.h"
CAlRamWidget::CAlRamWidget():
	m_floattime(0.f)
{
}

CAlRamWidget::CAlRamWidget(const CAlRamWidget& widget) :
	CWidgetWindow(widget)
{
}

CAlRamWidget::~CAlRamWidget()
{
}

bool CAlRamWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	


	m_ProfileImage = CreateWidget<CImage>("AlphaBlack");
	m_ProfileImage->SetTexture("AlphaBlack", TEXT("AlphaBlack.png"));
	m_ProfileImage->SetPos(0.f, 0.f);
	m_ProfileImage->SetSize(1280.f, 720.f);
	m_ProfileImage->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_ProfileImage->SetZOrder(2);

	m_TitleImage = CreateWidget<CImage>("m_TitleImage");
	m_TitleImage->SetTexture("½ÖÀå¿ä¶õ", TEXT("½ÖÀå¿ä¶õ.png"));
	m_TitleImage->SetPos(0.f, 0.f);
	m_TitleImage->SetSize(1280.f, 720.f);
	m_TitleImage->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_TitleImage->SetZOrder(3);








	return true;
}

void CAlRamWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if(m_floattime < 100.f)
		m_floattime += DeltaTime;

	if (m_floattime > 0.3f)
	{
		bool moustput = CInput::GetInst()->GetMousePut();
		if (moustput)
		{
			m_ProfileImage->SetSize(0.f, 0.f);
			m_TitleImage->SetSize(0.f, 0.f);
		}
	}
	
}

void CAlRamWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CAlRamWidget::Render()
{
	CWidgetWindow::Render();
}

CAlRamWidget* CAlRamWidget::Clone()
{
	return new CAlRamWidget(*this);
}

void CAlRamWidget::StartClick()
{
	
}

void CAlRamWidget::ExitClick()
{
	
}
