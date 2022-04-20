
#include "StartMapObj.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "Render/RenderManager.h"
#include "TestParticle.h"
#include "LogObj.h"
#include "Input.h"
CStartMapObj::CStartMapObj() :
    m_Start2(false),
    m_BlurCount(50.f)
{
   
}

CStartMapObj::CStartMapObj(const CStartMapObj& obj) :
    CGameObject(obj)
{
   
}

CStartMapObj::~CStartMapObj()
{
}

void CStartMapObj::Start()
{
    CGameObject::Start();
}

bool CStartMapObj::Init()
{
    CGameObject::Init();
   // m_AnimationCard = m_pScene->SpawnObject<CAnimationCard>("AnimationCard");
   
 ;

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    SetRootComponent(m_Sprite);
    m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
    m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.f, 0.f, 0.f);
    m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
    m_SpriteMtrl = m_Sprite->GetMaterial(0);
    m_SpriteMtrl->AddTexture("BackGround", TEXT("BackGround.jpg"));
    m_SpriteMtrl->SetBaseColor(1.f, 1.f, 1.f, 1.f);
    m_SpriteMtrl->SetEmissiveColor(1.f, 1.f, 1.f, 1.f);
    m_SpriteMtrl->SetShader("Standard2DTextureShader");

    m_Sprite2 = CreateSceneComponent<CSpriteComponent>("Sprite2");
    m_Sprite->AddChild(m_Sprite2);
    m_Sprite2->SetRelativeScale(1453.f, 850.f, 0.f);
    m_Sprite2->SetRelativePos(0.f, -130.f, 0.f);
    m_Sprite2->SetRender2DType(Render_Type_2D::RT2D_Default);
    m_SpriteMtrl2 = m_Sprite2->GetMaterial(0);
    m_SpriteMtrl2->AddTexture("StartBackGround", TEXT("StartBackGround.png"));
    m_SpriteMtrl2->SetBaseColor(1.f, 1.f, 1.f, 1.f);
    m_SpriteMtrl2->SetEmissiveColor(1.f, 1.f, 1.f, 0.5f);
    m_SpriteMtrl2->SetEmpty(0.5f);
    m_SpriteMtrl->SetShader("Standard2DTextureShader");
 
  //  CInput::GetInst()->AddKeyCallback<CStartMapObj>("MoveUp", KT_Push, this, &CStartMapObj::MoveUp);

    return true;
}

void CStartMapObj::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
  

    if (m_Start2)
    {
        m_SpriteMtrl2->SetShader("Standard2DTextureShader");
        m_Sprite->SetRelativeScale(1280.f, 720.f, 0.f);
    }
}

void CStartMapObj::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CStartMapObj::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CStartMapObj::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CStartMapObj* CStartMapObj::Clone()
{
    return new CStartMapObj(*this);
}

void CStartMapObj::CollisionBegin(const HitResult& result, CCollider* Collider)
{
   
}

void CStartMapObj::CollisionEnd(const HitResult& result, CCollider* Collider)
{
   
}

void CStartMapObj::SetBackGround()
{
    m_Sprite2->SetRelativeScale(0.f, 0.f, 0.f);
}

void CStartMapObj::MoveUp(float DeltaTime)
{
   // m_LogObj->CreateLog(nullptr, nullptr, 3, 1);
}
