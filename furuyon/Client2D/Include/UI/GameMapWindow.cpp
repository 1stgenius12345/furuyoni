#include "GameMapWindow.h"
#include "Device.h"
#include "Engine.h"
#include "../SceneMode/MainScene.h"
#include "../SceneMode/LoadingScene.h"
#include "Scene/SceneManager.h"
#include "Timer.h"
#include "../Object/GameMapObj.h"
CGameMapWindow::CGameMapWindow():
	m_GameMapObj(nullptr),
	m_Animation(false),
	m_AnimationTime(0.f)
{
}

CGameMapWindow::CGameMapWindow(const CGameMapWindow& widget) :
	CWidgetWindow(widget)
{
}

CGameMapWindow::~CGameMapWindow()
{
}

bool CGameMapWindow::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	CreateTextANDNumber( "Range_Number", m_Range_Number, Vector2(623.f, 497.f), TEXT("거리"), 10, 1.f);
	CreateTextANDNumber( "Dust_Number", m_Dust_Number, Vector2(796.f, 60.f), TEXT("땅"), 0, 1.f);
	CreateTextANDNumber("Dalin_Number", m_Dalin_Number, Vector2(526.f, 130.f), TEXT("달인"), 0, 0.6f);
	CreateTextANDNumber("Player1_Life_Number", m_Player1_Life_Number, Vector2(1136.f, 587.f), TEXT("생명력"), 10, 1.f);
	CreateTextANDNumber( "Player1_Shiled_Number", m_Player1_Shiled_Number, Vector2(1045.f, 389.), TEXT("방어막"), 3, 1.f);
	CreateTextANDNumber("Player1_Mana_Number", m_Player1_Mana_Number, Vector2(1179.f, 295.f), TEXT("마나"), 0, 1.f);
	CreateTextANDNumber( "Player1_Focus_Number", m_Player1_Focus_Number, Vector2(1192.f, 404.f), TEXT("집중력"), 0, 0.7f);
	CreateTextANDNumber("Player1_Deck_Number", m_Player1_Deck_Number, Vector2(968.f, 506.f), TEXT("덱"), 0, 0.7f);
	

	CreateTextANDNumber( "Player2_Life_Number", m_Player2_Life_Number, Vector2(105.f, 100.f), TEXT("생명력"), 10, 1.f);
	CreateTextANDNumber( "Player2_Shiled_Number", m_Player2_Shiled_Number, Vector2(204.f, 270.f), TEXT("방어막"), 3, 1.f);
	CreateTextANDNumber( "Player2_Mana_Number", m_Player2_Mana_Number, Vector2(72.f, 345.f), TEXT("마나"), 0, 1.f);
	CreateTextANDNumber( "Player2_Focus_Number", m_Player2_Focus_Number, Vector2(77.f, 230.f), TEXT("집중력"), 1, 0.7f);
	CreateTextANDNumber("Player2_Deck_Number", m_Player2_Deck_Number, Vector2(295.f, 127.f), TEXT("덱"), 0, 0.7f);

	float fps = CEngine::GetInst()->GetTimer()->GetFPS();
	std::string num_str1(std::to_string(fps));


	m_FPS = CreateWidget<CText>("FPS");
	m_FPS->SetText(StringToTCHAR(num_str1));
	m_FPS->SetPos(Center.x+300.f , Center.y-200.f);
	m_FPS->SetSize(200.f, 50.f);
	m_FPS->SetFontSize(20.f);
	m_FPS->SetShadowEnable(false);
	m_FPS->SetShadowColor(1.f, 1.f, 0.f);
	m_FPS->SetShadowAlphaEnable(true);
	m_FPS->SetShadowOpacity(0.5f);
	m_FPS->SetAlignH(TEXT_ALIGN_H::Center);
	m_FPS->SetAlignV(TEXT_ALIGN_V::Bottom);
	
	m_Player1Press = CreateWidget<CImage>("m_Player1Press");
	m_Player1Press->SetPos(1192.f - 185.f / 4.f, 246.f);
	m_Player1Press->SetSize(195.f/3.f,223.f/3.f);
	m_Player1Press->SetTexture("press", TEXT("press.png"));

	m_Player2Press = CreateWidget<CImage>("m_Player2Press");
	m_Player2Press->SetPos(77.f - 185.f / 4.f, 420.f);
	m_Player2Press->SetSize(195.f / 3.f, 223.f / 3.f);
	m_Player2Press->SetTexture("press", TEXT("press.png"));
	return true;
}

