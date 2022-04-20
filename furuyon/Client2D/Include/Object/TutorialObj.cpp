
#include "TutorialObj.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "Render/RenderManager.h"
#include "TestParticle.h"
#include "LogObj.h"
#include "Input.h"
#include "StageButton.h"
#include "Scene/SceneManager.h"
CTutorialObj::CTutorialObj() 
{
    m_index = 1;
}

CTutorialObj::CTutorialObj(const CTutorialObj& obj) :
    CGameObject(obj)
{

}

CTutorialObj::~CTutorialObj()
{
}

void CTutorialObj::Start()
{
    CGameObject::Start();
}

bool CTutorialObj::Init()
{
    CGameObject::Init();
    // m_AnimationCard = m_pScene->SpawnObject<CAnimationCard>("AnimationCard");

    ;

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_TutorialWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_TutorialWidgetComponent");


    SetRootComponent(m_Sprite);
    m_Sprite->SetRelativeScale(1280.f, 720.f, 0.f);
    m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.f, 0.f, 0.f);
    m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
    m_SpriteMtrl = m_Sprite->GetMaterial(0);
    m_SpriteMtrl->AddTexture("t1", TEXT("tutorial/1.png"));
    m_SpriteMtrl->SetBaseColor(1.2f, 1.2f, 1.2f, 1.2f);
    m_SpriteMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
    m_SpriteMtrl->SetShader("Standard2DTextureShader");



    // 기본동작 위젯 관리
    m_TutorialWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
    m_TutorialWidget = m_TutorialWidgetComponent->CreateWidget<CTutorialWidget>("m_TutorialWidget");
    m_Sprite->AddChild(m_TutorialWidgetComponent);
    m_TutorialWidget->SetTutorialObj(this);


    return true;
}

void CTutorialObj::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);



}

void CTutorialObj::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CTutorialObj::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CTutorialObj::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CTutorialObj* CTutorialObj::Clone()
{
    return new CTutorialObj(*this);
}

void CTutorialObj::Go()
{
    CSceneManager::GetInst()->CreateNextScene();
    CSceneManager::GetInst()->SetSceneMode<CStartScene>(false);
}


void CTutorialObj::CreateTex()
{
    TCHAR tex[20] = { 0 };
    std::string std_str;

    _tcsncat_s(tex, TEXT("tutorial/"), 9);


    std_str.push_back('t');

    TCHAR ds1[3] = { 0 };
    _stprintf_s(ds1, _countof(ds1), TEXT("%d"), m_index);

    if(m_index >= 10)
        _tcsncat_s(tex, ds1, 2);
    else
      _tcsncat_s(tex, ds1, 1);
    std_str.push_back(m_index + 0);
 
    _tcsncat_s(tex, TEXT(".png"), 4);


    m_SpriteMtrl->AddTexture(std_str, tex);
}
