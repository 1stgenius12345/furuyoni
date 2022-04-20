#include "Player2Ai.h"
#include "../Object/GameMapObj.h"
#include "../Object/AttackCard.h"
#include "../Object/SpellCard.h"
#include "../Object/BuildingCard.h"
CPlayer2Ai::CPlayer2Ai():
	m_GameMapObj(nullptr),
	m_LikeRange(0),
	m_LikeMana(0),
	m_DauegTime(false),
	m_PlayerAttackMin(0),
	m_PlayerAttackMax(0),
	m_PlayerAttackShiled(0),
	m_PlayerAttackLife(0),
	m_PlayerAttackClass(0),
	m_HandBack(false),
	m_Hero1(0),
	m_Hero2(0)
{
	m_EnableSpecialCard = nullptr;
}

CPlayer2Ai::CPlayer2Ai(const CPlayer2Ai& obj)
{
}

CPlayer2Ai::~CPlayer2Ai()
{
}

void CPlayer2Ai::Init()
{	// 1.5초마다 들어오는 Ai 판단소!!!
	srand(GetTickCount());
	AiHandEnable();
	// 전력을 사용할수있다면 사용하는게 좋지 않을까? 
	if (AiEnableSpecialSize() > 0 && m_GameMapObj->GetTenreokuCheckPlayer2() == 0)
	{

	}
	// 공격카드를 사용할수 있다면 사용
	
	if (AiEnableAttackSize() > 0)
	{
		UseAttackCard();
	}
	else if (AiEnableSpellSize() > 0)
	{
		UseSpellCard();
	}
	else if (m_GameMapObj->GetPlayer2focus() >= 2 && m_GameMapObj->Player2FocusCheck() == true)
	{
		AiFocuseUse();
	}
	else if (((m_LikeRange - m_GameMapObj->GetRange()) == 1) &&( (m_LikeRange - m_GameMapObj->GetRange()) == -1) && m_GameMapObj->Player2FocusCheck() == true)
	{
		AiFocuseUse();
	}
	else if (AiEnableBuildingSize() > 0)
	{
		UseBuildingCard();
	}
	// 공격카드를 거리조절이 필요
	else if(m_GameMapObj->GetPlayer2VecHand().size() > 2 && m_GameMapObj->Player2FocusCheck() == true)
	{
		AiHandtoBack();
	}
	else if (AiEnableSize() == 0 && m_GameMapObj->GetPlayer2VecHand().size() <= 2 && m_GameMapObj->GetPlayer2VecHand().size() > 0 && m_GameMapObj->GetPlayer2focus() == 1 && m_GameMapObj->Player2FocusCheck() == true)
	{
		int S1 = rand() % 5;
		if (S1 == 0 )
		{
			AiFocuseUse();
		}
		else if (S1 == 1)
		{
			AiHandtoBack();
		}
		else if (S1 == 2)
		{
			m_GameMapObj->TurnEndSound();
			m_GameMapObj->SetPlayer2MainEnd(true);
		}
		else if (S1 == 3)
		{
			m_GameMapObj->TurnEndSound();
			m_GameMapObj->SetPlayer2MainEnd(true);
		}
		else if (S1 == 4)
		{
			m_GameMapObj->TurnEndSound();
			m_GameMapObj->SetPlayer2MainEnd(true);
		}
	}
	else 
	{
		m_GameMapObj->TurnEndSound();
		m_GameMapObj->SetPlayer2MainEnd(true);
	}

	m_GameMapObj->Player1BuildingSetPos();
}
void CPlayer2Ai::Gaesi()
{
	m_GameMapObj->buffreset();
	m_GameMapObj->AddPlayer2focus(1);
	/// <summary>
	/// 원래는 선택해서 부여패를 떄게 해야함 나중에 추가예정
	/// </summary>
	m_GameMapObj->Player1GaesiBuilding();
	m_GameMapObj->Player2GaesiBuilding();

	m_GameMapObj->SetTenreokuCheckPlayer2(0);
	//m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Gaeshi, nullptr, 0, 0);
	// 드로우 할까 리프레쉬할까 판단하는곳
	srand(GetTickCount());
	int S1 = rand() % 100;

	if (m_GameMapObj->GetPlayer2VecDeck().size() <= 1 )
	{
		m_GameMapObj->RefreshDeck2();
		m_GameMapObj->DrawACard2(2);
		m_GameMapObj->LogCreate(nullptr, nullptr, 0, 6);
	}
	else
	{
		int dmg= m_GameMapObj->DrawACard2(2);
		m_GameMapObj->LogCreate(nullptr, nullptr, 0, 5);
		for (int i = 0; i < dmg; ++i)
		{
			if (m_GameMapObj->GetPlayer2Shiled() > 0)
				m_GameMapObj->AddPlayer2Shiled(-1);
			else
			{
				m_GameMapObj->AddPlayer2Life(-1);
				m_GameMapObj->AddPlayer2Mana(1);
			}
		}
	}
	
}
void CPlayer2Ai::End()
{
	m_GameMapObj->Player2End();
}
/// <summary>
/// 
/// 
/// 
/// 
//
/// </summary>
void CPlayer2Ai::AiHandEnable()
{
	AiEnableClear();
	int result = 0;
	m_LikeRange = -1;
	m_LikeMana = -1;

	std::vector<CSharedPtr<CCard>> vecPlayer2Hero = m_GameMapObj->GetPlayer2VecHero();
	for (int i = 0; i < vecPlayer2Hero.size(); ++i)
	{
		
		if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Attack)
		{
			CCard* pTempCard = vecPlayer2Hero[i];
			if (Player2UseAttackCard((CAttackCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					if (m_GameMapObj->GetTenreokuCheckPlayer2() == 0)
					{
						m_queEnableAttackCard.push(pTempCard);
					}

				}
				
			}
			
		}
		else if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Spell)
		{
			CCard* pTempCard = vecPlayer2Hero[i];
			if (Player2UseSpellCard((CSpellCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{

					if (m_GameMapObj->GetTenreokuCheckPlayer2() == 0)
					{
						m_queEnableSpellCard.push(pTempCard);
					}
				}
				
			}
		}
	

	}

	std::vector<CSharedPtr<CCard>> vecPlayer2Hand = m_GameMapObj->GetPlayer2VecHand();
	for (int i = 0; i < vecPlayer2Hand.size(); ++i)
	{
		if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Attack)
		{
			CCard* pTempCard = vecPlayer2Hand[i];
			if (Player2UseAttackCard((CAttackCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					if (m_GameMapObj->GetTenreokuCheckPlayer2() == 0)
					{
						m_queEnableAttackCard.push(pTempCard);
					}
				}
				

			}
			
		}
		else if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Spell)
		{
			CCard* pTempCard = vecPlayer2Hand[i];
			if (Player2UseSpellCard((CSpellCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					if (m_GameMapObj->GetTenreokuCheckPlayer2() == 0)
					{
						m_queEnableSpellCard.push(pTempCard);
					}

				}
				
			}
		}
		
	}





	/// <summary>
	/// //////////////////////
	/// </summary>
	vecPlayer2Hero = m_GameMapObj->GetPlayer2VecHero();
	for (int i = 0; i < vecPlayer2Hero.size(); ++i)
	{	
		if(m_LikeMana == -1)
			m_LikeMana = vecPlayer2Hero[i]->GetManaCosT();
		else
		{
			if(m_LikeMana < vecPlayer2Hero[i]->GetManaCosT())
				m_LikeMana = vecPlayer2Hero[i]->GetManaCosT();
		}
		if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Attack)
		{
			CCard* pTempCard = vecPlayer2Hero[i];
			if (Player2UseAttackCard((CAttackCard*)pTempCard))
			{	
				if (pTempCard->GetTenreok() > 0 )
				{	
					
					
				}
				else
				{
					m_queEnableAttackCard.push(pTempCard);
				}
			}
			if (((CAttackCard*)pTempCard)->GetMax() < m_GameMapObj->GetRange() && ((CAttackCard*)pTempCard)->GetMax() != 10)
			{
				if (m_LikeRange == -1)
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMax();
				else if (m_LikeRange < ((CAttackCard*)pTempCard)->GetMax())
				{
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMax();
				}
			}
			else if (((CAttackCard*)pTempCard)->GetMin() > m_GameMapObj->GetRange()&& ((CAttackCard*)pTempCard)->GetMin() != 0)
			{
				if (m_LikeRange == -1)
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMin();
				else if (m_LikeRange > ((CAttackCard*)pTempCard)->GetMin())
				{
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMin();
				}
			}
		}
		else if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Spell)
		{
			CCard* pTempCard = vecPlayer2Hero[i];
			if (Player2UseSpellCard((CSpellCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					
					
				}
				else
				{
					m_queEnableSpellCard.push(pTempCard);
				}
			}
		}
		else if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Building)
		{
			CCard* pTempCard = vecPlayer2Hero[i];
			if (Player2UseBuildingCard((CBuildingCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					
					
				}
				else
				{
					m_queEnableBuildingCard.push(pTempCard);
				}
			}
		}

	}

	 vecPlayer2Hand = m_GameMapObj->GetPlayer2VecHand();
	for (int i = 0; i < vecPlayer2Hand.size(); ++i)
	{
		if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Attack)
		{	
			CCard* pTempCard = vecPlayer2Hand[i];
			if (Player2UseAttackCard((CAttackCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					
				}
				else
				{
					m_queEnableAttackCard.push(pTempCard);
				}
				
			}
			if (((CAttackCard*)pTempCard)->GetMax() < m_GameMapObj->GetRange() && ((CAttackCard*)pTempCard)->GetMax() != 10)
			{
				if (m_LikeRange == -1)
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMax();
				else if (m_LikeRange < ((CAttackCard*)pTempCard)->GetMax())
				{
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMax();
				}
			}
			else if (((CAttackCard*)pTempCard)->GetMin() > m_GameMapObj->GetRange() && ((CAttackCard*)pTempCard)->GetMin() != 0)
			{
				if (m_LikeRange == -1)
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMin();
				else if (m_LikeRange > ((CAttackCard*)pTempCard)->GetMin())
				{
					m_LikeRange = ((CAttackCard*)pTempCard)->GetMin();
				}
			}
		}
		else if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Spell)
		{
			CCard* pTempCard = vecPlayer2Hand[i];
			if (Player2UseSpellCard((CSpellCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0)
				{
					
					
				}
				else
				{
					m_queEnableSpellCard.push(pTempCard);
				}
			}
		}
		else if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Building)
		{
			CCard* pTempCard = vecPlayer2Hand[i];
			if (Player2UseBuildingCard((CBuildingCard*)pTempCard))
			{
				if (pTempCard->GetTenreok() > 0 )
				{
					
					
				}
				else
				{
					m_queEnableBuildingCard.push(pTempCard);
				}
			}
		}
	}


}

