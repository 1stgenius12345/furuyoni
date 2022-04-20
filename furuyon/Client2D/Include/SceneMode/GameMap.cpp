#include "GameMap.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "../UI/StartHUDWidget.h"
#include "../Object/Deck.h"
#include "../UI/GameMapWindow.h"
#include "../UI/GameMapAnimation.h"
#include "../Object/GameMapObj.h"
#include "../ClientManager.h"
#include "Resource/ResourceManager.h"
#include "../UI/BackHUDWidget.h"
CGameMap::CGameMap()
{
}

CGameMap::~CGameMap()
{
}

bool CGameMap::Init()
{
	
	CResourceManager::GetInst()->SoundPause("selectbgm");
	CResourceManager::GetInst()->SoundPlay("fightbgm");








	m_pScene->GetResource()->LoadSound("UI", false, "ButtonMouseOn",
		"titlestart.wav");
	m_pScene->GetResource()->LoadSound("Effect", false, "CardtoBack",
		"effect/CardtoBack.wav");
	CGameMapAnimation* pGameMapWidget = m_pScene->GetViewport()->AddWindow<CGameMapAnimation>("pGameMapWidget");
	CDeck* pDeck = m_pScene->SpawnObject<CDeck>("Deck");
	CDeck* pDeck2 = m_pScene->SpawnObject<CDeck>("Deck2");
	pDeck->SetSelectWidget(nullptr);
	pDeck->BattleForReady();
	pGameMapWidget->Set1firstindex(CClientManager::GetInst()->Getfirst());
	pGameMapWidget->Set1secondindex(CClientManager::GetInst()->Getsecond());


	if (CClientManager::GetInst()->GetAiIndex() == 0)
	{

	}
	else
	{
		CClientManager::GetInst()->Clear();
		CClientManager::GetInst()->SetMapIndex();
	}

	pDeck2->BattleForReady();
	pGameMapWidget->Set2firstindex(CClientManager::GetInst()->Getfirst());
	pGameMapWidget->Set2secondindex(CClientManager::GetInst()->Getsecond());
	
	


	CClientManager::GetInst()->Clear();
	CGameMapObj* pGameMapObj = m_pScene->SpawnObject<CGameMapObj>("MapObj");
	
	pGameMapWidget->SetGameMapObj(pGameMapObj);
	pGameMapObj->SetPlayer1Deck(pDeck);
	pGameMapObj->SetPlayer2Deck(pDeck2);
	pGameMapObj->StartGameHandSetting();


	
	return true;
}
