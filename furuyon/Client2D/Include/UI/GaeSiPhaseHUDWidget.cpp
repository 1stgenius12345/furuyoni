#include "GaeSiPhaseHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
#include "../Object/BuildingCard.h"
#include "Scene/SceneManager.h"
#include "../SceneMode/GodSelectScene.h"
#include "../SceneMode/StageScene.h"
#include "../SceneMode/MainScene.h"
#include "../SceneMode/StartScene.h"
#include "../ClientManager.h"
CGaeSiPhaseHUDWidget::CGaeSiPhaseHUDWidget() :
	m_Open(false),
	m_Close(false),
	m_OpenStartCheck(false),
	m_GameMapObj(nullptr),
	m_AttackCard(nullptr),
	m_BuildingCard(nullptr),
	m_valuex(0),
	m_valuey(0),
	m_Nab(0),
	m_Chozo(0),
	m_Type(GameMapButtonType::None),
	m_Hide(false),
	m_firstSellectCard(nullptr),
	m_secondSellectCard(nullptr),
	m_TempCard(nullptr)
{
}

CGaeSiPhaseHUDWidget::CGaeSiPhaseHUDWidget(const CGaeSiPhaseHUDWidget& widget)
{
}

CGaeSiPhaseHUDWidget::~CGaeSiPhaseHUDWidget()
{
}

bool CGaeSiPhaseHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_DrawButton = CreateWidget<CButton>("Draw");
	m_DrawButton->SetPos(Center.x - 520.f, Center.y - Center.y * 2.f);
	
	m_DrawButton->SetStateTint(Button_State::Normal, 1.2f, 1.2f, 1.2f, 1.f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.4f, 1.4f, 1.4f, 1.f);
	m_DrawButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);

	m_DrawButton->SetSize(236.f , 236.f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "draw_default", TEXT("button/draw_default.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "draw_Click", TEXT("button/draw_Click.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "draw_default", TEXT("button/draw_default.png"));
	m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::DrawButton);
	m_DrawButton->SetZOrder(5);
	//m_DrawButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_DrawButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_RefreshButton = CreateWidget<CButton>("Refresh");
	m_RefreshButton->SetPos(Center.x+150.f, Center.y - Center.y * 2.f);
	m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_RefreshButton->SetSize(236.f , 236.f );
	m_RefreshButton->SetStateTexture(Button_State::Normal, "refresh_default", TEXT("button/refresh_default.png"));
	m_RefreshButton->SetStateTexture(Button_State::MouseOn, "refresh_Click", TEXT("button/refresh_Click.png"));
	m_RefreshButton->SetStateTexture(Button_State::Click, "refresh_default", TEXT("button/refresh_default.png"));
	m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::RefreshButton);
	m_RefreshButton->SetZOrder(5);

	
	m_HideButton = CreateWidget<CButton>("m_HideButton");
	m_HideButton->SetPos(Center.x*1.5f, Center.y /4.f);
	m_HideButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_HideButton->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_HideButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_HideButton->SetSize(0.f, 0.f);
	m_HideButton->SetStateTexture(Button_State::Normal, "숨기기", TEXT("button/숨기기.png"));
	m_HideButton->SetStateTexture(Button_State::MouseOn, "숨기기", TEXT("button/숨기기.png"));
	m_HideButton->SetStateTexture(Button_State::Click, "숨기기", TEXT("button/숨기기.png"));
	m_HideButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::HideButton);
	m_HideButton->SetZOrder(5);


	m_OraNumberWidget = CreateWidget<CNumberWidget>("m_OraNumberWidget");
	m_OraNumberWidget->SetPos(Center.x - 500.f, Center.y - Center.y * 2.3f);
	m_OraNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
	m_OraNumberWidget->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	m_OraNumberWidget->SetNumber(0);
	m_OraNumberWidget->SetFrameCount(10, 4);
	m_OraNumberWidget->SetZOrder(8);

	m_LifeNumberWidget = CreateWidget<CNumberWidget>("m_LifeNumberWidget");
	
	m_LifeNumberWidget->SetPos(Center.x + 250.f, Center.y - Center.y * 2.3f);
	m_LifeNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
	m_LifeNumberWidget->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	m_LifeNumberWidget->SetNumber(0);
	m_LifeNumberWidget->SetFrameCount(10, 4);
	m_LifeNumberWidget->SetZOrder(8);


	m_Arrow = CreateWidget<CImage>("Arrow");
	m_Arrow->SetTexture("오른쪽", TEXT("button/오른쪽.png"));
	m_Arrow->SetPos(720.f-192.f, 360.f);
	m_Arrow->SetSize(0.f, 0.f);

	m_Arrow->SetColorTint(1.f, 1.f, 1.f, 0.f);




	//m_RefreshButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_RefreshButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_DrawButton->SetSize(236.f / 500.f, 236.f / 500.f);
	m_RefreshButton->SetSize(236.f / 500.f, 236.f / 500.f);

	return true;
}

void CGaeSiPhaseHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_Open)
	{
		Open(DeltaTime);
		if (m_Type == GameMapButtonType::CardBurn)
		{
			int  tempintvalue = 0;
			std::vector<CSharedPtr<CCard>> temphand = m_GameMapObj->GetPlayer1VecHand();
			for (int i = 0; i < temphand.size(); ++i)
			{
				if (temphand[i]->GetCardType() != Card_Type::Attack)
				{
					if (temphand[i]->GetSelect())
						++tempintvalue;
				}
			}
			if (tempintvalue == 0)
				m_firstSellectCard = nullptr;
			else if (tempintvalue == 1)
			{
				for (int i = 0; i < temphand.size(); ++i)
				{
					if (temphand[i]->GetCardType() != Card_Type::Attack)
					{
						if (temphand[i]->GetSelect())
							m_firstSellectCard = temphand[i];
					}
				}
			}
			else if (tempintvalue == 2)
			{
				for (int i = 0; i < temphand.size(); ++i)
				{
					if (temphand[i]->GetCardType() != Card_Type::Attack)
					{
						if (temphand[i]->GetSelect())
						{
							if (m_firstSellectCard != temphand[i])
							{
								
								m_firstSellectCard = temphand[i];
								m_firstSellectCard->UnSellectTextureSetting();
								m_firstSellectCard->SetSelect(false);
								break;
							}
						}
						
					}
				}
			}
		}
		if (m_Type == GameMapButtonType::Player1Hero8card4)
		{
			if(m_firstSellectCard)
			{
				m_OraNumberWidget->SetNumber(38);
				m_OraNumberWidget->SetNumberSize(150.f / 2.f, 134.f / 2.f);
				m_OraNumberWidget->SetPos(m_firstSellectCard->GetRelativePos().x, m_firstSellectCard->GetRelativePos().y);
			}
			else
			{
				m_OraNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);
				
				
			}
			if (m_secondSellectCard)
			{
				m_LifeNumberWidget->SetNumber(39);
				m_LifeNumberWidget->SetNumberSize(150.f / 2.f, 134.f / 2.f);
				m_LifeNumberWidget->SetPos(m_secondSellectCard->GetRelativePos().x, m_secondSellectCard->GetRelativePos().y);
			}
			else
			{
			
				m_LifeNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);
				
				
			}
			int temp = 0;
			std::vector<CSharedPtr<CCard>> vectempUse = m_GameMapObj->GetPlayer1VecUse();
			std::vector<CSharedPtr<CCard>> vectempBack = m_GameMapObj->GetPlayer1VecBack();
			for (int i = 0; i < vectempUse.size(); ++i)
			{	
				if (vectempUse[i]->GetSelect())
				{
					++temp;
				}
			}
			for (int i = 0; i < vectempBack.size(); ++i)
			{
				if (vectempBack[i]->GetSelect())
				{
					++temp;
				}
			}
			if (temp == 0)
			{
				m_firstSellectCard = nullptr;
				m_secondSellectCard = nullptr;
			}
			else if (temp == 1)
			{
				for (int i = 0; i < vectempUse.size(); ++i)
				{
					if (vectempUse[i]->GetSelect())
					{
						m_firstSellectCard = vectempUse[i];
					}
				}
				for (int i = 0; i < vectempBack.size(); ++i)
				{
					if (vectempBack[i]->GetSelect())
					{
						m_firstSellectCard = vectempBack[i];
					}
				}
				m_secondSellectCard = nullptr;
			}
			else if (temp == 2)
			{
				for (int i = 0; i < vectempUse.size(); ++i)
				{
					if (vectempUse[i]->GetSelect())
					{
						if (m_firstSellectCard != vectempUse[i])
						{
							m_secondSellectCard = vectempUse[i];
						}
							
					}
				}
				for (int i = 0; i < vectempBack.size(); ++i)
				{
					if (vectempBack[i]->GetSelect())
					{
						if (m_firstSellectCard != vectempBack[i])
							m_secondSellectCard = vectempBack[i];
					}
				}
			}
			else if (temp == 3)
			{
				for (int i = 0; i < vectempUse.size(); ++i)
				{
					if (vectempUse[i]->GetSelect())
					{
						if (m_firstSellectCard != vectempUse[i] && m_secondSellectCard != vectempUse[i])
						{	
							m_firstSellectCard->UnSellectTextureSetting();
							m_firstSellectCard->SetSelect(false);
							m_firstSellectCard = m_secondSellectCard;
							m_secondSellectCard = vectempUse[i];
							
							return;
						}
						
					}
				}
				for (int i = 0; i < vectempBack.size(); ++i)
				{
					if (vectempBack[i]->GetSelect())
					{
						if (m_firstSellectCard != vectempBack[i] && m_secondSellectCard != vectempBack[i])
						{
							m_firstSellectCard->UnSellectTextureSetting();
							m_firstSellectCard->SetSelect(false);
							m_firstSellectCard = m_secondSellectCard;
							m_secondSellectCard = vectempBack[i];
							return;
						}
					}
				}
			}


		}
	}
	else if (m_Close)
	{
		Close(DeltaTime);

		
		
	}
}

void CGaeSiPhaseHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CGaeSiPhaseHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CGaeSiPhaseHUDWidget* CGaeSiPhaseHUDWidget::Clone()
{
	return new CGaeSiPhaseHUDWidget(*this);
}

void CGaeSiPhaseHUDWidget::OpenWidget()
{
	m_GameMapObj->CardUseCloseWidget();
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	if (m_Type == GameMapButtonType::Player1Daeung)
	{
		
		std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
		for (int i = 0; i < vechand.size(); ++i)
		{
			vechand[i]->SetMove(false);
			vechand[i]->SetSelect(false);
		}
		std::vector<CSharedPtr<CCard>> vechero = m_GameMapObj->GetPlayer1Hero();
		for (int i = 0; i < vechero.size(); ++i)
		{
			vechero[i]->SetMove(false);
			vechero[i]->SetSelect(false);
		}
	
	}
	
	m_HideButton->SetSize(513.f / 4.f, 195.f / 4.f);
	//m_DrawButton->SetSize(236.f / 500.f, 236.f / 500.f);
	//m_RefreshButton->SetSize(236.f / 500.f, 236.f / 500.f);
	m_DrawButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_RefreshButton->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_Open = true;
	m_Close = false;
	m_OpenStartCheck = true;
	m_Hide = false;
}

void CGaeSiPhaseHUDWidget::CloseWidget()
{
	m_Arrow->SetSize(0.f, 0.f);

	m_Arrow->SetColorTint(1.f, 1.f, 1.f, 0.f);

	m_DrawButton->SetMouseOnCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winbutton);
	m_RefreshButton->SetMouseOnCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winbutton);
	m_OraNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);
	m_LifeNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);

	m_HideButton->SetSize(0.f, 0.f);
	m_DrawButton->SetSize(236.f / 500.f, 236.f / 500.f);
	m_RefreshButton->SetSize(236.f / 500.f, 236.f / 500.f);
	

	m_GameMapObj->SetSelectTiming(false);
	m_Open = false;
	m_OpenStartCheck = false;
	m_Close = true;
	
}

void CGaeSiPhaseHUDWidget::StartClick()
{
}

void CGaeSiPhaseHUDWidget::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	Vector2 StartPoint = Vector2(Center.x-50.f ,  Center.y - 100.f);
	StartPoint = StartPoint-m_DrawButton->GetPos()  ;
	std::vector<CSharedPtr<CCard>> vecDaueg = m_GameMapObj->GetPlayer1DauegCard();

	if (StartPoint.y >= 0.05f && m_OpenStartCheck)
	{
		
		
		m_DrawButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_RefreshButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_OraNumberWidget->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_LifeNumberWidget->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));




	}
	else
	{
		m_OraNumberWidget->SetPos(Center.x - 500.f,150.f);
		m_LifeNumberWidget->SetPos(Center.x + 250.f, 150.f);
		std::vector<CSharedPtr<CCard>> vecHand = m_GameMapObj->GetPlayer1Hand();
		int tempdaueg = 0;
		for (int i = 0; i < vecHand.size(); ++i)
		{
			if (vecHand[i]->GetSelect())
			{	
				++tempdaueg;
				if (m_DaeugCard == vecHand[i])
				{

				}
				else
				{
					if (m_DaeugCard)
					{
						m_DaeugCard->SetSelect(false);
						m_DaeugCard->UnSellectTextureSetting();
					}
					m_DaeugCard = vecHand[i];
				}
				
			}
		}
		if (tempdaueg == 0)
			m_DaeugCard = nullptr;
		std::vector<CSharedPtr<CCard>> vecHero = m_GameMapObj->GetPlayer1Hero();
		for (int i = 0; i < vecHero.size(); ++i)
		{
			if (vecHero[i]->GetSelect())
			{
				++tempdaueg;
				if (m_DaeugCard == vecHero[i])
				{

				}
				else
				{
					if (m_DaeugCard)
					{
						m_DaeugCard->SetSelect(false);
						m_DaeugCard->UnSellectTextureSetting();
					}
					m_DaeugCard = vecHero[i];
				}

			}
		}
		if (tempdaueg == 0)
			m_DaeugCard = nullptr;

		m_OpenStartCheck = false;
	}
	




}

void CGaeSiPhaseHUDWidget::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	
	Vector2 StartPoint = Vector2(Center.x - 250.f, Center.y - Center.y * 2.f);
	StartPoint = StartPoint - m_DrawButton->GetPos();

	if (StartPoint.y <= 0.f)
	{
		
		m_DrawButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_RefreshButton->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_OraNumberWidget->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
		m_LifeNumberWidget->AddPos(StartPoint * Vector2(0, DeltaTime * 10.f + DeltaTime * 5.f));
	}
}

