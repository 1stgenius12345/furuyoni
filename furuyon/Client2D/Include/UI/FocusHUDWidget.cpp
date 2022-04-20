#include "FocusHUDWidget.h"
#include "Device.h"
#include "../Object/GameMapObj.h"
CFocusHUDWidget::CFocusHUDWidget():
	m_Open(false),
	m_Close(false),
	m_OpenStartCheck(false),
	m_index(0)
{
}

CFocusHUDWidget::CFocusHUDWidget(const CFocusHUDWidget& widget)
{
}

CFocusHUDWidget::~CFocusHUDWidget()
{
}

bool CFocusHUDWidget::Init()
{
	CWidgetWindow::Init();

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	m_Forward = CreateWidget<CButton>("Forward");
	m_Forward->SetPos(Center.x + 275.f, Center.y - 150.f );
	m_Forward->SetSize(238.f/500.f, 372.f/500.f); 
	m_Forward->SetStateTexture(Button_State::Normal, "Forward_default", TEXT("button/Forward_default.png"));
	m_Forward->SetStateTexture(Button_State::MouseOn, "Forward_Click", TEXT("button/Forward_Click.png"));
	m_Forward->SetStateTexture(Button_State::Click, "Forward_push", TEXT("button/Forward_push.png"));
	m_Forward->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_Forward->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_Forward->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Forward->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::ClickForward);
	m_Forward->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_Backward = CreateWidget<CButton>("Bakcward");
	m_Backward->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Backward->SetSize(238.f / 500.f, 372.f / 500.f);
	m_Backward->SetStateTexture(Button_State::Normal, "Backward_default", TEXT("button/Backward_default.png"));
	m_Backward->SetStateTexture(Button_State::MouseOn, "Backward_Click", TEXT("button/Backward_Click.png"));
	m_Backward->SetStateTexture(Button_State::Click, "Backward_push", TEXT("button/Backward_push.png"));
	m_Backward->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_Backward->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_Backward->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Backward->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::ClickBackward);
	
	m_Backward->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_Ora = CreateWidget<CButton>("Ora");
	m_Ora->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Ora->SetSize(238.f / 500.f, 372.f / 500.f);
	m_Ora->SetStateTexture(Button_State::Normal, "Ora_default", TEXT("button/Ora_default.png"));
	m_Ora->SetStateTexture(Button_State::MouseOn, "Ora_Click", TEXT("button/Ora_Click.png"));
	m_Ora->SetStateTexture(Button_State::Click, "Ora_push", TEXT("button/Ora_push.png"));
	m_Ora->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_Ora->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_Ora->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Ora->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::ClickOra);

	m_Ora->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	m_Mana = CreateWidget<CButton>("Mana");
	m_Mana->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Mana->SetSize(238.f / 500.f, 372.f / 500.f);
	m_Mana->SetStateTexture(Button_State::Normal, "Mana_default", TEXT("button/Mana_default.png"));
	m_Mana->SetStateTexture(Button_State::MouseOn, "Mana_Click", TEXT("button/Mana_Click.png"));
	m_Mana->SetStateTexture(Button_State::Click, "Mana_push", TEXT("button/Mana_push.png"));
	m_Mana->SetStateTint(Button_State::Normal, 0.8f, 0.8f, 0.8f, 1.f);
	m_Mana->SetStateTint(Button_State::MouseOn, 1.f, 1.f, 1.f, 1.f);
	m_Mana->SetStateTint(Button_State::Click, 0.6f, 0.6f, 0.6f, 1.f);
	m_Mana->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::ClickMana);

	m_Mana->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	

	return true;
}

void CFocusHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_GameMapObj->GetRange() <= m_GameMapObj->GetDALINRange())
	{
		m_Forward->SetStateTexture(Button_State::Normal, "Leaving_default", TEXT("button/Leaving_default.png"));
		m_Forward->SetStateTexture(Button_State::MouseOn, "Leaving_Click", TEXT("button/Leaving_Click.png"));
		m_Forward->SetStateTexture(Button_State::Click, "Leaving_push", TEXT("button/Leaving_push.png"));
		m_Forward->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::Clickital);
	}
	else
	{
		m_Forward->SetStateTexture(Button_State::Normal, "Forward_default", TEXT("button/Forward_default.png"));
		m_Forward->SetStateTexture(Button_State::MouseOn, "Forward_Click", TEXT("button/Forward_Click.png"));
		m_Forward->SetStateTexture(Button_State::Click, "Forward_push", TEXT("button/Forward_push.png"));
		m_Forward->SetClickCallback<CFocusHUDWidget>(this, &CFocusHUDWidget::ClickForward);
	}



	if (m_Open)
	{
		Open(DeltaTime);
	}

	if (m_Close)
	{
		Close(DeltaTime);
	}
}

void CFocusHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFocusHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CFocusHUDWidget* CFocusHUDWidget::Clone()
{
	return new CFocusHUDWidget(*this);
}

void CFocusHUDWidget::OpenWidget(int i)
{
	m_index = i;
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	m_Open = true;
	m_Close = false;
	m_OpenStartCheck = true;
	m_GameMapObj->SetSelectTiming(true);

	m_Forward->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Forward->SetSize(238.f / 50.f, 372.f / 50.f);

	m_Backward->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Backward->SetSize(238.f / 50.f, 372.f / 50.f);

	m_Ora->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Ora->SetSize(238.f / 50.f, 372.f / 50.f);

	m_Mana->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Mana->SetSize(238.f / 50.f, 372.f / 50.f);
}

void CFocusHUDWidget::CloseWidget()
{
	m_Open = false;
	m_OpenStartCheck = false;
	m_Close = true;
	m_GameMapObj->SetSelectTiming(false);
}

void CFocusHUDWidget::StartClick()
{
}

void CFocusHUDWidget::Open(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	
	/*float sizex = m_Forward->GetSize().x;
	float sizey = m_Forward->GetSize().y;
	if (sizex <= 238.f / 3.f && sizey <= 372.f /3.f)
	{
		Vector2 vecTemp = Vector2(DeltaTime * 500.f / 238.f, DeltaTime * 500.f / 372.f);
		m_Forward->AddSize(vecTemp);
		m_Backward->AddSize(vecTemp);
		m_Ora->AddSize(vecTemp);
		m_Mana->AddSize(vecTemp);
	}
	else
		m_Open = false;

	Vector2 StartPoint = Vector2(Center.x + 275.f - 238.f / 3.f * 1.5f, Center.y - 150.f + 372.f / 3.f);
	if (m_Forward->GetPos() != StartPoint)
	{
		m_Forward->AddPos((m_Forward->GetPos() - StartPoint) * DeltaTime * 100.f);
		m_Backward->AddPos((m_Backward->GetPos() - StartPoint) * DeltaTime * 100.f);
		m_Ora->AddPos((m_Ora->GetPos() - StartPoint) * DeltaTime * 100.f);
		m_Mana->AddPos((m_Mana->GetPos() - StartPoint) * DeltaTime * 100.f);
	}*/
	Vector2 StartPoint = Vector2(Center.x + 275.f - 238.f / 3.f * 1.5f, Center.y - 150.f + 372.f / 3.f);
	StartPoint =  StartPoint - m_Forward->GetPos();
	
	if (StartPoint.y >= 0.01f && m_OpenStartCheck)
	{
		m_Forward->AddPos(StartPoint * Vector2(DeltaTime * 20, DeltaTime * 20));
		m_Backward->AddPos(StartPoint * Vector2(DeltaTime * 20, DeltaTime * 20));
		m_Ora->AddPos(StartPoint * Vector2(DeltaTime * 20, DeltaTime * 20));
		m_Mana->AddPos(StartPoint * Vector2(DeltaTime * 20, DeltaTime * 20));
	}
	else
		m_OpenStartCheck = false;

	float sizex = m_Forward->GetSize().x;
	float sizey = m_Forward->GetSize().y;
	Vector2 vecTemp = Vector2(238.f/3.f, 372.f /3.f);
	vecTemp = vecTemp - m_Forward->GetSize();
	if (sizey <= 372.f / 3.f)
	{
		m_Forward->AddSize(vecTemp * Vector2(DeltaTime * 6, DeltaTime * 6));
		m_Backward->AddSize(vecTemp * Vector2(DeltaTime * 6, DeltaTime * 6));
		m_Ora->AddSize(vecTemp * Vector2(DeltaTime * 6, DeltaTime * 6));
		m_Mana->AddSize(vecTemp * Vector2(DeltaTime * 6, DeltaTime * 6));
	}

	
	if (!m_OpenStartCheck)
	{
		Vector2 BackStartPoint = Vector2(Center.x + 275.f - 238.f / 3.f * 0.5f, Center.y - 150.f + 372.f / 3.f);
		BackStartPoint = BackStartPoint - m_Backward->GetPos();
		m_Backward->AddPos(BackStartPoint * Vector2(DeltaTime * 6, DeltaTime * 6));

		Vector2 OraStartPoint = Vector2(Center.x + 275.f + 238.f / 3.f * 0.5f, Center.y - 150.f + 372.f / 3.f);
		OraStartPoint = OraStartPoint - m_Ora->GetPos();
		m_Ora->AddPos(OraStartPoint * Vector2(DeltaTime * 6, DeltaTime * 6));

		Vector2 ManaStartPoint = Vector2(Center.x + 275.f + 238.f / 3.f * 1.5f, Center.y - 150.f + 372.f / 3.f);
		ManaStartPoint = ManaStartPoint - m_Mana->GetPos();
		m_Mana->AddPos(ManaStartPoint * Vector2(DeltaTime * 6, DeltaTime * 6));

	}

}

