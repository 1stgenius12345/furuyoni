#include "AttackCard.h"

CAttackCard::CAttackCard():
	m_AttackRangeMin(0),
	m_AttackRangeMax(10),
	m_AttackDamageSh(3),
	m_AttackDamageLi(3),
	m_Daeugboolga(false)
{
	m_CardType = Card_Type::Attack;
}

CAttackCard::CAttackCard(const CAttackCard& obj) :
	CCard(obj)
{
	m_AttackRangeMin   = obj.m_AttackRangeMin;
	m_AttackRangeMax = obj.m_AttackRangeMax	 ;
	m_AttackDamageSh = obj.m_AttackDamageSh	 ;
	m_AttackDamageLi = obj.m_AttackDamageLi	 ;
	m_Daeugboolga = obj.m_Daeugboolga		 ;
}

CAttackCard::~CAttackCard()
{
}

void CAttackCard::Start()
{
	CCard::Start();


}

bool CAttackCard::Init()
{
	CCard::Init();

	return true;
}

void CAttackCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);
}

void CAttackCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CAttackCard::Collision(float DeltaTime)
{
	CCard::Collision(DeltaTime);
}

void CAttackCard::Render(float DeltaTime)
{
	CCard::Render(DeltaTime);
}

CAttackCard* CAttackCard::Clone()
{
	return new CAttackCard(*this);
}

void CAttackCard::Animation2DNotify(const std::string& Name)
{
}

void CAttackCard::CreateCardSetting()
{	// 통상패 세팅
	if (Card_Class::Normal == m_CardClass)
	{
		switch (m_HeroIndex)
		{
		// 유리나
		case 1:
			switch (m_CardIndex)
			{
			// 1번 참
			case 0:
				AttackCardSetting(3, 4, 3, 1, 0, 0);
				break;
			// 2번 일섬
			case 1:
				AttackCardSetting(3, 3, 2, 2, 0, 0);
				break;
			case 2:
				AttackCardSetting(1, 2, 2, 1, 0, 0);
				break;
			case 3:
				AttackCardSetting(2, 4, 4, 3, 0, 1);
				break;
			default:
				break;
			}
			break;
		//  사이네
		case 3:
			switch (m_CardIndex)
			{
				// 팔방 휘두르기
			case 0:
				AttackCardSetting(4, 5, 2, 1, 0, 0);
				break;
				// 낫 베기
			case 1:
				AttackCardSetting(4, 5, 3, 1, 1, 0);
				break;
				// 무게추
			case 2:
				AttackCardSetting(2, 3, 2, 1, 1, 0);
				break;
		
			default:
				break;
			}
			break;
			// 토코요 공격 통상패
		case 8:
			switch (m_CardIndex)
			{
				// 빗어내리기
			case 0:
				AttackCardSetting(4, 4, -1, 1, 0, 0);
				break;
				// 우아한 타격
			case 1:
				AttackCardSetting(2, 4, 2, 1, 1, 0);
				break;
		
			

			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	//  비장패 세팅
	else
	{
		switch (m_HeroIndex)
		{
		case 1:
			switch (m_CardIndex)
			{
			case 0:
				AttackCardSetting(3,4,4,4,0,0,7);
				break;
			case 1:
				AttackCardSetting(0, 10, 2, -1, 1, 0, 3);
				break;
			case 3:
				AttackCardSetting(1, 4, 5, 5, 0, 1,5);
				break;
			default:
				break;
			}
			break;
		// 사이네 공격 비장패
		case 3:
			switch (m_CardIndex)
			{
			// 무음쇄빙
			case 2:
				AttackCardSetting(0, 10, 1, 1, 1, 0, 2);
				break;
			//히사메 사이네의 최후의 종극
			case 3:
				AttackCardSetting(1, 5, 5, 5, 1, 0, 5);
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (m_CardIndex)
			{
				// 영원의 꽃
			case 0:
				AttackCardSetting(0, 10, -1, 1, 1, 0, 5);
				break;
				// 천년의 새
			case 1:
				AttackCardSetting(3, 4, 2, 2, 0, 0, 2);
				break;
				// 무궁의바람
			case 2:
				AttackCardSetting(3, 8, 1, 1, 0, 0, 1,true);
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

void CAttackCard::AttackCardSetting(int min, int max,int sh , int li,int dae,int jeo)
{
	m_AttackRangeMax = max;
	m_AttackRangeMin = min;
	m_AttackDamageSh = sh;
	m_AttackDamageLi = li;
	m_Daeung = dae;
	m_Tenreok = jeo;
	
}

void CAttackCard::AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo, int mana)
{
	m_AttackRangeMax = max;
	m_AttackRangeMin = min;
	m_AttackDamageSh = sh;
	m_AttackDamageLi = li;
	m_Daeung = dae;
	m_Tenreok = jeo;
	m_ManaCost = mana;
	
}

void CAttackCard::AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo, int mana, bool daeungbool)
{
	m_AttackRangeMax = max;
	m_AttackRangeMin = min;
	m_AttackDamageSh = sh;
	m_AttackDamageLi = li;
	m_Daeung = dae;
	m_Tenreok = jeo;
	m_ManaCost = mana;
	m_Daeugboolga = daeungbool;
}

void CAttackCard::AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo, bool daeungbool)
{
	m_AttackRangeMax = max;
	m_AttackRangeMin = min;
	m_AttackDamageSh = sh;
	m_AttackDamageLi = li;
	m_Daeung = dae;
	m_Tenreok = jeo;
	m_Daeugboolga = daeungbool;
}
