
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
#include "Resource/ResourceManager.h"
#include "Input.h"
#include "GameMapAnimation.h"
#include "../Object/GameMapObj.h"
#include "../ClientManager.h"
CGameMapAnimation::CGameMapAnimation()

{
	m_Player1firstindex	  =0;
	m_Player1secondindex  =0;
	m_Player2firstindex	  =0;
	m_Player2secondindex  =0;

	m_Turn = false;
	m_End = false;
	m_Triger1 = true;
	m_Triger2 = true;

}

CGameMapAnimation::CGameMapAnimation(const CGameMapAnimation& widget) :
	CWidgetWindow(widget)
{
}

CGameMapAnimation::~CGameMapAnimation()
{
}

bool CGameMapAnimation::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	m_AlphaBlack = CreateWidget<CImage>("AlphaBlack");
	m_AlphaBlack->SetTexture("AlphaBlack", TEXT("AlphaBlack.png"));
	m_AlphaBlack->SetPos(0.f, 0.f);
	m_AlphaBlack->SetSize(1280.f, 720.f);
	m_AlphaBlack->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_AlphaBlack->SetZOrder(0);

	m_VS = CreateWidget<CImage>("VS");
	m_VS->SetTexture("VS", TEXT("VS.png"));
	m_VS->SetPos(0.f, 0.f);
	m_VS->SetSize(1280.f, 720.f);
	m_VS->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_VS->SetZOrder(6);

	m_Player1first = CreateWidget<CImage>("m_Player1first");
	m_Player1first->SetTexture("NormalInfo", TEXT("/card/megami/0.png"));
	m_Player1first->SetPos(1400.f, 50.f);
	m_Player1first->SetSize(685.f / 3.5f, 1344.f / 3.5f);
	m_Player1first->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Player1first->SetZOrder(3);

	m_Player1second = CreateWidget<CImage>("m_Player1second");
	m_Player1second->SetTexture("NormalInfo", TEXT("/card/megami/0.png"));
	m_Player1second->SetPos(m_Player1first->GetPos().x + 500.f /3.5f, 30.f);
	m_Player1second->SetSize(685.f / 3.5f, 1344.f / 3.5f);
	m_Player1second->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Player1second->SetZOrder(3);

	m_Player2first = CreateWidget<CImage>("m_Player2first");
	m_Player2first->SetTexture("NormalInfo", TEXT("/card/megami/0.png"));
	m_Player2first->SetPos(-450.f, 280.f);
	m_Player2first->SetSize(685.f / 3.5f, 1344.f / 3.5f);
	m_Player2first->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Player2first->SetZOrder(3);
			
	m_Player2second = CreateWidget<CImage>("m_Player2second");
	m_Player2second->SetTexture("NormalInfo", TEXT("/card/megami/0.png"));
	m_Player2second->SetPos(m_Player2first->GetPos().x + 500.f / 3.5f, 260.f);
	m_Player2second->SetSize(685.f / 3.5f, 1344.f / 3.5f);
	m_Player2second->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Player2second->SetZOrder(3);






	return true;
}