void CGameMapWindow::Update(float DeltaTime)
{
	float fps = CEngine::GetInst()->GetTimer()->GetFPS();
	std::string num_str1(std::to_string(fps));
	m_FPS->SetText(StringToTCHAR(num_str1));
	CWidgetWindow::Update(DeltaTime);
	float ratio = 150.f / 134.f;
	if(m_Range_Number == nullptr)
		return;

	if (m_Animation)
	{
		m_AnimationTime += DeltaTime;
		int temp = m_que_Animation.front();

		if (m_AnimationTime <= 0.1f)
			AddNumberSizePlus(DeltaTime, m_que_Animation.front());
		else if (m_AnimationTime <= 0.2f)
			AddNumberSizePlus(-DeltaTime, m_que_Animation.front());
		else if (m_AnimationTime <= 0.3f)
		{
			SetNumberSizePlus(DeltaTime, m_que_Animation.front());
			m_Dust_Number->SetPos(751.f, 580.f);
			m_Animation = false;
			m_que_Animation.pop();
		}
		else if (m_AnimationTime <= 0.31f)
		{
			
		}

	}
	else if (m_que_Animation.size() > 0)
	{
		m_Animation = true;
		m_AnimationTime = 0.f;
	}

	if(m_GameMapObj->GetPlayer1Press())
		m_Player1Press->SetSize(195.f / 4.f, 223.f / 4.f);
	else
		m_Player1Press->SetSize(0.f, 0.f);
	if (m_GameMapObj->GetAiPress())
		m_Player2Press->SetSize(195.f / 4.f, 223.f / 4.f);
	else
		m_Player2Press->SetSize(0.f, 0.f);

	m_Range_Number 			   ->SetNumber( m_GameMapObj->GetRange());
	m_Dust_Number			   ->SetNumber( m_GameMapObj->GetDust());
	m_Player1_Life_Number	   ->SetNumber( m_GameMapObj->GetPlayer1Life());
	m_Player1_Shiled_Number	   ->SetNumber( m_GameMapObj->GetPlayer1Shiled());
	m_Player1_Mana_Number	   ->SetNumber( m_GameMapObj->GetPlayer1Mana());
	m_Player1_Focus_Number	   ->SetNumber( m_GameMapObj->GetPlayer1focus());
	m_Player1_Deck_Number	   ->SetNumber(m_GameMapObj->GetPlayer1DeckSize());
	m_Player2_Life_Number	   ->SetNumber( m_GameMapObj->GetPlayer2Life());
	m_Player2_Shiled_Number	   ->SetNumber( m_GameMapObj->GetPlayer2Shiled());
	m_Player2_Mana_Number	   ->SetNumber( m_GameMapObj->GetPlayer2Mana());
	m_Player2_Focus_Number	   ->SetNumber( m_GameMapObj->GetPlayer2focus());
	m_Player2_Deck_Number	   ->SetNumber( m_GameMapObj->GetPlayer2DeckSize());
	m_Dalin_Number->SetNumber(m_GameMapObj->GetDALINRange());

}

void CGameMapWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CGameMapWindow::Render()
{
	CWidgetWindow::Render();
}

CGameMapWindow* CGameMapWindow::Clone()
{
	return new CGameMapWindow(*this);
}

void CGameMapWindow::StartClick()
{

}

void CGameMapWindow::ExitClick()
{
	
}

