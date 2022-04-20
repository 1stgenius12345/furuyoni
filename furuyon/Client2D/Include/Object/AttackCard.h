#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "Card.h"

class CAttackCard :
	public CCard
{
	friend class CScene;
public:
	CAttackCard();
	CAttackCard(const CAttackCard& obj);
	virtual ~CAttackCard();

protected:
	int m_AttackRangeMin;
	int m_AttackRangeMax;
	int m_AttackDamageSh;
	int m_AttackDamageLi;
	bool m_Daeugboolga;
public:
	bool GetDaeugbool() const
	{
		return m_Daeugboolga;
	}
	void AddMin(int i)
	{
		m_AttackRangeMin += i;
	}
	int GetMin() const
	{
		return m_AttackRangeMin;
	}
	void SetMin(int i)
	{
		m_AttackRangeMin = i;
	}
	void AddMax(int i)
	{
		m_AttackRangeMax += i;
	}
	int GetMax() const
	{
		return m_AttackRangeMax;
	}
	void SetMax(int i)
	{
		m_AttackRangeMax = i;
	}

	void AddDSh(int i)
	{
		m_AttackDamageSh += i;
	}
	int GetDSh() const
	{
		return m_AttackDamageSh;
	}
	void SetDSh(int i)
	{
		m_AttackDamageSh = i;
	}


	void AddDLi(int i)
	{
		m_AttackDamageLi += i;
	}
	int GetDLi() const
	{
		return m_AttackDamageLi;
	}
	void SetDLi(int i)
	{
		m_AttackDamageLi = i;
	}


public:

	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CAttackCard* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	virtual void CreateCardSetting();


public:
	void AttackCardSetting(int min, int max, int sh, int li,int dae, int jeo);
	
	void AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo,int mana);
	void AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo, int mana,bool daeungbool);
	void AttackCardSetting(int min, int max, int sh, int li, int dae, int jeo, bool daeungbool);
};