void CFocusHUDWidget::Close(float DeltaTime)
{

	Resolution	RS = CDevice::GetInst()->GetResolution();
	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	
	m_Forward->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Forward->SetSize(238.f / 500.f, 372.f / 500.f);

	m_Backward->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Backward->SetSize(238.f / 500.f, 372.f / 500.f);
		
	m_Ora->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Ora->SetSize(238.f / 500.f, 372.f / 500.f);

	m_Mana->SetPos(Center.x + 275.f, Center.y - 150.f);
	m_Mana->SetSize(238.f / 500.f, 372.f / 500.f);


}

void CFocusHUDWidget::ClickForward()
{
	if (m_GameMapObj->GetPlayer1Shiled() >= 5 || m_GameMapObj->GetRange() <= 2)
	{
		
	}
	else
	{
		m_GameMapObj->ForwardSound();
		m_GameMapObj->AddRange(-1);
		m_GameMapObj->AddPlayer1Shiled(1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		//m_GameMapObj->PushAnimationCard(0, 1, Card_Class::Normal);
		if (m_index == 1)
		{
			m_GameMapObj->LogCreate(nullptr,nullptr,7,1);
		}
		else
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 1, 1);
		}
		return;
	}

	
}

void CFocusHUDWidget::ClickBackward()
{
	if (m_GameMapObj->GetPlayer1Shiled() <= 0 || m_GameMapObj->GetRange() == 10)
	{
		
	}
	else
	{
		m_GameMapObj->BackWardSound();
		m_GameMapObj->AddRange(1);
		m_GameMapObj->AddPlayer1Shiled(-100);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		//m_GameMapObj->PushAnimationCard(0, 2, Card_Class::Normal);
		if (m_index == 1)
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 8, 1);
		}
		else
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 2, 1);
		}
		return;
	}





}

void CFocusHUDWidget::ClickOra()
{
	if (m_GameMapObj->GetDust() <= 0 || m_GameMapObj->GetPlayer1Shiled() >= 5)
	{
	
	}
	else
	{
		m_GameMapObj->OraSound();
		m_GameMapObj->AddDust(-1);
		m_GameMapObj->AddPlayer1Shiled(1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		//m_GameMapObj->PushAnimationCard(0, 3, Card_Class::Normal);
		if (m_index == 1)
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 9, 1);
		}
		else
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 3, 1);
		}
		return;
	}




}

void CFocusHUDWidget::ClickMana()
{
	if (m_GameMapObj->GetPlayer1Shiled() <= 0 )
	{
		
	}
	else
	{
		m_GameMapObj->ManaSound();
		m_GameMapObj->AddPlayer1Shiled(-100);
		m_GameMapObj->AddPlayer1Mana(1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
		//m_GameMapObj->PushAnimationCard(0, 4, Card_Class::Normal);
		if (m_index == 1)
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 10, 1);
		}
		else
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 4, 1);
		}
		return;
	}

}

void CFocusHUDWidget::Clickital()
{
	if (m_GameMapObj->GetDust() <= 0)
		return;
	else
	{
		m_GameMapObj->ItalSound();
		m_GameMapObj->AddRange(1);
		m_GameMapObj->AddDust(-1);
		m_Open = false;
		m_Close = true;
		m_GameMapObj->SetSelectTiming(false);
	//	m_GameMapObj->PushAnimationCard(0, 5, Card_Class::Normal);
		if (m_index == 1)
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 11, 1);
		}
		else
		{
			m_GameMapObj->LogCreate(nullptr, nullptr, 5, 1);
		}
		return;
	}
}
