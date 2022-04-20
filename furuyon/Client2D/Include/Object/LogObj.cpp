
#include "LogObj.h"
#include "Deck.h"
#include "Card.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "../UI/PlayerWorldInfoWidget.h"


CLogObj::CLogObj():
	m_Look(true),
	m_Excel(0.f)
	
{


}



CLogObj::CLogObj(const CLogObj& obj) :
	CGameObject(obj)
{

}

CLogObj::~CLogObj()
{
	auto iter = m_vec_LogWidgetComponet.begin();
	auto iterend = m_vec_LogWidgetComponet.end();
	for (; iter != iterend; ++iter)
	{
		SAFE_RELEASE((*iter));
	}
}

void CLogObj::Start()
{
	CGameObject::Start();


}

bool CLogObj::Init()
{
	CGameObject::Init();

	
	//m_LogWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_LogWidgetComponent");

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_GameMapBackGround = CreateSceneComponent<CSpriteComponent>("Sprite");
	

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
	m_Sprite->SetRelativePos(300.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	// °ÔÀÓ¸Ê
	m_GameMapBackGround->SetRelativeScale(420.f, 670.f, 0.f);
	m_GameMapBackGround->SetPivot(0.5f, 0.5f, 0.5f);
	m_GameMapBackGround->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_GameMapBackGround->SetRelativePos(0.f, 0.f, 0.f);
	m_SpriteMtrl2 = m_GameMapBackGround->GetMaterial(0);
	m_SpriteMtrl2->AddTexture("·Î±×À§Á¬", TEXT("·Î±×À§Á¬.png"));
	//m_SpriteMtrl2->SetEmissiveColor(1.f, 1.5f, 1.5f, 1.f);
	m_SpriteMtrl2->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_GameMapBackGround);
	
	// Ä«µåµÞ¹è°æ
	


	// À§Á¬ °ü¸® ////////////////////////////////////////////////////////////////////////

	//// ±âº»µ¿ÀÛ À§Á¬ °ü¸®
	//m_LogWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	//m_LogWidgetComponent->SetPivot(0.5f, 0.5f, 0.5f);
	//m_LogWidgetComponent->SetRelativePos(-200.f,-310.f,0.f);
	//m_LogWidget = m_LogWidgetComponent->CreateWidget<CPlayerLogHUDWidget>("m_LogWidget");
	//m_Sprite->AddChild(m_LogWidgetComponent);

	return true;
}

void CLogObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	bool MouseRightPut = CInput::GetInst()->GetMouseRightPut();
	Vector2 mouseMove = CInput::GetInst()->GetMouseMove();
	bool mousepush = CInput::GetInst()->GetMousePush();
	if (mousepush)
	{
		m_Excel = 0;
		int tempy = mouseMove.y;
		m_Excel += tempy;
	}
	if (m_vec_LogWidgetComponet.size() > 0)
	{
		if (m_vec_LogWidgetComponet.back()->GetRelativePos().y >= -270.f && m_vec_LogWidgetComponet.front()->GetRelativePos().y <= 110.f)
		{
			for (int i = 0; i < m_vec_LogWidgetComponet.size(); ++i)
			{
				m_vec_LogWidgetComponet[i]->AddRelativePos(0.f, m_Excel / 2.f, 0.f);
			}
		}
		else if (m_Excel <= 0 && m_vec_LogWidgetComponet.front()->GetRelativePos().y >= 110.f)
		{
			for (int i = 0; i < m_vec_LogWidgetComponet.size(); ++i)
			{
				m_vec_LogWidgetComponet[i]->AddRelativePos(0.f, m_Excel / 2.f, 0.f);
			}
		}
		else if (m_Excel >= 0 && m_vec_LogWidgetComponet.back()->GetRelativePos().y <= -270.f)
		{
			for (int i = 0; i < m_vec_LogWidgetComponet.size(); ++i)
			{
				m_vec_LogWidgetComponet[i]->AddRelativePos(0.f, m_Excel / 2.f, 0.f);
			}
		}
		
	}
		

	if (m_Excel >= 0.2f)
		m_Excel -= 0.2f;
	else if (m_Excel >= 0.f)
	{
		m_Excel = 0.f;
	}
	else if(m_Excel <= -0.2f)
		m_Excel += 0.2f;
	else if (m_Excel <= 0.f)
	{
		m_Excel = 0.f;
	}

	if (MouseRightPut)
	{	
		if (m_Look)
		{
			m_Sprite->SetRelativePos(640.f, 360.f, 0.f);
			m_Look = false;
		}
		else
		{
			m_Sprite->SetRelativePos(-600.f, 0.f, 0.f);
			m_Look = true;
		}
		
		for (int i = 0; i < m_vec_LogWidgetComponet.size(); ++i)
		{
			m_vec_LogWidgetComponet[i]->InheritPos();
		}
	}




}

void CLogObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CLogObj::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CLogObj::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CLogObj* CLogObj::Clone()
{
	return new CLogObj(*this);
}

void CLogObj::Animation2DNotify(const std::string& Name)
{

}

void CLogObj::CreateLog(CCard* card, CCard* card2, int index, int player)
{
	CSharedPtr<CWidgetComponent> LogWidgetComponent = CreateSceneComponent<CWidgetComponent>("LogWidgetComponent");
	LogWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	LogWidgetComponent->SetPivot(0.5f, 0.5f, 0.5f);

	for (int i = 0; i < m_vec_LogWidgetComponet.size(); ++i)
	{
		m_vec_LogWidgetComponet[i]->AddRelativePos(0, 120.f, 0.f);
	}
	if(m_vec_LogWidgetComponet.size() == 0)
		LogWidgetComponent->SetRelativePos(-200.f, -270.f, 0.f);
	else
		LogWidgetComponent->SetRelativePos(-200.f, m_vec_LogWidgetComponet.back()->GetRelativePos().y - 120.f, 0.f);
	
	CPlayerLogHUDWidget* LogWidget = LogWidgetComponent->CreateWidget<CPlayerLogHUDWidget>("LogWidget");
	m_Sprite->AddChild(LogWidgetComponent);
	m_vec_LogWidgetComponet.push_back(LogWidgetComponent);

	if (card == nullptr && card2 == nullptr && player >= 3)
	{
		if (player == 3)
			LogWidget->PlayerDrawLog();
		else if (player == 4)
			LogWidget->PlayerRefreshLog();
		else if (player == 5)
			LogWidget->AiDrawLog();
		else if (player == 6)
			LogWidget->AiRefreshLog();
		return;
	}


	if (card == nullptr)
	{
		if (player == 1)
		{	
			if (index >= 7)
			{
				LogWidget->PlayerBackCardLog(index-6);
			}
			else
			{
				LogWidget->PlayerFocusLog(index);
			}
			return;
		}
		else
		{
			if (index >= 7)
			{
				LogWidget->AiBackCardLog(index - 6);
			}
			else
			{
				LogWidget->AiFocusLog(index);
			}
			return;
		}
	}
	else
	{
		if (player == 1)
		{
			if (card2 == nullptr)
			{
				if (index == 1)
				{
					LogWidget->PlayerJaegiLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass());
					return;
				}
				else if (index == 2)
				{
					LogWidget->PlayerBurnLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass());
					return;
				}
				LogWidget->PlayerUseLog(card->GetHeroIndex(),card->GetCardIndex(),(int)card->GetCardClass());
			}
			else
			{
				LogWidget->PlayerDaeugLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass(), card2->GetHeroIndex(), card2->GetCardIndex(), (int)card2->GetCardClass());
			}
			return;
		}
		else
		{
			if (card2 == nullptr)
			{
				if (index == 1)
				{
					LogWidget->AiJaegiLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass());
					return;
				}
				else if (index == 2)
				{
					LogWidget->AiBurnLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass());
					return;
				}
				LogWidget->AiUseLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass());
			}
			else
			{
				LogWidget->AiDaeugLog(card->GetHeroIndex(), card->GetCardIndex(), (int)card->GetCardClass(), card2->GetHeroIndex(), card2->GetCardIndex(), (int)card2->GetCardClass());
			}
			return;
		}
	}

	
	

}
