#include "WariorDeck.h"

CWariorDeck::CWariorDeck()
{
}

CWariorDeck::CWariorDeck(const CWariorDeck& obj) :
	CDeck(obj)
{
}

CWariorDeck::~CWariorDeck()
{
}

void CWariorDeck::Start()
{
	CDeck::Start();
}

bool CWariorDeck::Init()
{
	m_HeroIndex = 3;
	//CDeck::Init();

	CreateCard(0, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(1, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(2, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(3, m_HeroIndex, Card_Type::Spell, Card_Class::Normal);
	CreateCard(4, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(5, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(6, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(0, m_HeroIndex, Card_Type::Spell, Card_Class::Hero);
	CreateCard(1, m_HeroIndex, Card_Type::Spell, Card_Class::Hero);
	CreateCard(2, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(3, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);

	SelectSetting();



	return true;
}

void CWariorDeck::Update(float DeltaTime)
{
	CDeck::Update(DeltaTime);

}

void CWariorDeck::PostUpdate(float DeltaTime)
{
	CDeck::PostUpdate(DeltaTime);
}

void CWariorDeck::Collision(float DeltaTime)
{
	CDeck::Collision(DeltaTime);
}

void CWariorDeck::Render(float DeltaTime)
{
	CDeck::Render(DeltaTime);
}

CWariorDeck* CWariorDeck::Clone()
{
	return new CWariorDeck(*this);
}

void CWariorDeck::Animation2DNotify(const std::string& Name)
{
}