void CGameMapAnimation::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	m_firsttime += DeltaTime;
	if (m_firsttime >= 1.f && m_firsttime <= 2.5f)
	{
		Vector2 EndPoint = Vector2(670.f, 30.f);
		EndPoint = EndPoint.x - m_Player1first->GetPos().x;
		if (EndPoint.x < 0.f)
		{
			m_Player1first->AddPos(Vector2(EndPoint.x * DeltaTime * 15.f - DeltaTime * 10.f, 0.f));
			m_Player1second->SetPos(m_Player1first->GetPos().x + 500.f / 3.5f, 30.f);
		}

		Vector2 End2Point = Vector2(250.f, 260.f);
		End2Point = End2Point.x - m_Player2first->GetPos().x;
		if (End2Point.x > 0.f)
		{
			m_Player2first->AddPos(Vector2(End2Point.x * DeltaTime * 15.f + DeltaTime * 10.f, 0.f));
			m_Player2second->SetPos(m_Player2first->GetPos().x + 500.f / 3.5f, 260.f);
		}
	}
	else if (m_firsttime >= 4.f && m_firsttime <= 5.f)
	{
		m_VS->SetSize(0.f, 0.f);


		Vector2 EndPoint = Vector2(670.f, -700.f);
		EndPoint = EndPoint.y - m_Player1first->GetPos().y;
		if (EndPoint.y < 0.f)
		{
			m_Player1first->AddPos(Vector2( 0.f, EndPoint.y * DeltaTime * 15.f - DeltaTime * 10.f));
			m_Player1second->SetPos(m_Player1first->GetPos().x + 500.f / 3.5f, m_Player1first->GetPos().y - 20.f);
		}

		Vector2 End2Point = Vector2(250.f, 1060.f);
		End2Point = End2Point.y - m_Player2first->GetPos().y;
		if (End2Point.y > 0.f)
		{
			m_Player2first->AddPos(Vector2( 0.f, End2Point.y * DeltaTime * 15.f + DeltaTime * 10.f));
			m_Player2second->SetPos(m_Player2first->GetPos().x + 500.f / 3.5f, m_Player2first->GetPos().y - 20.f);
		}
	}
	else if (m_firsttime >= 5.f && m_firsttime <= 5.3f)
	{
		m_Player1first->SetTexture("선공", TEXT("선공.png"));
		m_Player1first->SetPos(640.f+10.f, 360.f-148.f);
		m_Player1first->SetSize(744.f / 3.5f, 1038.f / 3.5f);

		m_Player1second->SetTexture("후공", TEXT("후공.png"));
		m_Player1second->SetPos(640.f - 10.f-  212.f, 360.f - 148.f);
		m_Player1second->SetSize(744.f / 3.5f, 1038.f / 3.5f);
	}
	else if (m_firsttime >= 5.4f && m_firsttime <= 5.5f)
	{
		m_Player1first->SetPos(640.f - 106.f, 360.f - 148.f);
		m_Player1second->SetPos(640.f - 106.f, 360.f - 148.f);
		m_Player1second->SetTexture("CardSample", TEXT("/card/back.png"));
		m_Player1first->SetTexture("CardSample", TEXT("/card/back.png"));
	}
	else if (m_firsttime >= 5.5f && m_firsttime <= 7.5f)
	{

		m_Player1first->AddPos(Vector2(40 * cos(8* m_firsttime *PI),0.f));
		m_Player1second->AddPos(Vector2(-40 *cos(8* m_firsttime * PI ), 0.f));
	}
	else if (m_firsttime >= 7.5f && m_firsttime <= 7.7f)
	{
		m_Player1first->SetPos(640.f - 106.f, 360.f - 148.f);
		m_Player1second->SetPos(640.f - 106.f, 360.f - 148.f);
	}
	else if (m_firsttime >= 7.7f && m_firsttime <= 7.8f)
	{
		m_Player1first->AddSize(Vector2(744.f / 50.f *DeltaTime, 1038.f / 50.f * DeltaTime));
		srand(GetTickCount());

		if (m_Triger1)
		{
			m_Turn = true;
			m_Triger1 = false;
		}
			
		

		m_Player1second->SetSize(0.f,0.f);
	}
	else if (m_firsttime >= 7.8f && m_firsttime <= 7.9f)
	{
		m_Player1first->AddSize(Vector2(-744.f / 50.f * DeltaTime, -1038.f / 50.f * DeltaTime));
	}
	else if (m_firsttime >= 9.f && m_firsttime <= 9.05f)
	{
		m_Player1first->SetSize(0.f, 0.f);
		m_AlphaBlack->SetSize(0.f, 0.f);
	
		


		if (m_Triger2)
		{
			m_End = true;
			m_Triger2 = false;
		}
	}
	else if(m_firsttime >= 9.2f )
	{
		m_firsttime -= DeltaTime;
	}



	if (m_End)
	{
		//CResourceManager::GetInst()->SoundPause("fightbgm");
		m_GameMapObj->SetWhoFirst(m_WhoTrun);
		m_GameMapObj->SetMuligun(true);
		m_End = false;
	}



	if (m_Turn)
	{
		srand(GetTickCount());
		int i = rand() % 2;
		if (CClientManager::GetInst()->GetAiIndex() > 0)
		{
			CExcel tempExcel;
			i = tempExcel.StageTurn(CClientManager::GetInst()->GetAiIndex(),"mapdata.csv");
		}
		if (i == 2)
		{
			i = rand() % 2;
		}
		if (i == 0)
		{
			m_Player1first->SetTexture("선공", TEXT("선공.png"));
			m_WhoTrun = 1;
		}
		else
		{
			m_Player1first->SetTexture("후공", TEXT("후공.png"));
			m_WhoTrun = 2;
		}
		m_Turn = false;
	}

}

void CGameMapAnimation::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CGameMapAnimation::Render()
{
	CWidgetWindow::Render();
}

CGameMapAnimation* CGameMapAnimation::Clone()
{
	return new CGameMapAnimation(*this);
}

void CGameMapAnimation::StartClick()
{

}

void CGameMapAnimation::ExitClick()
{

}

void CGameMapAnimation::SetPlayer1first()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_Player1firstindex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_Player1firstindex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_Player1first->SetTexture(std_str, tex);
}

void CGameMapAnimation::SetPlayer1second()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_Player1secondindex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_Player1secondindex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_Player1second->SetTexture(std_str, tex);
}

void CGameMapAnimation::SetPlayer2first()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_Player2firstindex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_Player2firstindex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_Player2first->SetTexture(std_str, tex);
}

void CGameMapAnimation::SetPlayer2second()
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_Player2secondindex);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_Player2secondindex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_Player2second->SetTexture(std_str, tex);
}
