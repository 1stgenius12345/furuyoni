#include "Deck.h"
#include "Card.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "MagicDeck.h"
#include "WariorDeck.h"
#include "AttackCard.h"
#include "SpellCard.h"
#include "BuildingCard.h"
#include "tokoyoDeck.h"
CDeck::CDeck() :
	m_SelectWidget(nullptr),
	m_bRendernormal(true),
	m_HeroIndex(0)
{
	

}



CDeck::CDeck(const CDeck& obj) :
	CGameObject(obj)
{
	//*this = obj;
	//m_vecNormalCard.clear();
	//size_t Size = obj.m_vecNormalCard.size();
	//for (size_t i = 0; i < Size; ++i)
	//{
	//	CCard* CloneObj = m_vecNormalCard[i]->Clone();

	//	CloneObj->SetDeck(this);
	//	m_vecNormalCard.push_back(CloneObj);
	//	
	//}
}

CDeck::~CDeck()
{

}

void CDeck::BattleForReady()
{
	CDeck* Deck;
	int first = CClientManager::GetInst()->Getfirst();
	switch (first)
	{
	case 1:
		Deck = m_pScene->SpawnObject<CMagicDeck>("MagicDeck1");

		SelectCardInsert1(Deck);
		break;
	case 3:
		Deck = m_pScene->SpawnObject<CWariorDeck>("WariorDeck1");
	
		SelectCardInsert1(Deck);
		break;
	case 8:
		Deck = m_pScene->SpawnObject<CtokoyoDeck>("tokoyoDeck");

		SelectCardInsert1(Deck);
		break;
		
	}


	int second = CClientManager::GetInst()->Getsecond();
	switch (second)
	{
	case 1:
		Deck = m_pScene->SpawnObject<CMagicDeck>("MagicDeck2");
		
		SelectCardInsert2(Deck);
		break;
	case 3:
		Deck = m_pScene->SpawnObject<CWariorDeck>("WariorDeck2");
	
		SelectCardInsert2(Deck);
		break;
	case 8:
		Deck = m_pScene->SpawnObject<CtokoyoDeck>("tokoyoDeck2");
		
		SelectCardInsert2(Deck);
		break;
	}


	SettingGone();

	//HandSetting();

}

void CDeck::Start()
{
	CGameObject::Start();


}

bool CDeck::Init()
{
	CGameObject::Init();

	





	//SelectSetting();



	return true;
}

void CDeck::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	// 마우스에 인식





}

void CDeck::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDeck::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDeck::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CDeck* CDeck::Clone()
{
	return new CDeck(*this);
}

void CDeck::Animation2DNotify(const std::string& Name)
{

}

