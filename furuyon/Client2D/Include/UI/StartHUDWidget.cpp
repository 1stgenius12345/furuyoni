
#include "StartHUDWidget.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/MainScene.h"
#include "../SceneMode/GodSelectScene.h"
#include "../SceneMode/LoadingScene.h"
#include "../SceneMode/StageScene.h"
#include "../SceneMode/TutorialScene.h"
#include "Scene/SceneManager.h"
#include "../Object/StartMapObj.h"
#include "UI/Image.h"
#include "Render/RenderManager.h"
#include "Resource/ResourceManager.h"
#include "Input.h"
#include "../ClientManager.h"
CStartHUDWidget::CStartHUDWidget() :
	m_Button2(nullptr),
	m_MapObj(nullptr),
	m_SelectButton(nullptr),
	m_WhiteMaxState(false),
	m_WhiteTime(0.f),
	m_BlurCount(100.f),
	m_Stage2(false),
	m_StartstageWhiteDesolve(true),
	m_StartstageWhiteDesolveMax(false),
	m_ExitStageCount(0.f),
	m_ExitStage(false),
	m_Stage(false),
	m_titlesound(true)
{
	m_ButtonIndex = 0;
	m_ButtonAnimationRight = false;
	m_ButtonAnimationLeft = false;
	m_ButtonAnimationTime = 0.f;
}

CStartHUDWidget::CStartHUDWidget(const CStartHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CStartHUDWidget::~CStartHUDWidget()
{
}

bool CStartHUDWidget::Init()
{
	CWidgetWindow::Init();






	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	m_tutorialButton = CreateWidget<CButton>("tutorialButton");
	m_tutorialButton->SetPos(Center.x - 369.f / 2.f / 2.f, Center.y - 1020.f / 2.f / 2.f);
	m_tutorialButton->SetSize(369.f / 2.f, 1020.f / 2.f);
	m_tutorialButton->SetStateTexture(Button_State::Normal, "tutorialButton", TEXT("tutorialButton.png"));
	m_tutorialButton->SetStateTexture(Button_State::MouseOn, "tutorialButton", TEXT("tutorialButton.png"));
	m_tutorialButton->SetStateTexture(Button_State::Click, "tutorialButton", TEXT("tutorialButton.png"));
	m_tutorialButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
	m_tutorialButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
	m_tutorialButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_tutorialButton->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::Nothing);
	m_tutorialButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");
	m_tutorialButton->SetSize(0.f, 0.f);
	m_tutorialButton->SetZOrder(5);
	m_vecMenuButton.push_back(m_tutorialButton);


	m_MirrorMenuButton = CreateWidget<CButton>("StartButton");
	m_MirrorMenuButton->SetPos(Center.x + 969.f / 2.f/2.f, Center.y - 1020.f / 2.f/2.f);
	m_MirrorMenuButton->SetSize(369.f/2.f, 1020.f/2.f);
	m_MirrorMenuButton->SetStateTexture(Button_State::Normal, "StartButton", TEXT("StartButton.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::MouseOn, "StartButton", TEXT("StartButton.png"));
	m_MirrorMenuButton->SetStateTexture(Button_State::Click, "StartButton", TEXT("StartButton.png"));
	m_MirrorMenuButton->SetStateTint(Button_State::Normal, 0.3f, 0.3f, 0.3f, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::MouseOn, 0.3f, 0.3f, 0.3f, 1.f);
	m_MirrorMenuButton->SetStateTint(Button_State::Click, 0.3f, 0.3f, 0.3f, 1.f);
	m_MirrorMenuButton->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::Nothing);
	m_MirrorMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");
	m_MirrorMenuButton->SetSize(0.f, 0.f);
	m_MirrorMenuButton->SetZOrder(5);
	m_vecMenuButton.push_back(m_MirrorMenuButton);



	m_StageMenuButton = CreateWidget<CButton>("m_StageMenuButton");
	m_StageMenuButton->SetPos(Center.x + 2169.f / 2.f / 2.f, Center.y - 1020.f / 2.f / 2.f);
	m_StageMenuButton->SetSize(369.f / 2.f /1.5f, 1020.f / 2.f/ 1.5f);
	m_StageMenuButton->SetStateTexture(Button_State::Normal, "StageButton", TEXT("StageButton.png"));
	m_StageMenuButton->SetStateTexture(Button_State::MouseOn, "StageButton", TEXT("StageButton.png"));
	m_StageMenuButton->SetStateTexture(Button_State::Click, "StageButton", TEXT("StageButton.png"));
	m_StageMenuButton->SetStateTint(Button_State::Normal, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::MouseOn, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetStateTint(Button_State::Click, 0.3f, 0.3f, 0.3f, 1.f);
	m_StageMenuButton->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::Nothing);
	m_StageMenuButton->SetInteractionSound(Button_Sound_State::Click, "ButtonMouseOn");
	m_StageMenuButton->SetSize(0.f, 0.f);
	m_StageMenuButton->SetZOrder(5);
	m_vecMenuButton.push_back(m_StageMenuButton);










	m_Button2 = CreateWidget<CButton>("StartStartButton");
	m_Button2->SetPos(Center.x - 900.f / 4.f / 2.f, Center.y - 896.f / 2.f / 2.f);
	m_Button2->SetSize(1136.f / 5.f, 452.f / 5.f);
	m_Button2->SetStateTexture(Button_State::Normal, "StartButton_default", TEXT("button/StartButton_default.png"));
	m_Button2->SetStateTexture(Button_State::MouseOn, "StartButton_Click", TEXT("button/StartButton_Click.png"));
	m_Button2->SetStateTexture(Button_State::Click, "StartButton_Click", TEXT("button/StartButton_Click.png"));
	m_Button2->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_Button2->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_Button2->SetStateTint(Button_State::Click, 1.5f, 1.5f, 1.5f, 1.f);
	m_Button2->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::ExitClick);
	m_Button2->SetInteractionSound(Button_Sound_State::Click, "Mana2");
	//m_Button2->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_Button2->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");
	m_Button2->SetSize(0.f, 0.f);
	m_Button2->SetZOrder(4);


	m_ProfileImage = CreateWidget<CImage>("White");
	m_ProfileImage->SetTexture("White", TEXT("White.png"));
	m_ProfileImage->SetPos(0.f,0.f);
	m_ProfileImage->SetSize(1280.f, 740.f);
	m_ProfileImage->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_ProfileImage->SetZOrder(3);

	m_TitleImage = CreateWidget<CImage>("title");
	m_TitleImage->SetTexture("title", TEXT("title.png"));
	m_TitleImage->SetPos(Center.x-345.5f, Center.y + 100.5f);
	m_TitleImage->SetSize(691.f, 201.f);
	m_TitleImage->SetColorTint(1.5f, 1.5f, 1.5f, 1.5f);
	m_TitleImage->SetZOrder(3);
	m_TitleImage->SetSize(0.f, 0.f);







	return true;
}

void CStartHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	bool mousePut = CInput::GetInst()->GetMousePut();
	Vector2 mousepos = CInput::GetInst()->GetMouse2DWorldPos();
	if (mousePut && m_Stage2 == true && m_ButtonAnimationLeft == false&& m_ButtonAnimationRight == false && m_ExitStage == false)
	{
		if (mousepos.x >= Center.x)
		{
			if (m_ButtonIndex < 2)
			{
				m_ButtonAnimationTime = 0.f;
				m_ButtonIndex++;
				m_SelectButton = m_vecMenuButton[m_ButtonIndex];
				m_ButtonAnimationRight = true;
				for (int i = 0; i < m_vecMenuButton.size(); ++i)
				{
					m_vecMenuButton[i]->SetStateTint(Button_State::Normal, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetStateTint(Button_State::MouseOn, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetStateTint(Button_State::Click, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::Nothing);
				}
				m_SelectButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
				m_SelectButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
				m_SelectButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
			}

		}
		else
		{
			if (m_ButtonIndex > 0)
			{
				m_ButtonAnimationTime = 0.f;
				m_ButtonIndex--;
				m_SelectButton = m_vecMenuButton[m_ButtonIndex];
				m_ButtonAnimationLeft = true;
				for (int i = 0; i < m_vecMenuButton.size(); ++i)
				{
					m_vecMenuButton[i]->SetStateTint(Button_State::Normal, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetStateTint(Button_State::MouseOn, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetStateTint(Button_State::Click, 0.3f, 0.3f, 0.3f, 1.f);
					m_vecMenuButton[i]->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::Nothing);
				}
				m_SelectButton->SetStateTint(Button_State::Normal, 1.4, 1.4, 1.4, 1.f);
				m_SelectButton->SetStateTint(Button_State::MouseOn, 1.6f, 1.6f, 1.6f, 1.f);
				m_SelectButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
			}

		}
	}
	if (m_ButtonAnimationRight && m_ExitStage == false)
	{
		m_ButtonAnimationTime += DeltaTime;
		Vector2 EndPoint = Vector2(547.75f,105.f);
		EndPoint.x = EndPoint.x - m_SelectButton->GetPos().x;
		if (EndPoint.x <= 0)
		{
			for (int i = 0; i < m_vecMenuButton.size(); ++i)
			{
				m_vecMenuButton[i]->AddPos(EndPoint.x*DeltaTime* 20.f -DeltaTime*20.f,0.f);
			}
		}
		else
		{
			m_ButtonAnimationRight = false;
			SetSelectButton();
		}
	}


	if (m_ButtonAnimationLeft && m_ExitStage == false)
	{
		m_ButtonAnimationTime += DeltaTime;
		Vector2 EndPoint = Vector2(547.75f, 105.f);
		EndPoint.x = EndPoint.x - m_SelectButton->GetPos().x;
		if (EndPoint.x >= 0)
		{
			for (int i = 0; i < m_vecMenuButton.size(); ++i)
			{
				m_vecMenuButton[i]->AddPos(EndPoint.x * DeltaTime * 20.f + DeltaTime * 20.f, 0.f);
			}
		}
		else
		{
			m_ButtonAnimationLeft = false;
			SetSelectButton();
		}
	}






	if (m_StartstageWhiteDesolve)
	{
		if (!m_StartstageWhiteDesolveMax)
		{
			m_WhiteTime += DeltaTime;
			if (m_WhiteTime >= 3.f)
			{
				m_WhiteTime = 0.f;
				m_StartstageWhiteDesolveMax = true;
				
				
			}
		}
		else if(m_StartstageWhiteDesolveMax)
		{
			m_ProfileImage->AddColorTint(0.f, 0.f, 0.f, -1.f * DeltaTime);
			m_WhiteTime += DeltaTime;
			
			if (m_WhiteTime >= 1.5f)
			{
				m_StartstageWhiteDesolve = false;
				m_StartstageWhiteDesolveMax = false;
				m_WhiteTime = 0.f;
				m_Button2->SetSize(1136.f / 5.f, 452.f / 5.f);
				m_ProfileImage->SetColorTint(1.f, 1.f, 1.f, 0.f);
				
			}
			else if (m_WhiteTime >= 1.f)
			{
				m_TitleImage->SetSize(691.f, 201.f);
				if (m_titlesound)
				{
					CResourceManager::GetInst()->SoundPlay("titlesound");
					m_titlesound = false;
				}
				
			}
		
		}
	}

	if (m_MapObj)
	{
		if (m_Stage)
		{
			if (!m_WhiteMaxState)
			{
				m_ProfileImage->AddColorTint(0.f, 0.f, 0.f, 2.f * DeltaTime);
				m_WhiteTime += DeltaTime;
				if (m_WhiteTime >= 0.5f)
				{
					m_MapObj->SetStart2(true);
					m_WhiteTime = 0.f;
					m_WhiteMaxState = true;
				}
			}
			else if(m_WhiteMaxState)
			{
				m_ProfileImage->AddColorTint(0.f, 0.f, 0.f, -2.f * DeltaTime);
				m_WhiteTime += DeltaTime;
				m_tutorialButton->SetSize(369.f / 2.f, 1020.f / 2.f);
				m_MirrorMenuButton->SetSize(369.f / 2.f, 1020.f / 2.f);
				m_StageMenuButton->SetSize(369.f / 2.f, 1020.f / 2.f);
				m_MapObj->SetBackGround();

				if (m_WhiteTime >= 0.5f)
				{
					
					m_Stage = false;
					m_WhiteTime = 0.f;
					m_WhiteMaxState = false;
					m_MapObj->SetStart2(false);
					m_Stage2 = true;
				}
			}
			
		}

	
	}

	if (m_Stage2)
	{
		m_BlurCount -= DeltaTime;

	

		if (m_ExitStage)
		{

			for (int i = 0 ;i < m_vecMenuButton.size(); ++i)
			{
				if (m_vecMenuButton[i] != m_SelectButton)
				{
					m_vecMenuButton[i]->SetColorTint(1.f, 1.f, 1.f, 0.f);
				}
			}
			CRenderManager::GetInst()->AddEmpty(Vector2(1.f * DeltaTime, 0.f));
			m_ProfileImage->AddColorTint(0.f, 0.f, 0.f, 0.5f * DeltaTime);
			m_ExitStageCount += DeltaTime;

			Vector2 tempsize = Vector2(0.f,0.f);
			Vector2 temppos = Vector2(600.f, 360.f);
			tempsize -= m_SelectButton->GetSize() - Vector2(1.f, 1.f);
			temppos -= m_SelectButton->GetPos() - Vector2(1.f, 1.f);
			tempsize *= 10.f;
			temppos *= 10.f;
			m_SelectButton->AddSize(tempsize* DeltaTime);
			m_SelectButton->AddPos(temppos * DeltaTime);
			CRenderManager::GetInst()->SetBlur(true);

			if (m_ExitStageCount > 1.5f)
			{	
				m_SelectButton->SetPos(0,1000.f);
				m_SelectButton->SetSize(0.f, 0.f);

				if (m_ButtonIndex == 0)
				{
					CRenderManager::GetInst()->SetBlur(false);
					CSceneManager::GetInst()->CreateNextScene();
					CSceneManager::GetInst()->SetSceneMode<CTutorialScene>(false);
				}
				else if (m_ButtonIndex == 1)
				{
					CClientManager::GetInst()->SetAiindex(0);
					CRenderManager::GetInst()->SetBlur(false);
					CSceneManager::GetInst()->CreateNextScene();
					CSceneManager::GetInst()->SetSceneMode<CGodSelectScene>(false);
				}
				else if (m_ButtonIndex == 2)
				{
					CRenderManager::GetInst()->SetBlur(false);
					CSceneManager::GetInst()->CreateNextScene();
					CSceneManager::GetInst()->SetSceneMode<CStageScene>(false);
				}
			
			}
		}
		else
		{
			if (m_BlurCount > 0.f)
			{
				CRenderManager::GetInst()->AddEmpty(Vector2(0.00001f * DeltaTime, 0.f));

			}
		}

	
	}


}

void CStartHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStartHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CStartHUDWidget* CStartHUDWidget::Clone()
{
	return new CStartHUDWidget(*this);
}

void CStartHUDWidget::StartClick()
{
	// 다음 장면으로 넘어간다.

	m_ExitStage = true;
	for (int i = 0; i < m_vecMenuButton.size(); ++i)
	{
		
		m_vecMenuButton[i]->SetSize(0.f, 0.f);

	}
	m_SelectButton->SetSize(369.f / 2.f / 1.5f, 1020.f / 2.f / 1.5f);
}

void CStartHUDWidget::ExitClick()
{
	m_ButtonAnimationLeft = false;
	m_ButtonAnimationRight = false;
	m_Stage = true;
	m_Button2->SetSize(0.f, 0.f);
	m_WhiteTime = 0;
	m_TitleImage->SetSize(0.f, 0.f);
	m_SelectButton = m_MirrorMenuButton;
	m_ButtonIndex = 0;
}

void CStartHUDWidget::StageExitClick()
{
	m_ExitStage = true;
	for (int i = 0; i < m_vecMenuButton.size(); ++i)
	{

		m_vecMenuButton[i]->SetSize(0.f, 0.f);

	}
	m_SelectButton->SetSize(369.f / 2.f / 1.5f, 1020.f / 2.f / 1.5f);
}

void CStartHUDWidget::Nothing()
{
}

void CStartHUDWidget::SetSelectButton()
{
	m_SelectButton->SetClickCallback<CStartHUDWidget>(this, &CStartHUDWidget::StartClick);
}
