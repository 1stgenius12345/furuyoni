#include "tokoyoDeck.h"

CtokoyoDeck::CtokoyoDeck()
{
}

CtokoyoDeck::CtokoyoDeck(const CtokoyoDeck& obj) :
	CDeck(obj)
{
}

CtokoyoDeck::~CtokoyoDeck()
{
}

void CtokoyoDeck::Start()
{
	CDeck::Start();
}

bool CtokoyoDeck::Init()
{
	m_HeroIndex = 8;
	//CDeck::Init();

	// 1¹øÄ«µå
	CreateCard(0, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(1, m_HeroIndex, Card_Type::Attack, Card_Class::Normal);
	CreateCard(2, m_HeroIndex, Card_Type::Spell, Card_Class::Normal);
	CreateCard(3, m_HeroIndex, Card_Type::Spell, Card_Class::Normal);
	CreateCard(4, m_HeroIndex, Card_Type::Spell, Card_Class::Normal);
	CreateCard(5, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(6, m_HeroIndex, Card_Type::Building, Card_Class::Normal);
	CreateCard(0, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(1, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(2, m_HeroIndex, Card_Type::Attack, Card_Class::Hero);
	CreateCard(3, m_HeroIndex, Card_Type::Spell, Card_Class::Hero);

	SelectSetting();



	return true;
}

void CtokoyoDeck::Update(float DeltaTime)
{
	CDeck::Update(DeltaTime);

}

void CtokoyoDeck::PostUpdate(float DeltaTime)
{
	CDeck::PostUpdate(DeltaTime);
}

void CtokoyoDeck::Collision(float DeltaTime)
{
	CDeck::Collision(DeltaTime);
}

void CtokoyoDeck::Render(float DeltaTime)
{
	CDeck::Render(DeltaTime);
}

CtokoyoDeck* CtokoyoDeck::Clone()
{
	return new CtokoyoDeck(*this);
}

void CtokoyoDeck::Animation2DNotify(const std::string& Name)
{
}