void CGaeSiPhaseHUDWidget::ClickForwardBytype(GameMapButtonType type, class CCard* card,int x, int y)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	std::vector<CSharedPtr<CCard>> tempvec = m_GameMapObj->GetPlayer1VecUse();
	m_Type = type;
	m_GameMapObj->SetSelectTiming(true);
	switch (type)
	{
	case GameMapButtonType::None:
		break;
	case GameMapButtonType::Gaeshi:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "draw_default", TEXT("button/draw_default.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "draw_Click", TEXT("button/draw_Click.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "draw_default", TEXT("button/draw_default.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::DrawButton);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "refresh_default", TEXT("button/refresh_default.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "refresh_Click", TEXT("button/refresh_Click.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "refresh_default", TEXT("button/refresh_default.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::RefreshButton);
		break;
	case GameMapButtonType::Building:
		m_BuildingCard = (CBuildingCard*)card;
		m_DrawButton->SetStateTexture(Button_State::Normal, "NabShieldButton", TEXT("button/NabShieldButton.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "NabShieldButton1", TEXT("button/NabShieldButton1.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "NabShieldButton1", TEXT("button/NabShieldButton1.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::ShieldNab);
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "NabDustButton", TEXT("button/NabDustButton.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "NabDustButton1", TEXT("button/NabDustButton1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "NabDustButton1", TEXT("button/NabDustButton1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::DustNab);
		m_Nab = x;
		if (m_GameMapObj->GetPlayer1Shiled() <= 0 && m_GameMapObj->GetDust() <= 0)
		{
			m_Nab = 0;
			// 더이상 봉납할 벚꽃이 없다.
			((CBuildingCard*)card)->SetNabPoint(0);
			CloseBuildingWidget();
		}
		break;
	case GameMapButtonType::Attacked:
		break;
	case GameMapButtonType::Chozo:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "draw_ora", TEXT("button/draw_ora.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "draw_ora1", TEXT("button/draw_ora1.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "draw_ora1", TEXT("button/draw_ora1.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::ChozoOra);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "draw_life", TEXT("button/draw_life.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "draw_life1", TEXT("button/draw_life1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "draw_life1", TEXT("button/draw_life1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::ChozoLife);
		m_Chozo = x;
		break;
	case GameMapButtonType::Player1Win:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTint(Button_State::Normal, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTint(Button_State::Click, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "승리", TEXT("button/승리.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "승리", TEXT("button/승리.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "승리", TEXT("button/승리.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winbutton);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "결과창", TEXT("button/결과창.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "결과창1", TEXT("button/결과창1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "결과창1", TEXT("button/결과창1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winResult);
		break;
	case GameMapButtonType::Player2Win:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTint(Button_State::Normal, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTint(Button_State::Click, 1.2f, 1.2f, 1.2f, 1.f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "패배", TEXT("button/패배.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "패배", TEXT("button/패배.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "패배", TEXT("button/패배.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winbutton);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "결과창", TEXT("button/결과창.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "결과창1", TEXT("button/결과창1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "결과창1", TEXT("button/결과창1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1winResult);
		break;
	case GameMapButtonType::Player1AttackSelect:
		m_AttackCard = (CAttackCard*)card;
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "오라데미지", TEXT("button/오라데미지.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "오라데미지1", TEXT("button/오라데미지1.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "오라데미지1", TEXT("button/오라데미지1.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1AttackSelectShield);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "라이프데미지", TEXT("button/라이프데미지.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "라이프데미지1", TEXT("button/라이프데미지1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "라이프데미지1", TEXT("button/라이프데미지1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1AttackSelectLife);
		m_OraNumberWidget->SetPos(Center.x - 500.f, Center.y - Center.y * 2.3f);
		m_LifeNumberWidget->SetPos(Center.x + 250.f, Center.y - Center.y * 2.3f);
		m_OraNumberWidget->SetNumberSize(150.f*1.5f, 134.f * 1.5f);
		m_LifeNumberWidget->SetNumberSize(150.f * 1.5f, 134.f * 1.5f);
		if (m_valuex == -1)
			m_OraNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
		if (m_valuey == -1)
			m_LifeNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
		m_valuex = x;
		m_valuey = y;
		m_OraNumberWidget->SetNumber(x);
		m_LifeNumberWidget->SetNumber(y);
		break;
	case GameMapButtonType::Player1Daeung:
		break;
	case GameMapButtonType::Player1DustRange:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
		m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
		m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
		m_DrawButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
		m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);	m_DrawButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "더스트", TEXT("button/더스트.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "더스트", TEXT("button/더스트.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "더스트", TEXT("button/더스트.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::DustToRange);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "간격", TEXT("button/간격.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "간격", TEXT("button/간격.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "간격", TEXT("button/간격.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::RangeToDust);
		m_DrawButton->SetMouseOnCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::MouseOnLeftForRightArrow);
		m_RefreshButton->SetMouseOnCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::MouseOnRightForLeftArrow);
		break;
	case GameMapButtonType::Player1Hero3Card6:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "무음벽", TEXT("button/무음벽.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "무음벽1", TEXT("button/무음벽1.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "무음벽1", TEXT("button/무음벽1.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Hero3Card6Left);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "오라데미지", TEXT("button/오라데미지.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "오라데미지1", TEXT("button/오라데미지1.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "오라데미지1", TEXT("button/오라데미지1.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Hero3Card6Right);
		m_OraNumberWidget->SetNumberSize(150.f * 1.5f, 134.f * 1.5f);
		m_LifeNumberWidget->SetNumberSize(150.f * 1.5f, 134.f * 1.5f);
		m_OraNumberWidget->SetPos(Center.x - 500.f, Center.y - Center.y * 2.3f);
		m_LifeNumberWidget->SetPos(Center.x + 250.f, Center.y - Center.y * 2.3f);
		if (m_valuex == -1)
			m_OraNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
		if (m_valuey == -1)
			m_LifeNumberWidget->SetNumberSize(150.f / 50.f, 134.f / 50.f);
		m_valuex = x;
		m_BuildingCard = (CBuildingCard*)card;
		m_OraNumberWidget->SetNumber(m_BuildingCard->GetNabpoint());
		m_LifeNumberWidget->SetNumber(m_GameMapObj->GetPlayer1Shiled());
		break;
	case GameMapButtonType::Player1Hero8card3:
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
		m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
		m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
		m_DrawButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
		m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);	
		m_DrawButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
		m_DrawButton->SetStateTexture(Button_State::Normal, "Hero8Card3Left", TEXT("button/Hero8Card3Left.png"));
		m_DrawButton->SetStateTexture(Button_State::MouseOn, "Hero8Card3Left", TEXT("button/Hero8Card3Left.png"));
		m_DrawButton->SetStateTexture(Button_State::Click, "Hero8Card3Left", TEXT("button/Hero8Card3Left.png"));
		m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Hero8Card3Left);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "Hero8Card3Right", TEXT("button/Hero8Card3Right.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "Hero8Card3Right", TEXT("button/Hero8Card3Right.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "Hero8Card3Right", TEXT("button/Hero8Card3Right.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Heor8Card3Right);
		break;
	case GameMapButtonType::Player1Hero8card4:
		m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
		m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
		m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
		m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
		m_RefreshButton->SetStateTexture(Button_State::Normal, "Hero8Card4", TEXT("button/Hero8Card4.png"));
		m_RefreshButton->SetStateTexture(Button_State::MouseOn, "선택완료", TEXT("button/선택완료.png"));
		m_RefreshButton->SetStateTexture(Button_State::Click, "Hero8Card4", TEXT("button/Hero8Card4.png"));
		m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Hero8Card4);
		m_GameMapObj->SettingPlayer1UseBacksellecttime();
	
		m_TempCard = tempvec.back();
		tempvec.pop_back();
		m_GameMapObj->SetPlayer1VecUse(tempvec);
		break;
	case GameMapButtonType::End:
		break;
	default:
		break;
	}

	OpenWidget();
}

void CGaeSiPhaseHUDWidget::ClickDaeung(class CAttackCard* card,bool b)
{
	if (b == false)
	{
		Player1DauegExit();
		return;
	}
		

	m_Type = GameMapButtonType::Player1Daeung;
	m_GameMapObj->SetSelectTiming(true);
	m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
	m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
	m_DrawButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_DrawButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "대응", TEXT("button/대응.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "대응1", TEXT("button/대응1.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "대응1", TEXT("button/대응1.png"));
	m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1Daueg);
	m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_RefreshButton->SetStateTexture(Button_State::Normal, "넘기기", TEXT("button/넘기기.png"));
	m_RefreshButton->SetStateTexture(Button_State::MouseOn, "넘기기1", TEXT("button/넘기기1.png"));
	m_RefreshButton->SetStateTexture(Button_State::Click, "넘기기1", TEXT("button/넘기기1.png"));
	m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::Player1DauegExit);
	m_AttackCard = card;
	
	OpenWidget();
}

void CGaeSiPhaseHUDWidget::ClickCardBurn(int index)
{
	m_Type = GameMapButtonType::CardBurn;
	m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
	m_RefreshButton->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_RefreshButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.2f);
	m_RefreshButton->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_DrawButton->SetStateTint(Button_State::Normal, 1.2f, 1.2f, 1.2f, 1.f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.2f, 1.2f, 1.2f, 1.f);
	m_DrawButton->SetStateTint(Button_State::Click, 1.2f, 1.2f, 1.2f, 1.f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "notattackcard", TEXT("button/notattackcard.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "notattackcard", TEXT("button/notattackcard.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "notattackcard", TEXT("button/notattackcard.png"));
	m_DrawButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::CardBurnLeft);
	m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);
	m_RefreshButton->SetStateTexture(Button_State::Normal, "선택완료", TEXT("button/선택완료.png"));
	m_RefreshButton->SetStateTexture(Button_State::MouseOn, "선택완료", TEXT("button/선택완료.png"));
	m_RefreshButton->SetStateTexture(Button_State::Click, "선택완료", TEXT("button/선택완료.png"));
	m_RefreshButton->SetClickCallback<CGaeSiPhaseHUDWidget>(this, &CGaeSiPhaseHUDWidget::CardBurnRight);
	m_firstSellectCard = nullptr;
	m_GameMapObj->SetSelectTiming(true);
	OpenWidget();
}

void CGaeSiPhaseHUDWidget::DrawButton()
{
	int tempChozo = m_GameMapObj->DrawACard(2);

	// 메인 스타트
	m_GameMapObj->DrawSound();

	if(tempChozo >= 1)
		ClickForwardBytype(GameMapButtonType::Chozo, nullptr, tempChozo, 0);
	else
	{
		m_GameMapObj->SetPlayer1GaesiEnd(true);

		CloseWidget();
	}
	m_GameMapObj->LogCreate(nullptr, nullptr,0,3);
}

void CGaeSiPhaseHUDWidget::RefreshButton()
{
	m_GameMapObj->RefreshSound();
	m_GameMapObj->RefreshDeck();
	DrawButton();

	m_GameMapObj->LogCreate(nullptr, nullptr, 0, 4);
}

void CGaeSiPhaseHUDWidget::ClickOra()
{
	if (m_GameMapObj->GetDust() <= 0 || m_GameMapObj->GetPlayer1Shiled() >= 5)
	{

	}
	else
	{
		m_GameMapObj->AddDust(-1);
		m_GameMapObj->AddPlayer1Shiled(1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		return;
	}




}

void CGaeSiPhaseHUDWidget::ClickMana()
{
	if (m_GameMapObj->GetPlayer1Shiled() <= 0)
	{

	}
	else
	{

		m_GameMapObj->AddPlayer1Shiled(-100);
		m_GameMapObj->AddPlayer1Mana(1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		return;
	}
}

void CGaeSiPhaseHUDWidget::ShieldNab()
{
	std::vector<CSharedPtr<CCard>> vecUse = m_GameMapObj->GetPlayer1Buildingvector();
	CCard* tempcard = vecUse.back();
	CBuildingCard* tempSpell = (CBuildingCard*)tempcard;
	
	if (m_GameMapObj->GetPlayer1Shiled() <= 0 && m_GameMapObj->GetDust() <= 0)
	{
		// 더이상 봉납할 벚꽃이 없다.
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);

		CloseBuildingWidget();
	}
	if (m_GameMapObj->GetPlayer1Shiled() <= 0)
		return;
		
		
	if (m_Nab > 0)
	{
		m_Nab--;
		m_GameMapObj->AddPlayer1Shiled(-100);
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
		if (m_GameMapObj->GetPlayer1Shiled() <= 0 && m_GameMapObj->GetDust() <= 0)
		{
			// 벚꽃이 봉납한다.
			tempSpell->SetNabPoint(tempSpell->GetNab()-m_Nab);
		
			CloseBuildingWidget();
		}
		if (m_Nab == 0)
		{
			// 벚꽃이 봉납한다.
			tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
			CloseBuildingWidget();
		}
	}
	else
	{
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
		CloseBuildingWidget();
	}


		
}

void CGaeSiPhaseHUDWidget::DustNab()
{	

	std::vector<CSharedPtr<CCard>> vecUse = m_GameMapObj->GetPlayer1Buildingvector();
	CCard* tempcard = vecUse.back();
	CBuildingCard* tempSpell = (CBuildingCard*)tempcard;
	
	if (m_GameMapObj->GetPlayer1Shiled() <= 0 && m_GameMapObj->GetDust() <= 0)
	{
		// 벚꽃이 봉납한다.
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
		CloseBuildingWidget();
	}
	if (m_GameMapObj->GetDust() <= 0)
		return;



	if (m_Nab > 0)
	{
		m_Nab--;
		m_GameMapObj->AddDust(-1);
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
		if (m_GameMapObj->GetPlayer1Shiled() <= 0 && m_GameMapObj->GetDust() <= 0)
		{
			tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
			// 벚꽃이 봉납한다.
			CloseBuildingWidget();
		}
		if (m_Nab == 0)
		{
			// 벚꽃이 봉납한다.
			tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
			CloseBuildingWidget();
		}
	}
	else
	{
		tempSpell->SetNabPoint(tempSpell->GetNab() - m_Nab);
		CloseBuildingWidget();
	}
		
}

void CGaeSiPhaseHUDWidget::CloseBuildingWidget()
{
	m_HideButton->SetSize(0.f, 0.f);
	m_GameMapObj->Player1BuildingUseAnimation();
	m_GameMapObj->UseBuildingBYIndex(m_BuildingCard->GetPlayer(), m_BuildingCard);
	m_GameMapObj->Player1BuildingSetPos();
	m_GameMapObj->SetSelectTiming(false);
	m_Open = false;
	m_OpenStartCheck = false;
	m_Close = true;
}

void CGaeSiPhaseHUDWidget::ChozoOra()
{	
	if (m_GameMapObj->GetPlayer1Shiled() <= 0)
		return;

	if (m_Chozo > 0)
	{
		m_Chozo--;
		m_GameMapObj->AddPlayer1Shiled(-100);
		m_GameMapObj->AddDust(1);
		if (m_Chozo == 0)
		{
			CloseWidget();
			
			m_GameMapObj->SetPlayer1GaesiEnd(true);
		}
	}
}

void CGaeSiPhaseHUDWidget::ChozoLife()
{
	if (m_GameMapObj->GetPlayer1Life() <= 0)
	{
		CloseWidget();
	}
	

	if (m_Chozo > 0)
	{
		m_Chozo--;
		m_GameMapObj->AddPlayer1Life(-1);
		m_GameMapObj->AddPlayer1Mana(1);
		if (m_Chozo == 0)
		{
			CloseWidget();
			m_GameMapObj->SetPlayer1GaesiEnd(true);
		}
	}
}

void CGaeSiPhaseHUDWidget::Player1winbutton()
{
}

void CGaeSiPhaseHUDWidget::Player1winResult()
{	
	if (CClientManager::GetInst()->GetAiIndex() > 0)
	{
		CSceneManager::GetInst()->CreateNextScene();

		CSceneManager::GetInst()->SetSceneMode<CStageScene>(false);
	}
	else
	{
		CSceneManager::GetInst()->CreateNextScene();

		CSceneManager::GetInst()->SetSceneMode<CStartScene>(false);
	}
	
}

void CGaeSiPhaseHUDWidget::Player2winButton()
{
}

void CGaeSiPhaseHUDWidget::Player2winResult()
{
}

void CGaeSiPhaseHUDWidget::Player1AttackSelectShield()
{
	m_GameMapObj->AddPlayer1Shiled(-m_valuex);
	m_GameMapObj->AddDust(m_valuex);
	CloseWidget();
	m_GameMapObj->AttackEndEffect(m_AttackCard->GetPlayer(), m_AttackCard->GetHeroIndex(), m_AttackCard->GetCardIndex(), m_AttackCard->GetCardClass());
	
}

void CGaeSiPhaseHUDWidget::Player1AttackSelectLife()
{	
	m_GameMapObj->SetPlayer1Teum(true);
	m_GameMapObj->AddPlayer1Life(-m_valuey);
	m_GameMapObj->AddPlayer1Mana(m_valuey);
	CloseWidget();
	m_GameMapObj->AttackEndEffect(m_AttackCard->GetPlayer(), m_AttackCard->GetHeroIndex(), m_AttackCard->GetCardIndex(), m_AttackCard->GetCardClass());
	
}

void CGaeSiPhaseHUDWidget::Player1Daueg()
{
	if (m_DaeugCard != nullptr)
	{
	
		
		m_DaeugCard->SetSelect(false);
		m_DaeugCard->UnSellectTextureSetting();
		m_DaeugCard->SetSelectTime(false);
		m_GameMapObj->PushAnimationCard(m_AttackCard, 1);
		m_GameMapObj->AttackonTheStack(m_AttackCard);
		m_GameMapObj->Player1CardManaCost(m_DaeugCard);
		m_GameMapObj->PushAnimationCard(m_DaeugCard,0);
		m_GameMapObj->UseCard(m_DaeugCard);
		m_DaeugCard->SetDaeungTriger(true);
		m_GameMapObj->Player1DauegExit(m_DaeugCard);
		m_GameMapObj->LogCreate(m_AttackCard, nullptr, 0, 2);
		m_GameMapObj->LogCreate(m_DaeugCard, m_AttackCard, 0, 1);
		m_DaeugCard = nullptr;
		m_AttackCard = nullptr;
		CloseWidget();
	}
}

void CGaeSiPhaseHUDWidget::Player1DauegExit()
{
	CloseWidget();


	m_GameMapObj->AttackonTheStack(m_AttackCard);
	m_GameMapObj->LogCreate(m_AttackCard,nullptr,0,2);
	m_GameMapObj->Player1DauegExit(nullptr);
}

void CGaeSiPhaseHUDWidget::MouseOnLeftForRightArrow()
{
	m_Arrow->SetSize(224.f, 118.f);
	m_Arrow->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Arrow->SetTexture("오른쪽", TEXT("button/오른쪽.png"));

}

void CGaeSiPhaseHUDWidget::MouseOnRightForLeftArrow()
{
	m_Arrow->SetSize(224.f, 118.f);
	m_Arrow->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Arrow->SetTexture("왼쪽", TEXT("button/왼쪽.png"));
}

void CGaeSiPhaseHUDWidget::DustToRange()
{
	if (m_GameMapObj->GetDust() > 0 && m_GameMapObj->GetRange() < 10)
	{
		m_GameMapObj->AddDust(-1);
		m_GameMapObj->AddRange(1);
	}
	CloseWidget();
}

void CGaeSiPhaseHUDWidget::RangeToDust()
{
	if (m_GameMapObj->GetRange() > 0)
	{
		m_GameMapObj->AddDust(1);
		m_GameMapObj->AddRange(-1);
	}
	CloseWidget();
}

void CGaeSiPhaseHUDWidget::Hero3Card6Left()
{
	if (m_BuildingCard->GetNabpoint() <= 0)
		return;


	m_BuildingCard->AddNabPoint(-1);
	++m_valuex;
	m_OraNumberWidget->SetNumber(m_BuildingCard->GetNabpoint());
	m_LifeNumberWidget->SetNumber(m_GameMapObj->GetPlayer1Shiled());
	if (m_valuex == 0)
	{
		CloseWidget();
		m_GameMapObj->Player1BuildingZeroCheck();
	}
		
}

void CGaeSiPhaseHUDWidget::Hero3Card6Right()
{
	if (m_GameMapObj->GetPlayer1Shiled() <= 0)
		return;
	m_GameMapObj->AddPlayer1Shiled(-100);
	++m_valuex;
	m_OraNumberWidget->SetNumber(m_BuildingCard->GetNabpoint());
	m_LifeNumberWidget->SetNumber(m_GameMapObj->GetPlayer1Shiled());
	if (m_valuex == 0)
	{
		m_GameMapObj->Player1BuildingZeroCheck();
		CloseWidget();
	}
		
}

void CGaeSiPhaseHUDWidget::HideButton()
{
	m_GameMapObj->HideSound();
	if (m_Hide)
	{
		m_GameMapObj->AnimationHide();
		m_HideButton->SetStateTexture(Button_State::Normal, "숨기기", TEXT("button/숨기기.png"));
		m_HideButton->SetStateTexture(Button_State::MouseOn, "숨기기", TEXT("button/숨기기.png"));
		m_HideButton->SetStateTexture(Button_State::Click, "숨기기", TEXT("button/숨기기.png"));
		m_DrawButton->SetSize(236.f * 1.5f, 236.f * 1.5f);

		if(m_Type != GameMapButtonType::Player1Hero8card4)
			m_RefreshButton->SetSize(236.f * 1.5f, 236.f * 1.5f);

		if (m_Type == GameMapButtonType::Player1AttackSelect)
		{
			m_OraNumberWidget->SetNumberSize(150.f * 1.5f, 134.f * 1.5f);
			m_LifeNumberWidget->SetNumberSize(150.f * 1.5f, 134.f * 1.5f);
		}
		
		if (m_Type == GameMapButtonType::Player1DustRange)
		{
			m_Arrow->SetSize(224.f, 118.f);
			m_Arrow->SetColorTint(1.f, 1.f, 1.f, 1.f);
		}
		
		m_Hide = false;
		
	}
	else
	{
		m_GameMapObj->AnimationHide();
		m_Arrow->SetSize(0.f, 0.f);
		m_Arrow->SetColorTint(1.f, 1.f, 1.f, 0.f);
		m_DrawButton->SetSize(236.f / 500.f, 236.f / 500.f);
		m_RefreshButton->SetSize(236.f / 500.f, 236.f / 500.f);
		m_OraNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);
		m_LifeNumberWidget->SetNumberSize(150.f / 500.f, 134.f / 500.f);
		m_HideButton->SetStateTexture(Button_State::Normal, "보이기", TEXT("button/보이기.png"));
		m_HideButton->SetStateTexture(Button_State::MouseOn, "보이기", TEXT("button/보이기.png"));
		m_HideButton->SetStateTexture(Button_State::Click, "보이기", TEXT("button/보이기.png"));
		m_Hide = true;
	}
	
}

void CGaeSiPhaseHUDWidget::Hero8Card3Left()
{
	if (m_GameMapObj->GetPlayer1Mana() > 0 && m_GameMapObj->GetPlayer1Shiled() <= 4)
	{
		m_GameMapObj->AddPlayer1Mana(-1);
		m_GameMapObj->AddPlayer1Shiled(1);
	}
	CloseWidget();
}

void CGaeSiPhaseHUDWidget::Heor8Card3Right()
{
	if (m_GameMapObj->GetPlayer1Shiled() > 0 && m_GameMapObj->GetRange() < 10)
	{
		m_GameMapObj->AddPlayer1Shiled(-1);
		m_GameMapObj->AddRange(1);
	}
	CloseWidget();
}

void CGaeSiPhaseHUDWidget::Hero8Card4()
{
	m_GameMapObj->Hero8Card4(m_firstSellectCard,m_secondSellectCard);
	std::vector<CSharedPtr<CCard>> tempvec = m_GameMapObj->GetPlayer1VecUse();
	tempvec.push_back(m_TempCard);
	m_GameMapObj->SetPlayer1VecUse(tempvec);

	m_GameMapObj->SettingPlayer1UseBackUnSellecttime();
	CloseWidget();
}

void CGaeSiPhaseHUDWidget::CardBurnLeft()
{
}

void CGaeSiPhaseHUDWidget::CardBurnRight()
{
	if (m_firstSellectCard == nullptr)
	{
		return;
	}
	m_GameMapObj->Player1HandUnSellect();
	m_GameMapObj->Player1HandtoUse(m_firstSellectCard);
	CloseWidget();
}