void CGameMapWindow::CreateTextANDNumber( const std::string& Numbername,CSharedPtr<CNumberWidget>&  Number1, Vector2 pos, const TCHAR* name, int num, float size)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	//CText* text;
	//text = CreateWidget<CText>(textname);
	//text->SetText(name);
	//if(num >= 10)
	//	text->SetPos(Center.x + pos.x - 70.f, Center.y + pos.y + 134.f / 1.4f);
	//else
	//	text->SetPos(Center.x + pos.x - 87.5f, Center.y + pos.y + 134.f / 1.4f);
	//text->SetSize(200.f, 50.f);
	//text->SetFontSize(20.f);
	//text->SetShadowEnable(false);
	//text->SetShadowColor(1.f, 1.f, 0.f);
	//text->SetShadowAlphaEnable(true);
	//text->SetShadowOpacity(0.5f);
	//text->SetAlignH(TEXT_ALIGN_H::Center);
	//text->SetAlignV(TEXT_ALIGN_V::Bottom);
	CNumberWidget* Number;
	Number = CreateWidget<CNumberWidget>(Numbername);
	Number->SetPos((pos.x)-45.f, (720.f -pos.y)-80.f);
	Number->SetNumberSize(150.f / 1.4f* size, 134.f / 1.4f* size);
	Number->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	Number->SetNumber(num);
	Number->SetFrameCount(10, 4);
	Number->SetZOrder(3);
	Number->SetPivot(0.5f, 0.5f);
	//text1 = text;

	Number1 = Number;
}

void CGameMapWindow::AddNumberSizePlus(float delta, int index)
{
	float ratio = 150.f / 134.f;

	switch (index)
	{
	case 1:
		m_Range_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 2:
		m_Dust_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 3:
		m_Player1_Life_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
	break;
	case 4:
		m_Player1_Shiled_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 5:
		m_Player1_Mana_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 6:
		m_Player1_Focus_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 7:
		m_Player1_Deck_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 8:
		m_Player2_Life_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 9:
		m_Player2_Shiled_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 10:
		m_Player2_Mana_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 11:
		m_Player2_Focus_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 12:
		m_Player2_Deck_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	case 13:
		m_Dalin_Number->AddNumberSize(delta * 100.f, delta * ratio * 100.f);
		break;
	default:
		break;
	}
	

}

void CGameMapWindow::SetNumberSizePlus(float delta, int index)
{
	switch (index)
	{
	case 1:
		m_Range_Number->SetSize(195.f / 4.f, 223.f / 4.f);
		m_Range_Number->SetNumberSize(150.f / 1.4f , 134.f / 1.4f);
		break;
	case 2:
		m_Dust_Number->SetSize(195.f / 4.f, 223.f / 4.f);
		m_Dust_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 3:
		m_Player1_Life_Number->SetSize(195.f / 4.f, 223.f / 4.f);
		m_Player1_Life_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 4:
		m_Player1_Shiled_Number->SetSize(195.f / 4.f, 223.f / 4.f);
		m_Player1_Shiled_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 5:
		m_Player1_Mana_Number->SetSize(195.f / 4.f, 223.f / 4.f);
		m_Player1_Mana_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 6:
		m_Player1_Focus_Number->SetNumberSize(150.f / 1.4f* 0.7f, 134.f / 1.4f * 0.7f);
		break;
	case 7:
		m_Player1_Deck_Number->SetNumberSize(150.f / 1.4f * 0.7f, 134.f / 1.4f * 0.7f);
		break;
	case 8:
		m_Player2_Life_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 9:
		m_Player2_Shiled_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 10:
		m_Player2_Mana_Number->SetNumberSize(150.f / 1.4f, 134.f / 1.4f);
		break;
	case 11:
		m_Player2_Focus_Number->SetNumberSize(150.f / 1.4f * 0.7f, 134.f / 1.4f * 0.7f);
		break;
	case 12:
		m_Player2_Deck_Number->SetNumberSize(150.f / 1.4f * 0.7f, 134.f / 1.4f * 0.7f);
		break;
	case 13:
		m_Player2_Deck_Number->SetNumberSize(150.f / 1.4f * 0.7f, 134.f / 1.4f * 0.7f);
	default:
		break;
	}
	
}