void CDeck::MoveUp(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CDeck::MoveDown(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CDeck::RotationZ(float DeltaTime)
{
	AddRelativeRotationZ(360.f * DeltaTime);
}

void CDeck::RotationZInv(float DeltaTime)
{
	AddRelativeRotationZ(-360.f * DeltaTime);
}

void CDeck::Fire(float DeltaTime)
{

}

void CDeck::Triple(float DeltaTime)
{

}

void CDeck::Skill2(float DeltaTime)
{

}

void CDeck::AnimationFrameEnd(const std::string& Name)
{

}

void CDeck::CollisionBeginMouse(const Vector2& result, CCollider* Collider)
{


}

void CDeck::CollisionEndMouse(const Vector2& result, CCollider* Collider)
{


}

void CDeck::SetBack()
{
	size_t NormalSize = m_vecNormalCard.size();
	for (int i = 0; i < NormalSize; ++i)
	{
		m_vecNormalCard[i]->SetBack();
		m_vecNormalCard[i]->SetLookable(true);
	}
	
	size_t HeroSize = m_vecHeroCard.size();
	for (int i = 0; i < HeroSize; ++i)
	{
		m_vecHeroCard[i]->SetBack();
		m_vecHeroCard[i]->SetLookable(true);
	}
}

void CDeck::SetPlayer2()
{
	SetBack();
	size_t NormalSize = m_vecNormalCard.size();
	for (int i = 0; i < NormalSize; ++i)
	{
		m_vecNormalCard[i]->SetMove(false);
		m_vecNormalCard[i]->SetLookable(false);
	}

	size_t HeroSize = m_vecHeroCard.size();
	for (int i = 0; i < HeroSize; ++i)
	{
		m_vecHeroCard[i]->SetMove(false);
		m_vecHeroCard[i]->SetLookable(false);
	}

}

void CDeck::SetTexByHeroIndex(int index)
{
	for (int i = 0; i < m_vecNormalCard.size(); ++i)
	{
		m_vecNormalCard[i]->SetHeroIndex(index);
		
		m_vecNormalCard[i]->CreateTex();
	}
	for (int i = 0; i < m_vecHeroCard.size(); ++i)
	{
		m_vecHeroCard[i]->SetHeroIndex(index);
		m_vecHeroCard[i]->CreateTex();
	}
}

void CDeck::SetDonSelectTime()
{
	for (int i = 0; i < m_vecNormalCard.size(); ++i)
	{
		m_vecNormalCard[i]->SetSelectTime(false);

	
	}
	for (int i = 0; i < m_vecHeroCard.size(); ++i)
	{
		m_vecHeroCard[i]->SetSelectTime(false);
	
	}
}

void CDeck::ShowCard()
{// 1번카드
	CCard* card1 = m_pScene->SpawnObject<CCard>("card1");
	AddNormal1Card(card1);
	//2번카드
	CCard* card2 = m_pScene->SpawnObject<CCard>("card2");

	AddNormal1Card(card2);
	//3번카드
	CCard* card3 = m_pScene->SpawnObject<CCard>("card3");

	AddNormal1Card(card3);

	//4번카드
	CCard* card4 = m_pScene->SpawnObject<CCard>("card4");

	AddNormal1Card(card4);

	//5번카드
	CCard* card5 = m_pScene->SpawnObject<CCard>("card5");

	AddNormal1Card(card5);

	//6번카드
	CCard* card6 = m_pScene->SpawnObject<CCard>("card6");

	AddNormal1Card(card6);

	//7번카드
	CCard* card7 = m_pScene->SpawnObject<CCard>("card7");

	AddNormal1Card(card7);

	//영웅 1번카드
	CCard* Herocard1 = m_pScene->SpawnObject<CCard>("Herocard1");

	Herocard1->SetHero();
	AddHero1Card(Herocard1);

	//영웅 2번카드
	CCard* Herocard2 = m_pScene->SpawnObject<CCard>("Herocard2");

	Herocard2->SetHero();
	AddHero1Card(Herocard2);

	//영웅 3번카드
	CCard* Herocard3 = m_pScene->SpawnObject<CCard>("Herocard3");

	Herocard3->SetHero();
	AddHero1Card(Herocard3);

	//영웅 4번카드
	CCard* Herocard4 = m_pScene->SpawnObject<CCard>("Herocard4");

	Herocard4->SetHero();
	AddHero1Card(Herocard4);
}

CCard* CDeck::CreateCard(int Cardindex, int Heroindex, Card_Type type, Card_Class cardcalss)
{
	CCard* card1;
	if (type == Card_Type::Attack)
	{
		CAttackCard* cardtemp = m_pScene->SpawnObject<CAttackCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}
	else if (type == Card_Type::Spell)
	{
		CSpellCard* cardtemp = m_pScene->SpawnObject<CSpellCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}
	
	else if (type == Card_Type::Building)
	{
		CBuildingCard* cardtemp = m_pScene->SpawnObject<CBuildingCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}
	else
		card1 = m_pScene->SpawnObject<CCard>("card1");



	if (cardcalss == Card_Class::Normal)
		m_vecNormalCard.push_back(card1);
	else
		m_vecHeroCard.push_back(card1);

	return card1;
}

CCard* CDeck::CreateCardNotPush( int Cardindex,  int Heroindex,  Card_Type type,  Card_Class cardcalss)
{
	CCard* card1;
	if (type == Card_Type::Attack)
	{
		CAttackCard* cardtemp = m_pScene->SpawnObject<CAttackCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}
	else if (type == Card_Type::Spell)
	{
		CSpellCard* cardtemp = m_pScene->SpawnObject<CSpellCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}

	else if (type == Card_Type::Building)
	{
		CBuildingCard* cardtemp = m_pScene->SpawnObject<CBuildingCard>("card1");
		cardtemp->CreatCard(this, Cardindex, Heroindex, type, cardcalss);
		card1 = cardtemp;
	}
	else
		card1 = m_pScene->SpawnObject<CCard>("card1");



	return card1;
}

void CDeck::SelectCardInsert1(CDeck* deck)
{
	deck->SettingGone();
	for (int i = 0; i < 7; ++i)
	{
		if (CClientManager::GetInst()->GetNormal1Card(i) != -1)
		{

			AddNormalCard(deck->GetNormalCardByindex(CClientManager::GetInst()->GetNormal1Card(i)));

		}
		if (CClientManager::GetInst()->GetHero1Card(i) != -1)
		{
			AddHeroCard(deck->GetHeroCardByindex(CClientManager::GetInst()->GetHero1Card(i)));

		}
	}
}

void CDeck::SelectCardInsert2(CDeck* deck)
{
	deck->SettingGone();
	for (int i = 0; i < 7; ++i)
	{
		if (CClientManager::GetInst()->GetNormal2Card(i) != -1)
		{
			AddNormalCard(deck->GetNormalCardByindex(CClientManager::GetInst()->GetNormal2Card(i)));

		}
		if (CClientManager::GetInst()->GetHero2Card(i) != -1)
		{
			AddHeroCard(deck->GetHeroCardByindex(CClientManager::GetInst()->GetHero2Card(i)));
		}
	}
}
