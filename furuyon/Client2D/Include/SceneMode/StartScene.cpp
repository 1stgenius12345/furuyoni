
#include "StartScene.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "../UI/StartHUDWidget.h"
#include "../Object/FlameEffect.h"
#include "../Object/StartMapObj.h"
#include "../Object/flower.h"
#include "Resource/ResourceManager.h"
CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	CResourceManager::GetInst()->SoundPause("IntroSound");
	CResourceManager::GetInst()->SoundPause("fightbgm");
	CResourceManager::GetInst()->SoundPause("selectbgm");
	CResourceManager::GetInst()->SoundPlay("IntroSound");
	CreateMaterial();
	CreateParticle();

	m_pScene->GetResource()->LoadSound("UI", false, "ButtonMouseOn",
		"titlestart.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "Mana2",
		"effect/Mana.wav");
	CStartMapObj* pStartMapjJob = m_pScene->SpawnObject<CStartMapObj>("MapObj");
	for (int i = 0; i < 200; ++i)
	{
		CFlower* flower = m_pScene->SpawnObject<CFlower>("flower");
		flower->SetStartMapObj(pStartMapjJob);
	}
	
	CStartHUDWidget* Widget = m_pScene->GetViewport()->AddWindow<CStartHUDWidget>("StartHUD");
	Widget->SetMapObj(pStartMapjJob);

	
	
		

	return true;
}


void CStartScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateMaterial("PlayerChild");
	m_pScene->GetResource()->AddMaterialTexture("PlayerChild", "PlayerChild",
		TEXT("Teemo.jpg"));

	m_pScene->GetResource()->CreateMaterial("Snow");
	m_pScene->GetResource()->AddMaterialTexture("Snow", "Snow",
		TEXT("Particle/unnamed.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Snow", true);
	//m_pScene->GetResource()->SetMaterialOpacity("DefaultMaterial", 0.3f);

	m_pScene->GetResource()->CreateMaterial("Flame");
	m_pScene->GetResource()->AddMaterialTexture("Flame", "Flame",
		TEXT("Particle/unnamed.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Flame", true);

}

void CStartScene::CreateParticle()
{
	CMaterial* SnowMaterial = m_pScene->GetResource()->FindMaterial("Snow");

	m_pScene->GetResource()->CreateParticle("TestParticle");
	m_pScene->GetResource()->SetParticleMaterial("TestParticle", SnowMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("TestParticle", 1000);
	m_pScene->GetResource()->SetParticleStartColor("TestParticle", 0.68627f, 0.8745f, 0.89411f, 0.8f);
	m_pScene->GetResource()->SetParticleEndColor("TestParticle", 0.68627f, 0.8745f, 0.89411f, 0.f);
	m_pScene->GetResource()->SetParticleStartScale("TestParticle", 100.f, 100.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("TestParticle", 20.f, 20.f, 1.f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("TestParticle", 2.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("TestParticle", 4.f);
	m_pScene->GetResource()->SetParticleRange("TestParticle", 100.f, 0.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("TestParticle", 100.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("TestParticle", 200.f);
	m_pScene->GetResource()->SetParticleMoveEnable("TestParticle", true);
	m_pScene->GetResource()->SetParticle2D("TestParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("TestParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("TestParticle", 0.f, 0.f, 90.f);

	CMaterial* FlameMaterial = m_pScene->GetResource()->FindMaterial("Flame");

	m_pScene->GetResource()->CreateParticle("FlameParticle");
	m_pScene->GetResource()->SetParticleMaterial("FlameParticle", FlameMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("FlameParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("FlameParticle", 0.7529f, 0.7529f, 0.7529f, 1.5f);
	m_pScene->GetResource()->SetParticleEndColor("FlameParticle", 0.7529f, 0.7529f, 0.7529f, 1.5f);
	m_pScene->GetResource()->SetParticleStartScale("FlameParticle", 35.f/3.f, 35.f / 3.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("FlameParticle", 35.f / 3.f, 35.f / 3.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.2f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.2f);
	m_pScene->GetResource()->SetParticleRange("FlameParticle", 100.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("FlameParticle", 10.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("FlameParticle", 10.f);
	m_pScene->GetResource()->SetParticleMoveEnable("FlameParticle", true);
	m_pScene->GetResource()->SetParticle2D("FlameParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("FlameParticle", 0.74314f, -0.61566f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("FlameParticle", 0.f, 0.f, 0.f);

}
