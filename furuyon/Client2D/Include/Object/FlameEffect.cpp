
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

bool CFlameEffect::m_staticEnd = true;
CFlameEffect::CFlameEffect()
{
	m_End = true;
	m_Dir = 1;
}

CFlameEffect::CFlameEffect(const CFlameEffect& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CFlameEffect::~CFlameEffect()
{
}


void CFlameEffect::Start()
{
	CGameObject::Start();
	m_TempEndpos = m_Particle->GetWorldPos();
}

bool CFlameEffect::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");
	m_Distortion = CreateObjectComponent<CDistortionComponent>("Distortion");

	m_Particle->SetParticle("FlameParticle");

	m_Particle->SetRelativePos(Vector3(0.f, 0.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.5f);
	m_Particle->SetSpawnTime(0.0001f);
	m_Particle->SetGravityEnable(false);

	SetRootComponent(m_Particle);

	m_Distortion->SetTargetMaterial(m_Particle->GetMaterial(0));
	m_Distortion->EnableDistortion(false);
	m_Particle->SetDistortion(false);
	//m_Distortion->SetTargetPrimitive(m_Particle);

	SetLifeTime(0.f);
	
	return true;
}

void CFlameEffect::Update(float DeltaTime)
{
	if (m_Dir == 1)
	{
		Vector3 Endpoint = m_TempEndpos + Vector3(85.f, 0.f, 0.f);
		Endpoint = Endpoint - m_Particle->GetWorldPos();
		if (Endpoint.x >= 0.f)
		{
			m_Particle->AddRelativePos(Endpoint.x * DeltaTime * 5.f + DeltaTime * 10.f, 0.f, 0.f);
		}
		else
		{
			if (m_End)
			{
				m_FrontButton->SetClaer(true);
				m_End = false;
			}

		}

	}
	else if (m_Dir == 2)
	{
		Vector3 Endpoint = m_TempEndpos + Vector3(0.f, 85.f, 0.f);
		Endpoint = Endpoint - m_Particle->GetWorldPos();
		if (Endpoint.y >= 0.f)
		{
			m_Particle->AddRelativePos(0.f, Endpoint.y * DeltaTime * 5.f + DeltaTime * 10.f, 0.f);
		}
		else
		{
			if (m_End)
			{
				m_FrontButton->SetClaer(true);
				m_End = false;
			}

		}

	}
	else if (m_Dir == 3)
	{
		Vector3 Endpoint = m_TempEndpos + Vector3(-85.f, 0.f, 0.f);
		Endpoint = Endpoint - m_Particle->GetWorldPos();
		if (Endpoint.x <= 0.f)
		{
			m_Particle->AddRelativePos(Endpoint.x * DeltaTime * 5.f - DeltaTime * 10.f, 0.f, 0.f);
		}
		else
		{
			if (m_End)
			{
				m_FrontButton->SetClaer(true);
				m_End = false;
			}

		}
	}
	
	CGameObject::Update(DeltaTime);
}

void CFlameEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CFlameEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CFlameEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CFlameEffect* CFlameEffect::Clone()
{
	return new CFlameEffect(*this);
}

void CFlameEffect::Animation2DNotify(const std::string& Name)
{
}
