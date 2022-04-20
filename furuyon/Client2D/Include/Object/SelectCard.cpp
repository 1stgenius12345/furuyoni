

#include "SelectCard.h"
#include "Deck.h"
#include "Card.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "../UI/PlayerWorldInfoWidget.h"


CSelectCard::CSelectCard():
	m_NormalInthebox(false),
	m_HeroInthebox(false),
	m_pCard(nullptr)
{


}



CSelectCard::CSelectCard(const CSelectCard& obj) :
	CGameObject(obj)
{

}

CSelectCard::~CSelectCard()
{

}

void CSelectCard::Start()
{
	CGameObject::Start();


}

bool CSelectCard::Init()
{
	CGameObject::Init();

	m_NormalSelect = CreateSceneComponent<CColliderBox2D>("NormalSelect");
	m_HeroSelect = CreateSceneComponent<CColliderBox2D>("HeroSelect");
	m_SelectWidgetComponent = CreateSceneComponent<CWidgetComponent>("SelectWidget");


	

	CSpriteComponent* m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_GameMapBackGround = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_CardBackGround = CreateSceneComponent<CSpriteComponent>("m_CardBackGround");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(50.f , 50.f , 1.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->AddChild(m_NormalSelect);
	m_NormalSelect->SetExtent(0.f, 0.f);
	m_NormalSelect->SetCollisionProfile("Player");





	m_HeroSelect->AddRelativePos(0.f, -350.f, 0.f);
	m_HeroSelect->SetExtent(0.f, 0.f);
	m_HeroSelect->SetCollisionProfile("Monster");
	m_Sprite->AddChild(m_HeroSelect);



	// 게임맵
	m_GameMapBackGround->SetRelativeScale(1280.f, 720.f, 0.f);
	m_GameMapBackGround->SetPivot(0.5f, 0.5f, 0.5f);
	m_GameMapBackGround->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_GameMapBackGround->SetRelativePos(640.,360.f, 0.f);
	m_SpriteMtrl2 = m_GameMapBackGround->GetMaterial(0);
	m_SpriteMtrl2->AddTexture("BackGround", TEXT("BackGround.jpg"));
	m_SpriteMtrl2->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.f);
	m_SpriteMtrl2->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_GameMapBackGround);

	// 카드뒷배경
	m_CardBackGround->SetRelativeScale(989.f * 1280.f / 1603.f, 736.f * 720.f / 905.f
		, 0.f);
	m_CardBackGround->SetPivot(0.f, 0.f, 0.f);
	m_CardBackGround->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_CardBackGround->SetRelativePos(37.f * 1280.f / 1603.f, 94.f * 720.f / 905.f
		, 0.f);
	m_SpriteMtrl3 = m_CardBackGround->GetMaterial(0);
	m_SpriteMtrl3->AddTexture("CardBackGround", TEXT("CardBackGround.png"));
	m_SpriteMtrl3->SetBaseColor(0.8f, 0.8f, 0.8f, 1.f);
	m_SpriteMtrl3->SetEmissiveColor(0.7f, 0.7f, 0.7f, 1.f);
	m_SpriteMtrl3->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_CardBackGround);


	// 위젯 관리 ////////////////////////////////////////////////////////////////////////

	// 기본동작 위젯 관리
	m_SelectWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_SelectWidget = m_SelectWidgetComponent->CreateWidget<CSelectHUDWidget>("FocusWidget");
	m_SelectWidget->SetSelectCard(this);
	m_Sprite->AddChild(m_SelectWidgetComponent);












	
	m_NormalSelect->AddCollisionCallbackFunction<CSelectCard>(Collision_State::Begin, this,
		&CSelectCard::CollisionBeginNormal);
	m_NormalSelect->AddCollisionCallbackFunction<CSelectCard>(Collision_State::End, this,
		&CSelectCard::CollisionEndNormal);


	m_HeroSelect->AddCollisionCallbackFunction<CSelectCard>(Collision_State::Begin, this,
		&CSelectCard::CollisionBeginHero);
	m_HeroSelect->AddCollisionCallbackFunction<CSelectCard>(Collision_State::End, this,
		&CSelectCard::CollisionEndHero);
	return true;
}

void CSelectCard::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	// 마우스에 인식

	//bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();

	//if (m_NormalInthebox && MouseLeftState)
	//{
	//	m_NormalInthebox = false;
	//	if (m_SelectWidget->GetNormalCard() < 7)
	//	{
	//		m_SelectWidget->AddNormalCard(1);
	//		m_pCard->SetCardClick();
	//	}
	//	
	//}


	//if (m_HeroInthebox && MouseLeftState)
	//{
	//	m_HeroInthebox = false;

	//	if (m_SelectWidget->GetHeroCard() < 3)
	//	{
	//		m_SelectWidget->AddHeroCard(1);
	//		m_pCard->SetCardClick();
	//	}
	//		
	//}






}

void CSelectCard::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSelectCard::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CSelectCard::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CSelectCard* CSelectCard::Clone()
{
	return new CSelectCard(*this);
}

void CSelectCard::Animation2DNotify(const std::string& Name)
{

}

void CSelectCard::MoveUp(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CSelectCard::MoveDown(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CSelectCard::RotationZ(float DeltaTime)
{
	AddRelativeRotationZ(360.f * DeltaTime);
}

void CSelectCard::RotationZInv(float DeltaTime)
{
	AddRelativeRotationZ(-360.f * DeltaTime);
}

void CSelectCard::Fire(float DeltaTime)
{

}

void CSelectCard::Triple(float DeltaTime)
{

}

void CSelectCard::Skill2(float DeltaTime)
{

}

void CSelectCard::AnimationFrameEnd(const std::string& Name)
{

}

void CSelectCard::CollisionBeginNormal(const HitResult& result, CCollider* Collider)
{
	m_pCard = (CCard*)result.DestObject;
	m_NormalInthebox = true;
}

void CSelectCard::CollisionBeginHero(const HitResult& result, CCollider* Collider)
{
	m_pCard = (CCard*)result.DestObject;
	m_HeroInthebox = true;
}

void CSelectCard::CollisionEndNormal(const HitResult& result, CCollider* Collider)
{
	m_NormalInthebox = false;
}

void CSelectCard::CollisionEndHero(const HitResult& result, CCollider* Collider)
{
	m_HeroInthebox = false;
}

void CSelectCard::CollisionEndMouse(const Vector2& result, CCollider* Collider)
{


}
