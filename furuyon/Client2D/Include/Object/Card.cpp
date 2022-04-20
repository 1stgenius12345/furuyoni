#include "Card.h"
#include "Input.h"
#include "Bullet.h"
#include "Deck.h"
#include "Device.h"
#include "../UI/SelectHUDWidget.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "TestParticle.h"
#include "Resource/ResourceManager.h"
#include "Render/RenderManager.h"



//bool CCard::m_MouseClick = false;

CCard::CCard() :
	//m_PlayerInfoWidget(nullptr),
	m_CardIndex(0),
	m_HeroIndex(0),
	//	m_MouseClick(false),
	m_TempWorldZ(0.f),
	m_StartHandPos(0.f, 0.f, 0.f),
	m_bMove(true),
	m_bRender(true),
	m_Select(false),
	m_pDeck(nullptr),
	m_CardType(Card_Type::Attack),
	m_CardClass(Card_Class::Normal),
	m_CardClickDelay(0.f),
	m_CardClickDelayMAX(0.2f),
	m_Loopup(false),
	m_Use(false),
	m_Daeung(0),
	m_Tenreok(0),
	m_ManaCost(0),
	m_Lookable(true),
	m_SelectTime(false),
	m_Player(1),
	m_Daeung_Triger(false)
{
}



CCard::CCard(const CCard& obj) :
	CGameObject(obj)
{
	m_CardIndex = obj.m_CardIndex;
	m_HeroIndex = obj.m_HeroIndex;
	m_CardType = obj.m_CardType;
	m_CardClass = obj.m_CardClass;
	m_Daeung = obj.m_Daeung;
	m_Tenreok = obj.m_Tenreok;
	m_ManaCost = obj.m_ManaCost;
	m_Player = obj.m_Player;
	m_Daeung_Triger = obj.m_Daeung_Triger;


	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Rotation = FindSceneComponent("Rotation");
	m_Body = (CColliderBox2D*)FindSceneComponent("Body");

	


}

CCard::~CCard()
{
}

void CCard::SetCardUnClick()
{
	

	if (m_pDeck->GetSelectWidget() )
	{
		
		//m_bMove = true;
		if (m_CardClass == Card_Class::Normal )
		{
			if (m_pDeck->GetSelectWidget()->GetNormalCard() > 0)
			{
				CResourceManager::GetInst()->SoundPlay("Click");
				m_SpriteMtrl->SetShader("Standard2DTextureShader");
				m_pDeck->GetSelectWidget()->AddNormalCard(-1);
				m_Select = false;

			}
			
		}
		else
		{
			if (m_pDeck->GetSelectWidget()->GetHeroCard() > 0)
			{
				CResourceManager::GetInst()->SoundPlay("Click");
				m_SpriteMtrl->SetShader("Standard2DTextureShader");
				m_pDeck->GetSelectWidget()->AddHeroCard(-1);
				m_Select = false;
			}
		}
	}
	

}

void CCard::SetCardClick()
{
	if (m_pDeck->GetSelectWidget() )
	{
		
		//m_bMove = false;

		if (m_CardClass == Card_Class::Normal)
		{
			if (m_pDeck->GetSelectWidget()->GetNormalCard() < 7)
			{
				CResourceManager::GetInst()->SoundPlay("Click");
				m_SpriteMtrl->SetShader("Standard2DCard");
				m_pDeck->GetSelectWidget()->AddNormalCard(1);
				m_Select = true;
			}
		
		}
		else
		{
			if (m_pDeck->GetSelectWidget()->GetHeroCard() < 3)
			{
				CResourceManager::GetInst()->SoundPlay("Click");
				m_SpriteMtrl->SetShader("Standard2DCard");
				m_pDeck->GetSelectWidget()->AddHeroCard(1);
				m_Select = true;
			}
		}
	}

}

void CCard::Start()
{
	//if (!m_bRender)
	//	return;
	CGameObject::Start();
}

