

#include "GodSelectObj.h"
#include "Deck.h"
#include "Card.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "../UI/PlayerWorldInfoWidget.h"


CGodSelectObj::CGodSelectObj() :
	m_NormalInthebox(false),
	m_HeroInthebox(false),
	m_pCard(nullptr)
{


}



CGodSelectObj::CGodSelectObj(const CGodSelectObj& obj) :
	CGameObject(obj)
{

}

CGodSelectObj::~CGodSelectObj()
{

}

void CGodSelectObj::Start()
{
	CGameObject::Start();


}

bool CGodSelectObj::Init()
{
	CGameObject::Init();

	m_NormalSelect = CreateSceneComponent<CColliderBox2D>("NormalSelect");
	m_HeroSelect = CreateSceneComponent<CColliderBox2D>("HeroSelect");
	m_SelectWidgetComponent = CreateSceneComponent<CWidgetComponent>("SelectWidget");




	CSpriteComponent* m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_GameMapBackGround = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_CardBackGround = CreateSceneComponent<CSpriteComponent>("m_CardBackGround");
	m_SelectMegami = CreateSceneComponent<CSpriteComponent>("m_SelectMegami");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
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
	m_GameMapBackGround->SetRelativePos(640., 360.f, 0.f);
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



	// 카드뒷배경
	m_SelectMegami->SetRelativeScale(685.f / 3.5f, 1344.f / 3.5f, 0.f);
	m_SelectMegami->SetPivot(0.f, 0.f, 0.f);
	m_SelectMegami->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_SelectMegami->SetRelativePos(100.f, 200.f, 0.f);
	m_SpriteMtrl4 = m_SelectMegami->GetMaterial(0);
	m_SpriteMtrl4->AddTexture("card/megami/1.png", TEXT("card/megami/1.png"));
	m_SpriteMtrl4->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_SpriteMtrl4->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_SelectMegami);





	//m_SelectHero = CreateWidget<CImage>("m_SelectHero");
	//m_SelectHero->SetTexture("card/megami/1.png", TEXT("card/megami/1.png"));
	//m_SelectHero->SetPos(100.f, 200.f);
	//m_SelectHero->SetSize(685.f / 3.5f, 1344.f / 3.5f);



	// 위젯 관리 ////////////////////////////////////////////////////////////////////////

	// 기본동작 위젯 관리
	m_SelectWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_SelectWidget = m_SelectWidgetComponent->CreateWidget<CGodSelectHUDWidget>("FocusWidget");
	m_SelectWidget->SetSelectCard(this);
	m_Sprite->AddChild(m_SelectWidgetComponent);













	m_NormalSelect->AddCollisionCallbackFunction<CGodSelectObj>(Collision_State::Begin, this,
		&CGodSelectObj::CollisionBeginNormal);
	m_NormalSelect->AddCollisionCallbackFunction<CGodSelectObj>(Collision_State::End, this,
		&CGodSelectObj::CollisionEndNormal);


	m_HeroSelect->AddCollisionCallbackFunction<CGodSelectObj>(Collision_State::Begin, this,
		&CGodSelectObj::CollisionBeginHero);
	m_HeroSelect->AddCollisionCallbackFunction<CGodSelectObj>(Collision_State::End, this,
		&CGodSelectObj::CollisionEndHero);
	return true;
}

void CGodSelectObj::Update(float DeltaTime)
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

void CGodSelectObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CGodSelectObj::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CGodSelectObj::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CGodSelectObj* CGodSelectObj::Clone()
{
	return new CGodSelectObj(*this);
}

void CGodSelectObj::Animation2DNotify(const std::string& Name)
{

}

void CGodSelectObj::MoveUp(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CGodSelectObj::MoveDown(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CGodSelectObj::RotationZ(float DeltaTime)
{
	AddRelativeRotationZ(360.f * DeltaTime);
}

void CGodSelectObj::RotationZInv(float DeltaTime)
{
	AddRelativeRotationZ(-360.f * DeltaTime);
}

void CGodSelectObj::Fire(float DeltaTime)
{

}

void CGodSelectObj::Triple(float DeltaTime)
{

}

void CGodSelectObj::Skill2(float DeltaTime)
{

}

void CGodSelectObj::AnimationFrameEnd(const std::string& Name)
{

}

void CGodSelectObj::CollisionBeginNormal(const HitResult& result, CCollider* Collider)
{
	m_pCard = (CCard*)result.DestObject;
	m_NormalInthebox = true;
}

void CGodSelectObj::CollisionBeginHero(const HitResult& result, CCollider* Collider)
{
	m_pCard = (CCard*)result.DestObject;
	m_HeroInthebox = true;
}

void CGodSelectObj::CollisionEndNormal(const HitResult& result, CCollider* Collider)
{
	m_NormalInthebox = false;
}

void CGodSelectObj::CollisionEndHero(const HitResult& result, CCollider* Collider)
{
	m_HeroInthebox = false;
}

void CGodSelectObj::CollisionEndMouse(const Vector2& result, CCollider* Collider)
{


}

void CGodSelectObj::SetMegami3(int index)
{
	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), index);

	_tcsncat_s(tex, TEXT("card/"), 5);


	_tcsncat_s(tex, TEXT("megami/"), 7);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), index);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_SpriteMtrl4->AddTexture(std_str, tex);
}
