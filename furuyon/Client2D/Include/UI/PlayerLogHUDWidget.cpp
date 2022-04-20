#include "PlayerLogHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
#include "../Object/BuildingCard.h"
#include "Scene/SceneManager.h"
#include "../SceneMode/MainScene.h"
#include "Input.h"
CPlayerLogHUDWidget::CPlayerLogHUDWidget():
	m_UseCardBig(false),
	m_TargetCardBig(false)
	

{
}

CPlayerLogHUDWidget::CPlayerLogHUDWidget(const CPlayerLogHUDWidget& widget)
{
}

CPlayerLogHUDWidget::~CPlayerLogHUDWidget()
{
}

bool CPlayerLogHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	/*m_UseCard = CreateWidget<CButton>("m_UseCard");
	m_UseCard->SetPos(306.f,12.f);
	m_UseCard->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_UseCard->SetStateTint(Button_State::MouseOn, 1.5f, 1.5f, 1.5f, 1.5f);
	m_UseCard->SetStateTint(Button_State::Click, 0.8f, 0.8f, 0.8f, 0.8f);
	m_UseCard->SetSize(65.f,90.f);
	m_UseCard->SetStateTexture(Button_State::Normal, "���", TEXT("button/���.png"));
	m_UseCard->SetStateTexture(Button_State::MouseOn, "���1", TEXT("button/���1.png"));
	m_UseCard->SetStateTexture(Button_State::Click, "���1", TEXT("button/���1.png"));
	m_UseCard->SetClickCallback<CPlayerLogHUDWidget>(this, &CPlayerLogHUDWidget::ClickUse);
	m_UseCard->SetZOrder(10);

	m_TargetCard = CreateWidget<CButton>("m_TargetCard");
	m_TargetCard->SetPos(169.f, 12.f);
	m_TargetCard->SetStateTint(Button_State::Normal, 1.f, 1.f, 1.f, 1.f);
	m_TargetCard->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_TargetCard->SetStateTint(Button_State::Click, 1.f, 1.f, 1.f, 1.f);
	m_TargetCard->SetSize(65.f, 90.f );
	m_TargetCard->SetStateTexture(Button_State::Normal, "����", TEXT("button/����.png"));
	m_TargetCard->SetStateTexture(Button_State::MouseOn, "����1", TEXT("button/����1.png"));
	m_TargetCard->SetStateTexture(Button_State::Click, "����1", TEXT("button/����1.png"));
	m_TargetCard->SetClickCallback<CPlayerLogHUDWidget>(this, &CPlayerLogHUDWidget::ClickBack);
	m_TargetCard->SetZOrder(8);*/
	m_PlayerImage = CreateWidget<CImage>("m_PlayerImage");
	m_PlayerImage->SetTexture("��ǻ�ͻ��α�", TEXT("log/��ǻ�ͻ��α�.png"));
	m_PlayerImage->SetPos(0.f, 0.f);
	m_PlayerImage->SetSize(390.f, 114.f);
	m_PlayerImage->SetZOrder(0);
	m_PlayerImage->SetShader("UILogShader");

	m_UseCard = CreateWidget<CImage>("m_UseCard");
	m_UseCard->SetTexture("��ǻ�ͻ��α�", TEXT("log/��ǻ�ͻ��α�.png"));
	m_UseCard->SetPos(306.f, 12.f);
	m_UseCard->SetSize(65.f, 90.f);
	m_UseCard->SetZOrder(1);
	m_UseCard->SetShader("UILogShader");

	m_TargetCard = CreateWidget<CImage>("m_TargetCard");
	m_TargetCard->SetTexture("��ǻ�ͻ��α�", TEXT("log/��ǻ�ͻ��α�.png"));
	m_TargetCard->SetPos(169.f, 12.f);
	m_TargetCard->SetSize(65.f, 90.f);
	m_TargetCard->SetZOrder(1);
	m_TargetCard->SetShader("UILogShader");

	



	return true;
}

void CPlayerLogHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	
	
}

void CPlayerLogHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerLogHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CPlayerLogHUDWidget* CPlayerLogHUDWidget::Clone()
{
	return new CPlayerLogHUDWidget(*this);
}

void CPlayerLogHUDWidget::CreateTex(int HeroIndex, int CardIndex,int CardClass)
{
	if (HeroIndex == 0 && CardIndex == 1)
	{
		m_UseCard->SetTexture("����", TEXT("����.png"));
		
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 2)
	{
		m_UseCard->SetTexture("����", TEXT("����.png"));
		
		
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 3)
	{
		m_UseCard->SetTexture( "�ְ���", TEXT("�ְ���.png"));
	
	
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 4)
	{
		m_UseCard->SetTexture( "ǰ��", TEXT("ǰ��.png"));
	
		
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 5)
	{
		m_UseCard->SetTexture( "��Ż", TEXT("��Ż.png"));
		
	
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 6)
	{
		m_UseCard->SetTexture("����ȸ��", TEXT("����ȸ��.png"));
		
	
		return;
	}
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), CardIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);

	if (CardClass == 0)
		_tcsncat_s(tex, TEXT("Normal/"), 7);
	else
		_tcsncat_s(tex, TEXT("Hero/"), 5);

	TCHAR ds1[3] = { 0 };
	_stprintf_s(ds1, _countof(ds1), TEXT("%d"), HeroIndex);

	_tcsncat_s(tex, ds1, 1);
	_tcsncat_s(tex, TEXT("/"), 1);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), CardIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);


	m_UseCard->SetTexture( std_str, tex);
	return;

}

