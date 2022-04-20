
#include "StageObj.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "Render/RenderManager.h"
#include "TestParticle.h"
#include "LogObj.h"
#include "Input.h"
#include "StageButton.h"
CStageObj::CStageObj() :
    m_Start2(false),
    m_BlurCount(50.f)
{

}

CStageObj::CStageObj(const CStageObj& obj) :
    CGameObject(obj)
{

}

CStageObj::~CStageObj()
{
}

void CStageObj::Start()
{
    CGameObject::Start();
}

bool CStageObj::Init()
{
    CGameObject::Init();
    // m_AnimationCard = m_pScene->SpawnObject<CAnimationCard>("AnimationCard");

    ;

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    SetRootComponent(m_Sprite);
    m_Sprite->SetRelativeScale(1280.f*2.f, 720.f * 2.f, 0.f);
    m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.f, 0.f, 0.f);
    m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
    m_SpriteMtrl = m_Sprite->GetMaterial(0);
    m_SpriteMtrl->AddTexture("BackGround", TEXT("BackGround.jpg"));
    m_SpriteMtrl->SetBaseColor(1.2f, 1.2f, 1.2f, 1.2f);
    m_SpriteMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
    m_SpriteMtrl->SetShader("Standard2DTextureShader");


    CStageButton* pStageButton =  m_pScene->SpawnObject<CStageButton>("stageButton");
    pStageButton->SetRelativePos(600.f,300.f,0.f);
    pStageButton->SetStageObj(this);
    pStageButton->SetButtonIndex(1);
    //  CInput::GetInst()->AddKeyCallback<CStageObj>("MoveUp", KT_Push, this, &CStageObj::MoveUp);

    return true;
}

void CStageObj::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);


  
}

void CStageObj::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CStageObj::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CStageObj::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CStageObj* CStageObj::Clone()
{
    return new CStageObj(*this);
}

void CStageObj::CollisionBegin(const HitResult& result, CCollider* Collider)
{

}

void CStageObj::CollisionEnd(const HitResult& result, CCollider* Collider)
{

}

void CStageObj::SetBackGround()
{
    m_Sprite2->SetRelativeScale(0.f, 0.f, 0.f);
}

void CStageObj::MoveUp(float DeltaTime)
{
    // m_LogObj->CreateLog(nullptr, nullptr, 3, 1);
}

void CStageObj::CreateButton()
{
 
}