int CPlayer2Ai::AiEnableAttackSize()
{

	return m_queEnableAttackCard.size();
}

int CPlayer2Ai::AiEnableSpellSize()
{
	return  m_queEnableSpellCard.size();
}

int CPlayer2Ai::AiEnableBuildingSize()
{
	return  m_queEnableBuildingCard.size();
}

int CPlayer2Ai::AiEnableSpecialSize()
{
	/*if (m_EnableSpecialCard)
		return 1;
	else*/
		return 0;

}

int CPlayer2Ai::AiEnableSize()
{
	return AiEnableSpecialSize()+ AiEnableBuildingSize()+ AiEnableSpellSize()+ AiEnableAttackSize();
}

void CPlayer2Ai::AiEnableClear()
{
	while (!m_queEnableAttackCard.empty())
	{
		m_queEnableAttackCard.pop();
	}
	while (!m_queEnableSpellCard.empty())
	{
		m_queEnableSpellCard.pop();
	}
	while (!m_queEnableBuildingCard.empty())
	{
		m_queEnableBuildingCard.pop();
	}
	while (!m_queEnableDaeungCard.empty())
	{
		m_queEnableDaeungCard.pop();
	}
	m_EnableSpecialCard = nullptr;
}

int CPlayer2Ai::AiFocuseUse()
{
	m_HandBack = false;
	m_GameMapObj->AddPlayer2focus(-1);
	UseFocus();
	return 0;
}

