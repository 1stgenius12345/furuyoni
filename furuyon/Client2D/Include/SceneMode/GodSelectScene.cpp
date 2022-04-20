
#include "GodSelectScene.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/Teemo.h"
#include "../Object/PixelCollisionTest.h"
#include "../Object/TestParticle.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "Scene/Viewport.h"
#include "../Object/MainMap.h"
#include "../Object/Card.h"
#include "../Object/Deck.h"
#include "../UI/GodSelectHUDWidget.h"
#include "../Object/GodSelectObj.h"
#include "../Object/MagicDeck.h"
#include "../Object/WariorDeck.h"
#include "../Object/tokoyoDeck.h"
#include "../UI/AlRamWidget.h"
#include "Resource/ResourceManager.h"
#include "../UI/BackHUDWidget.h"
CGodSelectScene::CGodSelectScene()
{
}

CGodSelectScene::~CGodSelectScene()
{
}

bool CGodSelectScene::Init()
{
	CResourceManager::GetInst()->SoundPause("IntroSound");
	CResourceManager::GetInst()->SoundPause("fightbgm");
	CResourceManager::GetInst()->SoundPause("selectbgm");
	CResourceManager::GetInst()->SoundPlay("selectbgm");


	m_pScene->GetResource()->LoadSound("UI", false, "NormalHeroChange",
		"effect/NormalHeroChange.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "Select",
		"effect/Select.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "HeroSelectButoon",
		"effect/HeroSelectButoon.wav");

	CAlRamWidget* pAlRamWidget = m_pScene->GetViewport()->AddWindow<CAlRamWidget>("pAlRamWidget");
	
	
	CGodSelectObj* pSelect = m_pScene->SpawnObject<CGodSelectObj>("SelectCard");

	CDeck* pDeck = m_pScene->SpawnObject<CDeck>("Deck");
	pDeck->ShowCard();
	pDeck->SetHeroIndex(1);
	pDeck->SetDonSelectTime();
	
	pSelect->GetSelectWidget()->SetDeck(pDeck);
	




	CBackHUDWidget* Widget = m_pScene->GetViewport()->AddWindow<CBackHUDWidget>("BackHUD");




	return true;
}