bool CCard::Init()
{
	 
	CGameObject::Init();

	m_Body = CreateSceneComponent<CColliderBox2D>("Body");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(744.f/4.f/1.3f, 1038.f/4.f/1.3f, 0.f);
	m_Sprite->SetRelativePos(-300.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 1.f);
	//m_Sprite->AddChild(m_PlayerInfoWidgetComponent);
	m_Body->SetExtent(m_Sprite->GetRelativeScale().x* 180.f /744.f, m_Sprite->GetRelativeScale().y*270.f/1038.f);
	m_Body->SetCollisionProfile("PlayerAttack");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);
	m_Sprite->AddChild(m_Body);
	m_SpriteMtrl = m_Sprite->GetMaterial(0);
	m_SpriteMtrl->AddTexture("CardSample", TEXT("card/back.jpg"));
	m_SpriteMtrl->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.f);
	m_SpriteMtrl->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_Rotation);
	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);
	m_Body->AddCollisionMouseCallbackFunction<CCard>(Collision_State::Begin, this,
		&CCard::CollisionBeginMouse);
	m_Body->AddCollisionMouseCallbackFunction<CCard>(Collision_State::End, this,
		&CCard::CollisionEndMouse);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCard::Update(float DeltaTime)
{	

	/*if (!m_bRender)
	{
		m_SpriteMtrl->SetOpacity(0.f);
		m_Sprite->SetRelativePos(0.f,-500.f, 0.f);
		m_StartHandPos = Vector3(0.f, -500.f, 0.f);
		m_Sprite->AddChild(m_Body);
	}
	else
	{
		m_SpriteMtrl->SetOpacity(1.f);
	}
	*/
		
	CGameObject::Update(DeltaTime);
	bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();
	bool MouseRightState = CInput::GetInst()->GetMouseRightState();
	bool MouseRightPut = CInput::GetInst()->GetMouseRightPut();
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	if (!MouseLeftState)
	{
		if (m_Loopup)
		{
			m_Loopup = false;

		}

	}
	if (MouseRightPut)
	{
		if (m_Loopup)
		{
			m_Loopup = false;

		}

	}
	
	
	if(m_Lookable)
		LoopUptherCard();


	// Select단에서 하는 업데이트
	if (m_pDeck->GetSelectWidget())
	{
		if (m_MouseIsit)
		{
			m_CardClickDelay += DeltaTime;
			if (m_CardClickDelay >= m_CardClickDelayMAX)
			{
				m_CardClickDelay -= m_CardClickDelayMAX;
				
				if (m_pScene->GetCard() == this)
				{
					m_pScene->NullCard();
				}
				m_MouseIsit = false;
			}
		}
		if (MouseLeftState)
		{
			
			//m_Loopup = false;
		}
			
	}
	else
	{



		Vector3 temp3 = m_Sprite->GetRelativePos();
	//	Vector3 temp2 = m_PlayerInfoWidgetComponent->GetRelativePos();
		
		Vector2 Mousepos = CInput::GetInst()->GetMousePos();
		if (!MouseLeftState && m_bMove)
		{
			if (m_MouseIsit && m_pScene->GetCard() == this)
			{
				//m_SpriteMtrl->SetShader("Standard2DCard");
				m_Sprite->SetRelativePos(Mousepos.x, Mousepos.y, 0.f);
				m_Sprite->SetRelativeScale(744.f / 16.f / 1.3f, 1038.f / 16.f / 1.3f, 1.f);
				m_Body->SetExtent(2.f, 2.f);

				//m_Sprite->DeleteChild(m_Body);
				//m_Body->SetRelativePos(0.f,-1000.f,0.f);
			}

			//m_MouseIsit = false;
		}
		else if(!m_Loopup)
		{	
			// 부여패 크기 조절 
			if(!m_Use)
				m_Sprite->SetRelativeScale(744.f / 4.f / 1.3f, 1038.f / 4.f / 1.3f, 1.f);
			else
				m_Sprite->SetRelativeScale(744.f / 10.f / 1.3f, 1038.f / 10.f / 1.3f, 1.f);
			//m_SpriteMtrl->SetShader("Standard2DTextureShader");
		/*	if (m_pScene->GetCard() == this)
			{
				m_pScene->NullCard();
			}*/
			m_MouseIsit = false;
			m_Sprite->SetRelativePos(m_StartHandPos);
			m_Body->SetExtent(m_Sprite->GetRelativeScale().x * 180.f / 372.f, m_Sprite->GetRelativeScale().y * 270.f / 519.f);
			m_Body->SetCollisionProfile("MonsterAttack");

		}
		if (MouseRightState)
		{
			
		/*	if (m_pDeck->GetSelectWidget())
				m_pDeck->GetSelectWidget()->SetLookUp(true);*/
			//m_Loopup = false;
			m_Body->SetCollisionProfile("PlayerAttack");
		}
			



	}
	

	//if (m_CardClass == Card_Class::Hero && m_Use == false && m_Loopup == false && !(m_pDeck->GetSelectWidget()))
	//{
	//	m_SpriteMtrl->AddTexture("back",TEXT("card/back.jpg"));
	//}
	//else if (m_CardClass == Card_Class::Hero && (m_Use == true || m_Loopup == true) && !(m_pDeck->GetSelectWidget()))
	//{
	//	CreateTex();
	//}



	//m_Rotation->AddRelativeRotationZ(90.f * DeltaTime);


	// 마우스에 인식
	
	
	

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCard::PostUpdate(float DeltaTime)
{
	
	CGameObject::PostUpdate(DeltaTime);
}

void CCard::Collision(float DeltaTime)
{

	CGameObject::Collision(DeltaTime);
}

void CCard::Render(float DeltaTime)
{
	

	CGameObject::Render(DeltaTime);
}

CCard* CCard::Clone()
{
	return new CCard(*this);
}

void CCard::Animation2DNotify(const std::string& Name)
{
	
}

void CCard::CreateCardSetting()
{
}


void CCard::MoveUp(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CCard::MoveDown(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CCard::RotationZ(float DeltaTime)
{
	AddRelativeRotationZ(360.f * DeltaTime);
}

void CCard::RotationZInv(float DeltaTime)
{
	AddRelativeRotationZ(-360.f * DeltaTime);
}

void CCard::Fire(float DeltaTime)
{
	
}

void CCard::Triple(float DeltaTime)
{
	
}

void CCard::Skill2(float DeltaTime)
{
	
}

void CCard::AnimationFrameEnd(const std::string& Name)
{
	
}

void CCard::CollisionBeginMouse(const Vector2& result, CCollider* Collider)
{
	
	

	bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();
	bool MouseRightState = CInput::GetInst()->GetMouseRightState();
	bool MousePut = CInput::GetInst()->GetMousePut();
	bool MouseRightPut = CInput::GetInst()->GetMouseRightPut();
	if (m_pDeck->GetSelectWidget())
	{	
		if (MousePut && !m_MouseIsit)
		{
			if (m_Select)
			{
			
				SetCardUnClick();
				m_CardClickDelay = 0.f;
			}
			else
			{
				
				SetCardClick();
				m_CardClickDelay = 0.f;
			}
			if (!m_pScene->IsCard())
			{
				m_pScene->SetCard(this);
				m_MouseIsit = true;
			}
			
		}
		else if (MouseRightPut && !m_MouseIsit)
		{
			if (m_Loopup)
				m_Loopup = false;
			else
				m_Loopup = true;
		}
		


	}
	else
	{

		if (m_SelectTime)
		{
			if (MousePut && !m_MouseIsit)
			{
				if (m_Select)
				{
					CResourceManager::GetInst()->SoundPlay("Click");
					m_SpriteMtrl->SetShader("Standard2DTextureShader");
					m_Select = false;
					m_CardClickDelay = 0.f;
				}
				else
				{
				
					CResourceManager::GetInst()->SoundPlay("Click");
						//m_bMove = false;
					m_SpriteMtrl->SetShader("Standard2DCard");
					m_Select = true;
					

					m_CardClickDelay = 0.f;
				}
				if (!m_pScene->IsCard())
				{
					m_pScene->SetCard(this);
					m_MouseIsit = true;
				}
			
			}
		}
		
		bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();
	

	/*	if (!MouseLeftState)
		{*/
			if (!m_pScene->IsCard())
			{
				m_pScene->SetCard(this);
				m_MouseIsit = true;
			}
			

	//	}
		else if (MouseRightPut && !m_MouseIsit)
		{
			if (m_Loopup)
				m_Loopup = false;
			else
				m_Loopup = true;
		}
	}
	
	


}

void CCard::CollisionEndMouse(const Vector2& result, CCollider* Collider)
{
	m_pScene->NullCard();
	
//m_MouseIsit = false;
	
	
		//m_MouseIsit = false;
	//m_Sprite->AddRelativePos(0.f,0.f,m_TempWorldZ * 2.f);
}

void CCard::LoopUptherCard()
{
	bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();
	bool MouseRightState = CInput::GetInst()->GetMouseRightState();
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;

	if (m_Loopup)
	{
		
		m_Body->SetExtent(m_Sprite->GetRelativeScale().x * 180.f / 372.f/2.f/1.3f, m_Sprite->GetRelativeScale().y * 270.f / 519.f  / 2.f/1.3f);
		m_Body->SetRelativePos(m_StartHandPos-Vector3(Center.x, Center.y + 30.f, 0.f));
	//	m_Body->SetWorldPos(m_Sprite->GetWorldPos());
		m_Sprite->SetRelativeScale(744.f/2.f, 1038.f/2.f, 0.f);
		m_Sprite->SetRelativePos(Center.x, Center.y + 30.f, 0.f);
	//	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	//	m_PlayerInfoWidget->SetSize(m_Sprite->GetRelativeScale().x / 375.f, m_Sprite->GetRelativeScale().y / 563.f);
		
		if(m_pDeck->GetSelectWidget())
			m_SpriteMtrl->SetEmissiveColor(2.f, 2.f, 2.f, 0.f);;
		m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	//	CreateTex();
		if (m_pDeck->GetSelectWidget())
			m_pDeck->GetSelectWidget()->SetLookUp(false);
		//m_PlayerInfoWidget->SetPos()
	//	m_PlayerInfoWidget->UpdatePosANDScale();
	}
	else
	{
		/*if (!m_Use && m_CardClass == Card_Class::Hero && m_Sprite->GetRelativeScale() != Vector3(744.f / 4.f / 1.3f, 1038.f / 4.f / 1.3f, 1.f) && !m_pDeck->GetSelectWidget())
		{
			SetBack();
		}*/

		m_Sprite->SetRelativeScale(744.f / 4.f / 1.3f, 1038.f / 4.f / 1.3f, 1.f);
		m_Sprite->SetRelativePos(m_StartHandPos);
		if (m_pDeck->GetSelectWidget())
			m_SpriteMtrl->SetEmissiveColor(0.5f, 0.5f, 0.5f, 0.5f);
		m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);
		m_Body->SetExtent(m_Sprite->GetRelativeScale().x * 180.f /372.f, m_Sprite->GetRelativeScale().y * 270.f /519.f);
		m_Body->SetRelativePos(0.f, 0.f, 0.f);

		
	//	m_PlayerInfoWidget->SetSize(m_Sprite->GetRelativeScale().x / 375.f, m_Sprite->GetRelativeScale().y / 563.f)	//	m_PlayerInfoWidget->UpdatePosANDScale();
	}
}

void CCard::CreatCard(CDeck* deck, int Cardindex, int Heroindex, Card_Type type, Card_Class cardcalss)
{
	m_pDeck = deck;
	m_CardIndex = Cardindex;
	m_HeroIndex = Heroindex;
	m_CardClass = cardcalss;
	m_CardType = type;
	CreateTex();
	CreateCardSetting();

}

void CCard::CreateTex()
{
	TCHAR tex[20] = { 0 };
	std::string std_str;

	_tcsncat_s(tex, TEXT("card/"), 5);



	if (m_CardClass == Card_Class::Normal)
	{
		_tcsncat_s(tex, TEXT("Normal/"), 7);
		std_str.push_back(0);
	}
	else
	{
		_tcsncat_s(tex, TEXT("Hero/"), 5);
		std_str.push_back(1);
	}
		

	TCHAR ds1[3] = { 0 };
	_stprintf_s(ds1, _countof(ds1), TEXT("%d"), m_HeroIndex);

	_tcsncat_s(tex, ds1, 1);
	_tcsncat_s(tex, TEXT("/"), 1);
	std_str.push_back(m_HeroIndex+0);
	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_CardIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);
	std_str.push_back(m_CardIndex+0);
	//std::string std_str = TCHARToString(tex);

	m_SpriteMtrl->AddTexture(std_str, tex);
}

void CCard::LoadCard(CDeck* deck, int Cardindex, int Heroindex, Card_Type type, Card_Class cardcals)
{
}

void CCard::SettingGone()
{
	SetRelativePos(0.f, 1000.f, 0.f);
	SetStartHandPos(Vector3(0.f, 2000.f, 0.f));
	SetMove(false);
}

void CCard::SellectTextureSetting()
{
	m_SpriteMtrl->SetShader("Standard2DCard");
}

void CCard::UnSellectTextureSetting()
{
	 m_SpriteMtrl->SetShader("Standard2DTextureShader");
}

void CCard::SetRenderBack()
{
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);
}

void CCard::SetRenderDefault()
{
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);
}