bool CPlayer2Ai::AiHandtoBack()
{	
	m_HandBack = true;
	std::vector<CSharedPtr<CCard>> vecPlayer2Hand = m_GameMapObj->GetPlayer2VecHand();
	std::vector<CSharedPtr<CCard>> vecPlayer2Back = m_GameMapObj->GetPlayer2VecBack();
	if (vecPlayer2Hand.size() == 0)
		return false;
	size_t Handvecsize = vecPlayer2Hand.size();
	vecPlayer2Back.push_back(vecPlayer2Hand[0]);
	vecPlayer2Hand[0]->SettingGone();
	vecPlayer2Hand.erase(vecPlayer2Hand.begin());
	m_GameMapObj->SetPlayer2VecBack(vecPlayer2Back);
	m_GameMapObj->SetPlayer2VecHand(vecPlayer2Hand);
	m_GameMapObj->HandSortSetting();


	UseFocus();



	m_GameMapObj->SetPlayer2MainEnd(true);
	return true;
}

bool CPlayer2Ai::AiDauengCheck(CAttackCard* card)
{
	Player1AttackCardSetting(card);

	m_DauegTime = true;
	if (m_GameMapObj->GetPlayer2MainEnd() == true)
	{
		m_DauegTime = false;
		return false;
	}
		

	AiEnableClear();
	int result = 0;
	

	std::vector<CSharedPtr<CCard>> vecPlayer2Hand = m_GameMapObj->GetPlayer2VecHand();
	for (int i = 0; i < vecPlayer2Hand.size(); ++i)
	{

		// 사이네 간파 
		// 팔상일때 대응처럼 사용가능
		if (vecPlayer2Hand[i]->GetCardIndex() == 3 && vecPlayer2Hand[i]->GetHeroIndex() == 3)
		{
			if (m_GameMapObj->GetPlayer2Shiled() <= 1)
			{
				m_queEnableDaeungCard.push(vecPlayer2Hand[i]);
				
				continue;
			}
		}




		if (vecPlayer2Hand[i]->GetDaeung() > 0)
		{
			if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Attack)
			{
				CCard* pTempCard = vecPlayer2Hand[i];
				if (Player2UseAttackCard((CAttackCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);

				}

			}
			else if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Spell)
			{
				CCard* pTempCard = vecPlayer2Hand[i];
				if (Player2UseSpellCard((CSpellCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);
				}
			}
			else if (vecPlayer2Hand[i]->GetCardType() == Card_Type::Building)
			{
				CCard* pTempCard = vecPlayer2Hand[i];
				if (Player2UseBuildingCard((CBuildingCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);
				}
			}
		}
		
	}


	std::vector<CSharedPtr<CCard>> vecPlayer2Hero = m_GameMapObj->GetPlayer2VecHero();
	for (int i = 0; i < vecPlayer2Hero.size(); ++i)
	{	if(vecPlayer2Hero[i]->GetDaeung() > 0)
		{









			if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Attack)
			{
				CCard* pTempCard = vecPlayer2Hero[i];
				if (Player2UseAttackCard((CAttackCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);
				}

			}
			else if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Spell)
			{
				CCard* pTempCard = vecPlayer2Hero[i];
				if (Player2UseSpellCard((CSpellCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);
				}
			}
			else if (vecPlayer2Hero[i]->GetCardType() == Card_Type::Building)
			{
				CCard* pTempCard = vecPlayer2Hero[i];
				if (Player2UseBuildingCard((CBuildingCard*)pTempCard))
				{
					m_queEnableDaeungCard.push(pTempCard);
				}
			}
		}
		
	}

	m_DauegTime = false;
	return m_queEnableDaeungCard.size() > 0;
}

CCard* CPlayer2Ai::AiUseDaueng()
{
	// Ai대응설계할예정
	CCard* tempcard = m_queEnableDaeungCard.front();
	while (m_queEnableDaeungCard.size() > 0)
	{
	
		if (m_PlayerAttackLife >= 3)
		{
			if(tempcard->GetManaCosT() <= m_queEnableDaeungCard.front()->GetManaCosT())
				tempcard = m_queEnableDaeungCard.front();
		}
		else
		{
			break;
		}
		m_queEnableDaeungCard.pop();
	}


	
	int tempmana = tempcard->GetManaCosT();

	if (CheckCard(3, 1, Card_Class::Hero, tempcard))
	{
		tempmana -= m_GameMapObj->GetPlayer1Shiled();
	}
	m_GameMapObj->AddPlayer2Mana(-tempmana);
	m_GameMapObj->AddDust(tempmana);
	m_GameMapObj->UseCard(tempcard);
	m_GameMapObj->PushAnimationCard(tempcard,0);
	tempcard->SetDaeungTriger(true);
	std::vector<CSharedPtr<CCard>> vecHand = m_GameMapObj->GetPlayer2VecHand();
	std::vector<CSharedPtr<CCard>> vecUse = m_GameMapObj->GetPlayer2VecUse();
	std::vector<CSharedPtr<CCard>> vecBuilding = m_GameMapObj->GetPlayer2VecBuilding();

	for (int i = 0; i < vecHand.size(); ++i)
	{
		if (vecHand[i] == tempcard)
		{	
			if (vecHand[i]->GetCardType() == Card_Type::Building)
				vecBuilding.push_back(tempcard);
			else
				vecUse.push_back(tempcard);



			tempcard->SettingGone();
			vecHand.erase(vecHand.begin() + i);
			break;
		}
	}
	std::vector<CSharedPtr<CCard>> vecHero = m_GameMapObj->GetPlayer2VecHero();
	std::vector<CSharedPtr<CCard>> vecHeroUse = m_GameMapObj->GetPlayer2VecHeorUse();
	for (int i = 0; i < vecHero.size(); ++i)
	{
		if (vecHero[i] == tempcard)
		{

			if (vecHero[i]->GetCardType() == Card_Type::Building)
				vecBuilding.push_back(tempcard);
			else
				vecHeroUse.push_back(tempcard);
			
			tempcard->SettingGone();
			vecHero.erase(vecHero.begin() + i);
			break;
		}
	}

	m_GameMapObj->SetPlayer2VecBuilding(vecBuilding);
	m_GameMapObj->SetPlayer2VecHero(vecHero);
	m_GameMapObj->SetPlayer2VecHeroUse(vecHeroUse);
	m_GameMapObj->SetPlayer2VecHand(vecHand);
	m_GameMapObj->SetPlayer2VecUse(vecUse);
	m_GameMapObj->HandSortSetting();
	return tempcard;

}

bool CPlayer2Ai::Player2UseAttackCard(CAttackCard* card)
{
	int cardindex = card->GetCardIndex();
	int heroindex = card->GetHeroIndex();
	int RangeMin = card->GetMin()-m_GameMapObj->GetBuffRangeMin();
	int RangeMax = card->GetMax();
	//int ShieldDamage;
	//int LifeDamage;
	int ManaCost = card->GetManaCosT();
	Card_Class CardClass = card->GetCardClass();

	if (cardindex == 3 && heroindex == 1 && CardClass == Card_Class::Hero)
	{
		if (m_GameMapObj->GetPlayer1Life()> 3)
		{
			
			return false;
		}
	}

	if (m_GameMapObj->GetTenreokuCheckPlayer2() > 0 && card->GetTenreok() == 1)
	{
		
		return false;
	}



	if (!m_GameMapObj->Player1UseAttackCard(card))
	{
		return false;
	}

	//if (RangeMin <= m_GameMapObj->GetRange() && m_GameMapObj->GetRange() <= RangeMax)
	//{
	//	if (CardClass == Card_Class::Hero)
	//	{
	//		if (ManaCost <= m_GameMapObj->GetPlayer2Mana())
	//		{

	//		}
	//		else
	//		{
	//			
	//			return false;
	//		}
	//	}
	//}
	//else
	//{

	//	return false;
	//	// 공격거리안됨
	//}

	if (CheckCard(1, 1, (Card_Class)1, card))
	{
		if (!m_DauegTime)
		{
		

			return false;
		}
		else
		{
			if (m_PlayerAttackShiled == -1)
				return false;

			if (m_PlayerAttackShiled - m_GameMapObj->GetPlayer2Shiled() > 2)
				return false;

			if (m_PlayerAttackShiled == 1)
				return false;

			if (m_PlayerAttackLife == 1)
				return false;
		}
		
	}
	if (CheckCard(1, 3, (Card_Class)1, card))
	{
		if (m_GameMapObj->GetPlayer2Life() > 3)
		{
			return false;
		}

	}
	if (CheckCard(3, 2, (Card_Class)1, card))
	{
		if (!m_DauegTime)
		{
			
			return false;
		}
		else
		{
			if (m_GameMapObj->GetPlayer2HeroCardSize() == 1)
			{
				return true;
			}
			if (m_GameMapObj->GetPlayer2HeroCardSize() > 1 && m_GameMapObj->GetPlayer2Mana() >= (m_LikeMana - 1))
			{
				return true;
			}
		}
		
	}
	if (CheckCard(3, 3, (Card_Class)1, card))
	{
		if (!m_DauegTime)
		{
			return false;
		}
		else
		{
			if (m_PlayerAttackClass == 0)
				return false;
		}
	}
	if (CheckCard(8, 1, (Card_Class)0, card))
	{
		if (!m_DauegTime)
			return false;
	}
	if (CheckCard(8, 0, (Card_Class)1, card))
	{
		if (!m_DauegTime)
			return false;
		else
		{
			if (m_GameMapObj->GetPlayer2Life() - m_PlayerAttackLife < 3)
				return true;
		
			if (m_PlayerAttackLife >= 3)
				return true;
			return false;
		}
	}
	if (CheckCard(8, 1, (Card_Class)1, card))
	{
		if (m_GameMapObj->GetPlayer2VecUse().size() + m_GameMapObj->GetPlayer2VecBack().size() < 4)
			return false;
	}
	if (CheckCard(8, 2, (Card_Class)1, card))
	{
		if (m_GameMapObj->Player1HandNotAttack() == 0)
			return false;
	}
	return true;
}

bool CPlayer2Ai::Player2UseSpellCard(CSpellCard* card)
{
	if (m_GameMapObj->GetTenreokuCheckPlayer2() > 0 && card->GetTenreok() == 1)
	{
		
		return false;
	}

	if (!m_GameMapObj->Player1UseSpellCard(card))
		return false;

	if (CheckCard(1, 4, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > m_LikeRange && m_GameMapObj->GetPlayer2focus() < 2)
		{
			return true;
		}
		else
			return false;
	}

	if (CheckCard(1, 2, (Card_Class)1, card))
	{
		if (m_GameMapObj->GetPlayer2Shiled() <= 1)
		{
			return true;
		}
		else
			return false;
	}

	if (CheckCard(3, 3, (Card_Class)0, card))
	{
		
		return false;
	}
	if (CheckCard(3, 0, (Card_Class)1, card))
	{
		m_LikeRange = 4;

		if (m_GameMapObj->GetRange() < 3 || m_GameMapObj->GetRange() > 6)
			return false;
	
	}
	if (CheckCard(3, 1, (Card_Class)1, card))
	{
		if (m_GameMapObj->GetRange() > 3 && m_GameMapObj->GetPlayer1Shiled() < 3 )
			return false;

	}
	//  토코요 스펠
	if (CheckCard(8, 2, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > 3)
			return false;

	}
	if (CheckCard(8, 3, (Card_Class)0, card))
	{
		if (!m_DauegTime)
		{
			if (m_LikeRange + 1 == m_GameMapObj->GetRange() && m_GameMapObj->GetPlayer2focus() <= 1)
			{
				return true;
			}
			return false;
		}
	}

	if (CheckCard(8, 4, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetPlayer2Shiled() >= 4)
		{
			return false;
		}
		if ((m_GameMapObj->GetPlayer2VecBack().size() + m_GameMapObj->GetPlayer2VecUse().size()) <= 3)
		{
			return false;
		}
	}

	if (CheckCard(8, 3, (Card_Class)1, card))
	{
		if (m_GameMapObj->GetPlayer1focus() < 1)
		{
			return false;
		}
	
	}
	return true;
}

bool CPlayer2Ai::Player2UseBuildingCard(CBuildingCard* card)
{
	if (m_GameMapObj->GetTenreokuCheckPlayer2() > 0 && card->GetTenreok() == 1)
	{

		return false;
	}


	if (!m_GameMapObj->Player1UseBuildingCard(card))
	{
		return false;
	}



	if (CheckCard(1, 5, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > 5 || m_GameMapObj->GetPlayer1Shiled() <= 1)
		{
			return false;
		}
	}
	
	if (CheckCard(1, 6, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetPlayer2Life() > 4)
		{
			return false;
		}
	}
	if (CheckCard(3, 4, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > 3)
		{
			return false;
		}
	
			
	}

	if (CheckCard(3, 5, (Card_Class)0, card))
	{
		if (!m_DauegTime)
			return false;
	}
	if (CheckCard(3, 6, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetDust() < 5 && m_GameMapObj->GetPlayer2Shiled() > 1)
		{
			return false;
		}
	}

	if (CheckCard(8, 5, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > 6 || m_GameMapObj->GetPlayer2Shiled() >= 4)
		{
			return false;
		}
	}
	if (CheckCard(8, 6, (Card_Class)0, card))
	{
		if (m_GameMapObj->GetRange() > 6)
		{
			return false;
		}
	}
	return true;
}

bool CPlayer2Ai::ForWard()
{
	if (m_GameMapObj->GetPlayer2Shiled() >= 5 || m_GameMapObj->GetRange() <= 2)
	{
		return false;
	}
	else
	{
		m_GameMapObj->ForwardSound();
		m_GameMapObj->AddRange(-1);
		m_GameMapObj->AddPlayer2Shiled(1);
		m_GameMapObj->PushAnimationCard2(0, 1, Card_Class::Normal);
		if(m_HandBack)
			m_GameMapObj->LogCreate(nullptr, nullptr, 7, 2);
		else
			m_GameMapObj->LogCreate(nullptr, nullptr, 1, 2);
	
		return true;
	}
}

bool CPlayer2Ai::BackWard()
{
	if (m_GameMapObj->GetPlayer2Shiled() <= 0 || m_GameMapObj->GetRange() == 10)
	{
		return false;
	}
	else
	{
		m_GameMapObj->BackWardSound();
		m_GameMapObj->AddRange(1);
		m_GameMapObj->AddPlayer2Shiled(-1);
		m_GameMapObj->PushAnimationCard2(0, 2, Card_Class::Normal);
		if (m_HandBack)
			m_GameMapObj->LogCreate(nullptr, nullptr, 8, 2);
		else
			m_GameMapObj->LogCreate(nullptr, nullptr,2, 2);
		return true;
	}
}

bool CPlayer2Ai::Ora()
{
	if (m_GameMapObj->GetDust() <= 0 || m_GameMapObj->GetPlayer2Shiled() >= 5)
	{
		return false;
	}
	else
	{
		m_GameMapObj->OraSound();
		m_GameMapObj->AddDust(-1);
		m_GameMapObj->AddPlayer2Shiled(1);
		m_GameMapObj->PushAnimationCard2(0, 3, Card_Class::Normal);
		if (m_HandBack)
			m_GameMapObj->LogCreate(nullptr, nullptr, 9, 2);
		else
			m_GameMapObj->LogCreate(nullptr, nullptr, 3, 2);
		return true;
	}
}

bool CPlayer2Ai::Mana()
{
	if (m_GameMapObj->GetPlayer2Shiled() <= 0 && m_GameMapObj->GetPlayer2HeroCardSize() == 0)
	{
		return false;
	}
	else if (m_GameMapObj->SumPlayer2HeroManaCost() > m_GameMapObj->GetPlayer2Mana())
	{
		return false;
	}
	else
	{
		m_GameMapObj->ManaSound();
		m_GameMapObj->AddPlayer2Shiled(-1);
		m_GameMapObj->AddPlayer2Mana(1);

		m_GameMapObj->PushAnimationCard2(0, 4, Card_Class::Normal);
		if (m_HandBack)
			m_GameMapObj->LogCreate(nullptr, nullptr, 10, 2);
		else
			m_GameMapObj->LogCreate(nullptr, nullptr, 4, 2);
		return true;
	}
}

bool CPlayer2Ai::Ital()
{	
	if (m_GameMapObj->GetDust() <= 0)
	{
		return false;
	}
	else
	{
		m_GameMapObj->ItalSound();
		m_GameMapObj->AddDust(-1);
		m_GameMapObj->AddRange(1);
		m_GameMapObj->PushAnimationCard2(0, 5, Card_Class::Normal);
		if (m_HandBack)
			m_GameMapObj->LogCreate(nullptr, nullptr,11, 2);
		else
			m_GameMapObj->LogCreate(nullptr, nullptr, 5, 2);
		return true;
	}
	
}

bool CPlayer2Ai::UseFocus()
{	
	if (m_LikeRange <= m_GameMapObj->GetRange() && m_GameMapObj->GetPlayer2Shiled() == 5)
	{
		Mana();
		return true;
	}

	if ((m_LikeMana - m_GameMapObj->GetPlayer2Mana()) == 1 && m_GameMapObj->GetPlayer2Shiled() >= 1)
	{
		if (!Mana())
		{
			if (!Ora())
			{
				if (m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
				{
					if (!ForWard())
					{
						BackWard();
					}
				}
				else
				{
					if (!Ital())
					{
						BackWard();
					}
				}
			}
		}
	}
	else if (m_GameMapObj->GetRange() > m_LikeRange && m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
	{
		if (!ForWard())
		{
			if (!Mana())
			{
				if (!Ora())
				{
					if (m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
					{
						if (!ForWard())
						{
							BackWard();
						}
					}
					else
					{
						if (!Ital())
						{
							BackWard();
						}
					}
				}
			}
		}
	}
	else if (m_GameMapObj->GetRange() < m_LikeRange && m_GameMapObj->GetRange() <= m_GameMapObj->GetDALINRange())
	{
		if (!Ital())
		{
			BackWard();
		}
	}
	else if (m_GameMapObj->GetRange() < m_LikeRange)
	{
		if (!BackWard())
		{
			if (!Ora())
			{
				if (m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
				{
					if (!ForWard())
					{
						BackWard();
					}
				}
				else
				{
					if (!Ital())
					{
						BackWard();
					}
				}
			}
		}
	}
	else if (m_GameMapObj->GetPlayer2Shiled() < 5)
	{
		if (!Ora())
		{
			if (!ForWard())
			{	
				if (!Mana())
				{
					if (!Ora())
					{
						if (m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
						{
							if (!ForWard())
							{
								BackWard();
							}
						}
						else
						{
							if (!Ital())
							{
								BackWard();
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (!Mana())
		{
			if (!Ora())
			{
				if (m_GameMapObj->GetRange() > m_GameMapObj->GetDALINRange())
				{
					if (!ForWard())
					{
						BackWard();
					}
				}
				else
				{
					if (!Ital())
					{
						BackWard();
					}
				}
			}
		}
	}
		

	return true;
}

bool CPlayer2Ai::UseAttackCard()
{	
	CCard* tempcard = m_queEnableAttackCard.front();
	
	int tempmana = tempcard->GetManaCosT();
	m_GameMapObj->AddPlayer2Mana(-tempmana);
	m_GameMapObj->AddDust(tempmana);

	if (CheckCard(3,0,(Card_Class)0,tempcard))
	{
		if (m_GameMapObj->GetPlayer2Shiled() == 2 && m_GameMapObj->GetPlayer2focus() == 1)
		{
		
			if (m_GameMapObj->Player2FocusCheck() == true)
			{
				m_GameMapObj->AddPlayer2focus(-1);
				Mana();
				return true;
			}
			
		}
	}


	if (m_GameMapObj->Player1Daueg(tempcard) && ((CAttackCard*)tempcard)->GetDaeugbool() == false)
	{
		m_GameMapObj->PushAnimationCard(tempcard, 0);
		m_GameMapObj->Player1OpenDauegButton((CAttackCard*)tempcard);
		
	}
	else
	{
		m_GameMapObj->AttackonTheStack((CAttackCard*)tempcard);
		m_GameMapObj->PushAnimationCard(tempcard, 0);
		m_GameMapObj->LogCreate(tempcard,nullptr,0,2);
	}
		
	m_queEnableAttackCard.pop();
	m_GameMapObj->AddTenreokuCheckPlayer2(1);
	std::vector<CSharedPtr<CCard>> vecHand = m_GameMapObj->GetPlayer2VecHand();
	std::vector<CSharedPtr<CCard>> vecUse = m_GameMapObj->GetPlayer2VecUse();
	
	for (int i = 0; i < vecHand.size(); ++i)
	{
		if (vecHand[i] == tempcard)
		{	
			vecUse.push_back(tempcard);
			tempcard->SettingGone();
			vecHand.erase(vecHand.begin() + i);
			break;
		}
	}
	std::vector<CSharedPtr<CCard>> vecHero = m_GameMapObj->GetPlayer2VecHero();
	std::vector<CSharedPtr<CCard>> vecHeroUse = m_GameMapObj->GetPlayer2VecHeorUse();
	for (int i = 0; i < vecHero.size(); ++i)
	{
		if (vecHero[i] == tempcard)
		{
			vecHeroUse.push_back(tempcard);
			tempcard->SettingGone();
			vecHero.erase(vecHero.begin() + i);
			break;
		}
	}

	m_GameMapObj->SetPlayer2VecHero(vecHero);
	m_GameMapObj->SetPlayer2VecHeroUse(vecHeroUse);
	m_GameMapObj->SetPlayer2VecHand(vecHand);
	m_GameMapObj->SetPlayer2VecUse(vecUse);

	m_GameMapObj->HandSortSetting2();

	return true;
}

bool CPlayer2Ai::UseSpellCard()
{
	CCard* tempcard = m_queEnableSpellCard.front();

	// 맑음의 무대 쓰기전에 집중력 다 쓰기 콤보
	if (CheckCard(8, 3, (Card_Class)1, tempcard))
	{
		while (m_GameMapObj->GetPlayer2focus() > 0)
		{
			if (m_GameMapObj->Player2FocusCheck() == true)
			{
				m_GameMapObj->AddPlayer2focus(-1);
				UseFocus();
				return true;
			}
			
		}
	}


	int tempmana = tempcard->GetManaCosT();
	m_GameMapObj->LogCreate(tempcard, nullptr, 0, 2);
	if (CheckCard(3, 1, Card_Class::Hero, tempcard))
	{
		tempmana -= m_GameMapObj->GetPlayer1Shiled();
	}
	m_GameMapObj->AddPlayer2Mana(-tempmana);
	m_GameMapObj->AddDust(tempmana);

	m_GameMapObj->PushAnimationCard(tempcard,0);

	m_GameMapObj->UseCard(tempcard);
	m_queEnableSpellCard.pop();
	m_GameMapObj->AddTenreokuCheckPlayer2(1);
	std::vector<CSharedPtr<CCard>> vecHand = m_GameMapObj->GetPlayer2VecHand();
	std::vector<CSharedPtr<CCard>> vecUse = m_GameMapObj->GetPlayer2VecUse();
	for (int i = 0; i < vecHand.size(); ++i)
	{
		if (vecHand[i] == tempcard)
		{
			vecUse.push_back(tempcard);
			tempcard->SettingGone();
			vecHand.erase(vecHand.begin() + i);
			break;
		}
	}
	std::vector<CSharedPtr<CCard>> vecHero = m_GameMapObj->GetPlayer2VecHero();
	std::vector<CSharedPtr<CCard>> vecHeroUse = m_GameMapObj->GetPlayer2VecHeorUse();
	for (int i = 0; i < vecHero.size(); ++i)
	{
		if (vecHero[i] == tempcard)
		{
			vecHeroUse.push_back(tempcard);
			tempcard->SettingGone();
			vecHero.erase(vecHero.begin() + i);
			break;
		}
	}


	m_GameMapObj->SetPlayer2VecHero(vecHero);
	m_GameMapObj->SetPlayer2VecHeroUse(vecHeroUse);
	m_GameMapObj->SetPlayer2VecHand(vecHand);
	m_GameMapObj->SetPlayer2VecUse(vecUse);
	m_GameMapObj->HandSortSetting2();
	return true;
}

bool CPlayer2Ai::UseBuildingCard()
{
	CCard* tempcard = m_queEnableBuildingCard.front();

	// 맑음의 무대 쓰기전에 집중력 다 쓰기 콤보
	if (CheckCard(8, 6, (Card_Class)0, tempcard))
	{
		while (m_GameMapObj->GetPlayer2focus() > 0)
		{
			m_GameMapObj->AddPlayer2focus(-1);
			UseFocus();
		}
	}


	int tempmana = tempcard->GetManaCosT();
	m_GameMapObj->AddPlayer2Mana(-tempmana);
	m_GameMapObj->AddDust(tempmana);
	m_GameMapObj->PushAnimationCard(tempcard,0);
	m_GameMapObj->LogCreate(tempcard, nullptr, 0, 2);
	((CBuildingCard*)tempcard)->SetNabPoint(0);
	((CBuildingCard*)tempcard)->SetUse(true);
	int tempNab = ((CBuildingCard*)tempcard)->GetNab();
	for (int i = 0 ;i < tempNab; ++i)
	{
		if (m_GameMapObj->GetDust() > 0)
		{
			((CBuildingCard*)tempcard)->AddNabPoint(1);
			m_GameMapObj->AddDust(-1);
		}
		else
		{
			if (m_GameMapObj->GetPlayer2Shiled() > 0)
			{
				((CBuildingCard*)tempcard)->AddNabPoint(1);
				m_GameMapObj->AddPlayer2Shiled(-100);
			}
			else
			{
				break;
			}
		}
	}


	m_GameMapObj->UseCard(tempcard);
	m_queEnableBuildingCard.pop();
	m_GameMapObj->AddTenreokuCheckPlayer2(1);
	std::vector<CSharedPtr<CCard>> vecHand = m_GameMapObj->GetPlayer2VecHand();
	std::vector<CSharedPtr<CCard>> vecBuilding = m_GameMapObj->GetPlayer2VecBuilding();
	for (int i = 0; i < vecHand.size(); ++i)
	{
		if (vecHand[i] == tempcard)
		{
			vecBuilding.push_back(tempcard);
			tempcard->SettingGone();
			vecHand.erase(vecHand.begin() + i);
			break;
		}
	}


	std::vector<CSharedPtr<CCard>> vecHero = m_GameMapObj->GetPlayer2VecHero();
	std::vector<CSharedPtr<CCard>> vecHeroUse = m_GameMapObj->GetPlayer2VecHeorUse();
	for (int i = 0; i < vecHero.size(); ++i)
	{
		if (vecHero[i] == tempcard)
		{
			vecBuilding.push_back(tempcard);
			tempcard->SettingGone();
			vecHero.erase(vecHero.begin() + i);
			break;
		}
	}


	m_GameMapObj->SetPlayer2VecHero(vecHero);
	m_GameMapObj->SetPlayer2VecHeroUse(vecHeroUse);
	m_GameMapObj->SetPlayer2VecHand(vecHand);
	m_GameMapObj->SetPlayer2VecBuilding(vecBuilding);
	m_GameMapObj->HandSortSetting2();
	return true;
}

bool CPlayer2Ai::CheckCard(int Hero, int CardIndex, Card_Class cardclass,CCard* card)
{	
	if (card->GetHeroIndex() == Hero && card->GetCardIndex() == CardIndex && card->GetCardClass() == cardclass)
		return true;
	else
		return false;
	
}

// 선호하는거리가 멀리있으면 false
bool CPlayer2Ai::LikeRangeCheck()
{
	if (m_GameMapObj->GetRange() == m_PlayerAttackMax)
		return false;
	else if (m_GameMapObj->GetRange() == m_PlayerAttackMin)
		return true;
	else
	{
		return false;
	}
}

void CPlayer2Ai::Player1AttackCardSetting(CAttackCard* card)
{
	m_PlayerAttackMin = card->GetMin();
	m_PlayerAttackMax = card->GetMax();
	m_PlayerAttackShiled = card->GetDSh();
	m_PlayerAttackLife = card->GetDLi();
	m_PlayerAttackClass = (int)card->GetCardClass();
}
