#include "MulrigunHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
#include "../Object/BuildingCard.h"
CMulrigunHUDWidget::CMulrigunHUDWidget() :
	m_Open(false),
	m_Close(false),
	m_OpenStartCheck(false),
	m_CloseEndCheck(false),
	m_firstCard(nullptr),
	m_SecondCard(nullptr),
	m_ThirdCard(nullptr),
	m_HandCardBurn(false)
{
}

CMulrigunHUDWidget::CMulrigunHUDWidget(const CMulrigunHUDWidget& widget)
{
}

CMulrigunHUDWidget::~CMulrigunHUDWidget()
{
}

bool CMulrigunHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_DrawButton = CreateWidget<CButton>("Phase");
	m_DrawButton->SetPos(565.f, -1100.f);
	m_DrawButton->SetStateTint(Button_State::Normal, 1.5f, 1.5f, 1.5f, 1.5f);
	m_DrawButton->SetStateTint(Button_State::MouseOn, 1.8f, 1.8f, 1.8f, 1.8f);
	m_DrawButton->SetStateTint(Button_State::Click, 1.5f, 1.5f, 1.5f, 1.5f);
	m_DrawButton->SetSize(353.f / 2.5f, 342.f/ 2.5f);
	m_DrawButton->SetStateTexture(Button_State::Normal, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetClickCallback<CMulrigunHUDWidget>(this, &CMulrigunHUDWidget::DrawButton);
	m_DrawButton->SetZOrder(5);

	m_Firstinfo = CreateWidget<CButton>("m_Firstinfo");
	m_Firstinfo->SetPos(600.f, -1050.f);
	m_Firstinfo->SetStateTint(Button_State::Normal, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Firstinfo->SetStateTint(Button_State::MouseOn, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Firstinfo->SetStateTint(Button_State::Click, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Firstinfo->SetSize(353.f / 3.f, 342.f / 3.f);
	m_Firstinfo->SetStateTexture(Button_State::Normal, "맨밑", TEXT("button/맨밑.png"));
	m_Firstinfo->SetStateTexture(Button_State::MouseOn, "맨밑", TEXT("button/맨밑.png"));
	m_Firstinfo->SetStateTexture(Button_State::Click, "맨밑", TEXT("button/맨밑.png"));
	
	m_Firstinfo->SetZOrder(5);

	m_Secondinfo = CreateWidget<CButton>("m_SecondCard");
	m_Secondinfo->SetPos(600.f, -1050.f);
	m_Secondinfo->SetStateTint(Button_State::Normal, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Secondinfo->SetStateTint(Button_State::MouseOn, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Secondinfo->SetStateTint(Button_State::Click, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Secondinfo->SetSize(353.f / 3.f, 342.f / 3.f);
	m_Secondinfo->SetStateTexture(Button_State::Normal, "맨밑두번째", TEXT("button/맨밑두번째.png"));
	m_Secondinfo->SetStateTexture(Button_State::MouseOn, "맨밑두번째", TEXT("button/맨밑두번째.png"));
	m_Secondinfo->SetStateTexture(Button_State::Click, "맨밑두번째", TEXT("button/맨밑두번째.png"));
	//m_Secondinfo->SetClickCallback<CMulrigunHUDWidget>(this, &CMulrigunHUDWidget::DrawButton);
	m_Secondinfo->SetZOrder(5);

	m_Thirdinfo = CreateWidget<CButton>("m_Thirdinfo");
	m_Thirdinfo->SetPos(600.f, -1050.f);
	m_Thirdinfo->SetStateTint(Button_State::Normal, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Thirdinfo->SetStateTint(Button_State::MouseOn, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Thirdinfo->SetStateTint(Button_State::Click, 1.5f, 1.5f, 1.5f, 1.5f);
	m_Thirdinfo->SetSize(353.f / 3.f, 342.f / 3.f);
	m_Thirdinfo->SetStateTexture(Button_State::Normal, "맨밑세번째", TEXT("button/맨밑세번째.png"));
	m_Thirdinfo->SetStateTexture(Button_State::MouseOn, "맨밑세번째", TEXT("button/맨밑세번째.png"));
	m_Thirdinfo->SetStateTexture(Button_State::Click, "맨밑세번째", TEXT("button/맨밑세번째.png"));
//	m_Thirdinfo->SetClickCallback<CMulrigunHUDWidget>(this, &CMulrigunHUDWidget::DrawButton);
	m_Thirdinfo->SetZOrder(5);
	//m_DrawButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_DrawButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");


	//m_RefreshButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	//m_RefreshButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");



	return true;
}

void CMulrigunHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);




	if (m_Open)
	{
		Open(DeltaTime);

	}
	else if (m_Close)
	{	
		Close(DeltaTime);
		int selectcount = 0;
		if (m_HandCardBurn)
		{
			// 어차피 선택한거 태우는건 저쪽가서 하면됨 여기서 굳이 순서 맞출필요없음 
		}
		else if (m_CloseEndCheck)
		{
			std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
			for (int i = 0; i < vechand.size(); ++i)
			{	
				if (!vechand[i]->GettLook())
				{
					vechand[i]->SetRelativePos(729.4f - (72.f * vechand.size()), 360.f, 0.f);
					vechand[i]->AddWorldPos(vechand[i]->GetRelativeScale().x * i + 10.f, 0.f, 0.f);
					vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
					vechand[i]->SetMove(false);
				}
				


				if (vechand[i]->GetSelect())
				{
					selectcount++;
				}
			}
			for (int i = 0; i < vechand.size(); ++i)
			{
				if (selectcount == 0)
				{
					m_firstCard = nullptr;
					m_SecondCard = nullptr;
					m_ThirdCard = nullptr;
					break;
				}
					
				if (vechand[i]->GetSelect())
				{
					if (selectcount == 1)
					{
						m_firstCard = vechand[i];
						m_SecondCard = nullptr;
						m_ThirdCard = nullptr;
						break;
					}
					else if (selectcount == 2)
					{
						if (m_firstCard == vechand[i])
							continue;
						else
						{
							if (m_ThirdCard && m_SecondCard)
							{
								if (m_ThirdCard->GetSelect() && m_SecondCard->GetSelect())
								{
									m_firstCard = m_SecondCard;
									m_SecondCard = m_ThirdCard;
									m_ThirdCard = nullptr;
									break;
								}
							}
							if (m_ThirdCard == vechand[i])
							{
								m_SecondCard = vechand[i];
								m_ThirdCard = nullptr;	
							}
							
							
						}
						m_SecondCard = vechand[i];
						m_ThirdCard = nullptr;
						break;
					}
					else if (selectcount == 3)
					{
						if (m_firstCard == vechand[i] || m_SecondCard == vechand[i])
							continue;
						m_ThirdCard = vechand[i];
					}

				}
			}
			if (!m_firstCard)
				m_Firstinfo->SetPos(550.f, -1100.f);
			else
				m_Firstinfo->SetPos(Vector2(m_firstCard->GetRelativePos().x-75.f, m_firstCard->GetRelativePos().y + 100.f));

			if (!m_SecondCard)
				m_Secondinfo->SetPos(550.f, -1050.f);
			else
				m_Secondinfo->SetPos(Vector2(m_SecondCard->GetRelativePos().x - 75.f, m_SecondCard->GetRelativePos().y + 100.f));

			if (!m_ThirdCard)
				m_Thirdinfo->SetPos(550.f, -1050.f);
			else
				m_Thirdinfo->SetPos(Vector2(m_ThirdCard->GetRelativePos().x- 75.f, m_ThirdCard->GetRelativePos().y + 100.f));
		}
	}
}

void CMulrigunHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMulrigunHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CMulrigunHUDWidget* CMulrigunHUDWidget::Clone()
{
	return new CMulrigunHUDWidget(*this);
}

void CMulrigunHUDWidget::OpenWidget()
{

	m_Firstinfo->SetPos(550.f, -1100.f);
	m_Secondinfo->SetPos(550.f, -1050.f);
	m_Thirdinfo->SetPos(550.f, -1050.f);
	m_DrawButton->SetPos(565.f, -1100.f);
	m_GameMapObj->SetMuligunEnd(true);
	std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
	for (int i = 0; i < vechand.size(); ++i)
	{
		vechand[i]->SetRelativePos(729.4f - (72.f * vechand.size()), -800.f, 0.f);
		vechand[i]->AddWorldPos(vechand[i]->GetRelativeScale().x * i + 10.f, 0.f, 0.f);
		vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
		vechand[i]->SetMove(false);
		vechand[i]->SetSelectTime(false);
	}
	if(m_HandCardBurn)
		m_GameMapObj->Player1CardBurn();
	else
		m_GameMapObj->Mulrigungo(m_firstCard, m_SecondCard, m_ThirdCard);
	m_Open = true;
	m_Close = false;
	m_OpenStartCheck = false;
	// 화면에 알파블랙 설치용도
	m_GameMapObj->SetSelectTiming(false);
}

void CMulrigunHUDWidget::CloseWidget()
{
	// 화면에 알파블랙 설치용도
	std::vector<CSharedPtr<CCard>> vechand= m_GameMapObj->GetPlayer1Hand();
	for (int i = 0; i < vechand.size(); ++i)
	{
		vechand[i]->SetRelativePos(729.4f - (72.f * vechand.size()), -800.f, 0.f);
		vechand[i]->AddWorldPos(vechand[i]->GetRelativeScale().x * i + 10.f, 0.f, 0.f);
		vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
		vechand[i]->SetMove(false);
		vechand[i]->SetSelectTime(true);
			
	}
	m_GameMapObj->SetSelectTiming(true);
	m_Open = false;
	m_OpenStartCheck = false;
	m_CloseEndCheck = false;
	m_Close = true;
	m_DrawButton->SetStateTexture(Button_State::Normal, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "greate", TEXT("button/결정하기.png"));
	m_DrawButton->SetClickCallback<CMulrigunHUDWidget>(this, &CMulrigunHUDWidget::DrawButton);

}

void CMulrigunHUDWidget::ClosePlayer1EndWidget()
{
	// 화면에 알파블랙 설치용도
	m_GameMapObj->SetSelectTiming(true);
	std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
	for (int i = 0; i < vechand.size(); ++i)
	{
		vechand[i]->SetRelativePos(729.4f - (72.f * vechand.size()), -800.f, 0.f);
		vechand[i]->AddWorldPos(vechand[i]->GetRelativeScale().x * i + 10.f, 0.f, 0.f);
		vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
		vechand[i]->SetMove(false);
		vechand[i]->SetSelectTime(true);
	}
	
	m_Open = false;
	m_OpenStartCheck = false;
	m_CloseEndCheck = false;
	m_Close = true;
	m_HandCardBurn = true;
	m_DrawButton->SetStateTexture(Button_State::Normal, "버림패정하기", TEXT("button/버림패정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::MouseOn, "버림패정하기", TEXT("button/버림패정하기.png"));
	m_DrawButton->SetStateTexture(Button_State::Click, "버림패정하기", TEXT("button/버림패정하기.png"));
	m_DrawButton->SetClickCallback<CMulrigunHUDWidget>(this, &CMulrigunHUDWidget::BurnButton);
}

void CMulrigunHUDWidget::StartClick()
{
}

void CMulrigunHUDWidget::Open(float DeltaTime)
{
	/*Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
	Vector2 StartPoint = Vector2(0.f, -800.f);
	StartPoint = StartPoint - m_DrawButton->GetPos();

	if (StartPoint.y >= 0.02f && !m_OpenStartCheck)
	{
		m_DrawButton->AddPos(Vector2(0.f, StartPoint.y * DeltaTime * 5.f));
		for (int i = 0; i < vechand.size(); ++i)
		{
			vechand[i]->AddRelativePos(0.f, StartPoint.y * DeltaTime * 5.f, 0.f);
			vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
			vechand[i]->SetMove(false);
		}

	}
	else
	{

	}
		*/




}

void CMulrigunHUDWidget::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
	Vector2 StartPoint = Vector2(Center.x +15.f, Center.y );
	StartPoint = StartPoint - vechand[0]->GetRelativePos().y;

	if (StartPoint.y >= 0.02f)
	{
		m_DrawButton->AddPos(Vector2(0.f, StartPoint.y * DeltaTime * 15.f + DeltaTime * 15.f));

		for (int i = 0; i < vechand.size(); ++i)
		{
			vechand[i]->AddRelativePos(0.f, StartPoint.y * DeltaTime * 15.f + DeltaTime * 15.f, 0.f);
			vechand[i]->SetStartHandPos(vechand[i]->GetRelativePos());
			vechand[i]->SetMove(false);
		}
	}
	else
	{
		m_CloseEndCheck = true;
	}
}


void CMulrigunHUDWidget::DrawButton()
{

	OpenWidget();

}

void CMulrigunHUDWidget::BurnButton()
{
	int selectcount = 0;
	std::vector<CSharedPtr<CCard>> vechand = m_GameMapObj->GetPlayer1Hand();
	for (int i = 0; i < vechand.size(); ++i)
	{
		if (vechand[i]->GetSelect())
		{
			selectcount++;
		}
	}

	if((vechand.size() - selectcount) == 2)
		OpenWidget();
}

void CMulrigunHUDWidget::RefreshButton()
{
	m_GameMapObj->RefreshDeck();

	CloseWidget();
}
