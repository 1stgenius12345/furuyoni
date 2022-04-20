
#include "flower.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Device.h"
CFlower::CFlower()
{
}

CFlower::CFlower(const CFlower& obj) :
	CGameObject(obj)
{

}

CFlower::~CFlower()
{
}

void CFlower::Start()
{
	CGameObject::Start();
}

bool CFlower::Init()
{
	CGameObject::Init();
	float random = gaussianRandom(); // -3 ~ 3; 가우시안랜덤

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(52.f + random * 52.f * 1.f, 38.f + random * 38.f * 1.f, 0.f);
	m_Sprite->SetRelativePos(1280.f + random * 740.f * 3.f, 360.f + random * 360.f * 4.f, 0.1f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);


	m_SpriteMtrl = m_Sprite->GetMaterial(0);
	m_SpriteMtrl->AddTexture("Particle", TEXT("Particle/flower.png"));
	m_SpriteMtrl->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.5f);
	m_SpriteMtrl->SetShader("Standard2DtitleShader");


	return true;
}

void CFlower::Update(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	float random = -50.f * DeltaTime * (gaussianRandom() + 3.f) - 50.f * DeltaTime;

	Vector2 ratio = Vector2(m_Sprite->GetRelativeScale().x / 52.f, m_Sprite->GetRelativeScale().y / 38.f);
	CGameObject::Update(DeltaTime);
	//	m_Sprite->AddRelativeRotationX(random);
	//	m_Sprite->AddRelativeRotationY(random);
	m_Sprite->AddRelativeRotationZ(random * ratio.x);
	m_Sprite->AddRelativePos(random * ratio.x, random * ratio.y, 0.f);



	if (m_Sprite->GetRelativePos().y < -100.f)
	{
		m_Sprite->SetRelativePos(2.f * Center.x - m_Sprite->GetRelativePos().x, -m_Sprite->GetRelativePos().y + 2.f * Center.y, 0.f);

	}
}

void CFlower::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CFlower::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CFlower::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CFlower* CFlower::Clone()
{
	return new CFlower(*this);
}

void CFlower::Animation2DNotify(const std::string& Name)
{
}