void CPlayerLogHUDWidget::CreateTex2(int HeroIndex, int CardIndex, int CardClass)
{
	if (HeroIndex == 0 && CardIndex == 1)
	{
		m_TargetCard->SetTexture("����", TEXT("����.png"));
		
		return;
	}
	else if (HeroIndex == 0 && CardIndex == 2)
	{
		m_TargetCard->SetTexture( "����", TEXT("����.png"));
		

		return;
	}
	else if (HeroIndex == 0 && CardIndex == 3)
	{
		m_TargetCard->SetTexture("�ְ���", TEXT("�ְ���.png"));
		

		return;
	}
	else if (HeroIndex == 0 && CardIndex == 4)
	{
		m_TargetCard->SetTexture("ǰ��", TEXT("ǰ��.png"));
		
	

		return;
	}
	else if (HeroIndex == 0 && CardIndex == 5)
	{
		m_TargetCard->SetTexture( "��Ż", TEXT("��Ż.png"));
	

		return;
	}
	else if (HeroIndex == 0 && CardIndex == 6)
	{
		m_TargetCard->SetTexture( "����ȸ��", TEXT("����ȸ��.png"));
		

		return;
	}
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), CardIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);

	if (CardClass == 0)
		_tcsncat_s(tex, TEXT("Normal/"), 7);
	else
		_tcsncat_s(tex, TEXT("Hero/"), 5);

	TCHAR ds1[3] = { 0 };
	_stprintf_s(ds1, _countof(ds1), TEXT("%d"), HeroIndex);

	_tcsncat_s(tex, ds1, 1);
	_tcsncat_s(tex, TEXT("/"), 1);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), CardIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);


	m_TargetCard->SetTexture( std_str, tex);
	

}

void CPlayerLogHUDWidget::ClickUse()
{
	if (m_UseCardBig == false)
	{
		
		m_UseCard->SetPos(0.f- m_Pos.x- 65.f * 2.5f, 0.f- m_Pos.y- 90.f * 2.5f);
		m_UseCard->SetSize(65.f*5.f, 90.f*5.f);
		m_UseCardBig = true;
	}
}

void CPlayerLogHUDWidget::ClickBack()
{
	
}

void CPlayerLogHUDWidget::AiDaeugLog(int HeroIndex, int CardIndex, int CardClass, int HeroIndex2, int CardIndex2, int CardClass2)
{
	m_PlayerImage->SetTexture("��ǻ�ʹ����α�", TEXT("log/��ǻ�ʹ����α�.png"));
	CreateTex(HeroIndex,CardIndex,CardClass);
	CreateTex2(HeroIndex2, CardIndex2, CardClass2);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(65.f, 90.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
}

// 1~6����
void CPlayerLogHUDWidget::AiBackCardLog(int focus)
{
	m_PlayerImage->SetTexture("��ǻ�͵���α�", TEXT("log/��ǻ�͵���α�.png"));
	CreateTex(0, focus, 0);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
}

void CPlayerLogHUDWidget::AiFocusLog(int focus)
{
	m_PlayerImage->SetTexture("��ǻ�����߷·α�", TEXT("log/��ǻ�����߷·α�.png"));
	CreateTex(0, focus, 0);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
}

void CPlayerLogHUDWidget::AiRefreshLog()
{
	m_PlayerImage->SetTexture("��ǻ�͸��������α�", TEXT("log/��ǻ�͸��������α�.png"));
	m_UseCard->SetSize(0.f, 0.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
	
}

void CPlayerLogHUDWidget::AiDrawLog()
{
	m_PlayerImage->SetTexture("��ǻ�͵�ο�α�", TEXT("log/��ǻ�͵�ο�α�.png"));
	m_UseCard->SetSize(0.f, 0.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
}

void CPlayerLogHUDWidget::AiUseLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("��ǻ�ͻ��α�", TEXT("log/��ǻ�ͻ��α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(306.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerDaeugLog(int HeroIndex, int CardIndex, int CardClass, int HeroIndex2, int CardIndex2, int CardClass2)
{
	m_PlayerImage->SetTexture("�÷��̾�����α�", TEXT("log/�÷��̾�����α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	CreateTex2(HeroIndex2, CardIndex2, CardClass2);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(65.f, 90.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerBackCardLog(int focus)
{
	m_PlayerImage->SetTexture("�÷��̾��α�", TEXT("log/�÷��̾��α�.png"));
	CreateTex(0, focus, 0);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerFocusLog(int focus)
{
	m_PlayerImage->SetTexture("�÷��̾����߷·α�", TEXT("log/�÷��̾����߷·α�.png"));
	CreateTex(0, focus, 0);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerRefreshLog()
{
	m_PlayerImage->SetTexture("�÷��̾�������α�", TEXT("log/�÷��̾�������α�.png"));
	m_UseCard->SetSize(0.f, 0.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerDrawLog()
{
	m_PlayerImage->SetTexture("�÷��̾��ο�α�", TEXT("log/�÷��̾��ο�α�.png"));
	m_UseCard->SetSize(0.f, 0.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerUseLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("�÷��̾���α�", TEXT("log/�÷��̾���α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerJaegiLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("�÷��̾����α�", TEXT("log/�÷��̾����α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::AiJaegiLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("��ǻ�����α�", TEXT("log/��ǻ�����α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::PlayerBurnLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("�÷��̾�����α�", TEXT("log/�÷��̾�����α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}

void CPlayerLogHUDWidget::AiBurnLog(int HeroIndex, int CardIndex, int CardClass)
{
	m_PlayerImage->SetTexture("��ǻ�͹����α�", TEXT("log/��ǻ�͹����α�.png"));
	CreateTex(HeroIndex, CardIndex, CardClass);
	m_UseCard->SetSize(65.f, 90.f);
	m_TargetCard->SetSize(0.f, 0.f);
	m_TargetCard->SetPos(169.f, 12.f);
	m_UseCard->SetPos(28.f, 12.f);
}
