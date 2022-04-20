
#include "TutorialScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "Scene/Viewport.h"

#include "Resource/ResourceManager.h"

#include "../UI/BackHUDWidget.h"
#include "../Object/TutorialObj.h"

CTutorialScene::CTutorialScene()
{
}

CTutorialScene::~CTutorialScene()
{
}

bool CTutorialScene::Init()
{
	CreateMaterial();
	CreateParticle();
	CResourceManager::GetInst()->SoundPause("IntroSound");
	CResourceManager::GetInst()->SoundPause("fightbgm");
	CResourceManager::GetInst()->SoundPause("selectbgm");


	m_pScene->GetResource()->LoadSound("UI", false, "NormalHeroChange",
		"effect/NormalHeroChange.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "Select",
		"effect/Select.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "HeroSelectButoon",
		"effect/HeroSelectButoon.wav");


	CTutorialObj* pTutorialObj = m_pScene->SpawnObject<CTutorialObj>("pTutorialObj");



	return true;
}

void CTutorialScene::CreateMaterial()
{

	m_pScene->GetResource()->CreateMaterial("Snow");
	m_pScene->GetResource()->AddMaterialTexture("Snow", "Snow",
		TEXT("Particle/Bubbles50px.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Snow", true);
	//m_pScene->GetResource()->SetMaterialOpacity("DefaultMaterial", 0.3f);

	m_pScene->GetResource()->CreateMaterial("Flame");
	m_pScene->GetResource()->AddMaterialTexture("Flame", "Flame",
		TEXT("Particle/particle_00.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Flame", true);



}

void CTutorialScene::CreateParticle()
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
	m_pScene->GetResource()->SetParticleMoveEnable("TestParticle", false);
	m_pScene->GetResource()->SetParticle2D("TestParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("TestParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("TestParticle", 0.f, 0.f, 90.f);

	CMaterial* FlameMaterial = m_pScene->GetResource()->FindMaterial("Flame");

	m_pScene->GetResource()->CreateParticle("FlameParticle");
	m_pScene->GetResource()->SetParticleMaterial("FlameParticle", FlameMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("FlameParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("FlameParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleEndColor("FlameParticle", 1.f, 0.7529f, 0.7961f, 1.f);
	m_pScene->GetResource()->SetParticleStartScale("FlameParticle", 5.f, 5.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("FlameParticle", 5.f, 5.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 10000.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 10000.f);
	m_pScene->GetResource()->SetParticleRange("FlameParticle", 0.f, 0.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("FlameParticle", 0.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("FlameParticle", 0.f);
	m_pScene->GetResource()->SetParticleMoveEnable("FlameParticle", false);
	m_pScene->GetResource()->SetParticle2D("FlameParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("FlameParticle", 0.74314f, -0.61566f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("FlameParticle", 0.f, 0.f, 0.f);
}
