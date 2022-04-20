#include "SpellCard.h"

CSpellCard::CSpellCard() :
	m_SpellTriger(0)
{
	m_CardType = Card_Type::Spell;
}

CSpellCard::CSpellCard(const CSpellCard& obj) :
	CCard(obj)
{
	m_SpellTriger = obj.m_SpellTriger;
}

CSpellCard::~CSpellCard()
{
}

void CSpellCard::Start()
{
	CCard::Start();
}

bool CSpellCard::Init()
{
	CCard::Init();

	return true;
}

void CSpellCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);
}

void CSpellCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CSpellCard::Collision(float DeltaTime)
{
	CCard::Collision(DeltaTime);
}

void CSpellCard::Render(float DeltaTime)
{
	CCard::Render(DeltaTime);
}

CSpellCard* CSpellCard::Clone()
{
	return new CSpellCard(*this);
}

void CSpellCard::Animation2DNotify(const std::string& Name)
{
}

void CSpellCard::CreateCardSetting()
{// ����� ����
	if (Card_Class::Normal == m_CardClass)
	{
		switch (m_HeroIndex)
		{
		// ������
		case 1:
			switch (m_CardIndex)
			{
			// ���
			case 4:
				SpellCardSetting(0,0,0);
				break;

			default:
				break;
			}
			break;
		// ����
		case 3:
			switch (m_CardIndex)
			{
			// 
			case 3:
				SpellCardSetting(0, 0, 0);
				break;

			default:
				break;
			}
			break;
		case 8:
			switch (m_CardIndex)
			{
				// ���ٴ� �䳢
			case 2:
				SpellCardSetting(0, 0, 0);
				break;
				// ������
			case 3:
				SpellCardSetting(0, 1, 0);
				break;
				// ��ä ������
			case 4:
				SpellCardSetting(0, 0, 1);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	//  ������ ����
	else
	{
		switch (m_HeroIndex)
		{
		case 1:
			switch (m_CardIndex)
			{
			// �ʹ迡�� �����
			case 2:
				SpellCardSetting(1, 0, 0,2);
				break;
			default:
				break;
			}
			break;
		// ���̳�
		case 3:
			switch (m_CardIndex)
			{
			// ����ȣ��
			case 0:
				SpellCardSetting(0, 0, 0, 6);
				break;
			case 1:
				SpellCardSetting(0, 0, 0, 8);
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (m_CardIndex)
			{
			case 3:
				SpellCardSetting(0, 0, 0, 2);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

}

void CSpellCard::SpellCardSetting(int triger, int dae, int jeo)
{
	m_SpellTriger = triger;
	m_Daeung = dae;
	m_Tenreok = jeo;
}

void CSpellCard::SpellCardSetting(int triger, int dae, int jeo, int mana)
{
	m_SpellTriger = triger;
	m_Daeung = dae;
	m_Tenreok = jeo;
	m_ManaCost = mana;
}

