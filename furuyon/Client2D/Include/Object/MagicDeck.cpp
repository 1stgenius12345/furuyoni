#include "MagicDeck.h"

CMagicDeck::CMagicDeck()
{
	m_HeroIndex = 1;
}

CMagicDeck::CMagicDeck(const CMagicDeck& obj) :
	CDeck(obj)
{
}

CMagicDeck::~CMagicDeck()
{
}

void CMagicDeck::Start()
{
	CDeck::Start();
}

bool CMagicDeck::Init()
{
	m_HeroIndex = 1;
	//CDeck::Init();

	// 1¹øÄ«µå
	CreateCard(0, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(1, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(2, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(3, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(4, m_HeroIndex, Card_Type::Spell, Card_Class::Normal);
	CreateCard(5, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(6, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(0, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(1, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(2, m_HeroIndex, Card_Type::Spell, Card_Class::Hero);
	CreateCard(3, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);

	SelectSetting();



	return true;
}

void CMagicDeck::Update(float DeltaTime)
{
	CDeck::Update(DeltaTime);

}

void CMagicDeck::PostUpdate(float DeltaTime)
{
	CDeck::PostUpdate(DeltaTime);
}

void CMagicDeck::Collision(float DeltaTime)
{
	CDeck::Collision(DeltaTime);
}

void CMagicDeck::Render(float DeltaTime)
{
	CDeck::Render(DeltaTime);
}

CMagicDeck* CMagicDeck::Clone()
{
	return new CMagicDeck(*this);
}

void CMagicDeck::Animation2DNotify(const std::string& Name)
{
}
