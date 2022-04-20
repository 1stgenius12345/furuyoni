
#pragma once

#include "GameObject.h"
#include "../ClientManager.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/SelectHUDWidget.h"
#include "Card.h"



class CDeck :
	public CGameObject
{
	friend class CScene;
	friend class CCard;

protected:
	CDeck();
	CDeck(const CDeck& obj);
	virtual ~CDeck();

protected:
	std::vector<CSharedPtr<CCard>> m_vecNormalCard;
	std::vector<CSharedPtr<CCard>> m_vecHeroCard;
	class CSelectHUDWidget* m_SelectWidget;

protected:
	bool m_bRendernormal;
	int m_HeroIndex;


public:
	CCard* GetHeroCardByindex(int index) const
	{
		return m_vecHeroCard[index];
	}
	CCard* GetNormalCardByindex(int index) const
	{
		
		return m_vecNormalCard[index];
	}
	void SetHeroIndex(int i)
	{
		m_HeroIndex = i;
	}
	int GetHeroIndex() const
	{
		return m_HeroIndex;
	}
	void BattleForReady();

	void ReadyForBattle1()
	{	
		CClientManager::GetInst()->Setfirst(m_HeroIndex);
		size_t sizevec = m_vecNormalCard.size();
		
		for (int i = 0; i < sizevec; ++i)
		{
			if (m_vecNormalCard[i]->GetSelect())
			{
				CClientManager::GetInst()->SetNormal1Card(i);
			}
		}

		size_t sizevec1 = m_vecHeroCard.size();

		for (int i = 0; i < sizevec1; ++i)
		{
			if (m_vecHeroCard[i]->GetSelect())
			{
				CClientManager::GetInst()->SetHero1Card(i);
			}
		}
		
	}
	void ReadyForBattle2()
	{
		CClientManager::GetInst()->Setsecond(m_HeroIndex);
		size_t sizevec = m_vecNormalCard.size();

		for (int i = 0; i < sizevec; ++i)
		{
			if (m_vecNormalCard[i]->GetSelect())
			{
				CClientManager::GetInst()->SetNormal2Card(i);
			}
		}

		size_t sizevec1 = m_vecHeroCard.size();

		for (int i = 0; i < sizevec1; ++i)
		{
			if (m_vecHeroCard[i]->GetSelect())
			{
				CClientManager::GetInst()->SetHero2Card(i);
			}
		}

	}
	class CSelectHUDWidget* GetSelectWidget() const
	{
		if (m_SelectWidget == nullptr)
			return nullptr;
		return m_SelectWidget;
	}
	void SetSelectWidget(class CSelectHUDWidget* widget)
	{
		m_SelectWidget = widget;
	}

	void SetRendernormal(bool normal)
	{
		m_bRendernormal = normal;
	}
	void SetRendernormal()
	{
		if (m_bRendernormal)
			m_bRendernormal = false;
		else
			m_bRendernormal = true;
	}
	bool GetRendernormal() const
	{
		return m_bRendernormal;
	}
	void SelectOtherSetting()
	{
		size_t vecsize = m_vecNormalCard.size();

		for (int i = 0; i < vecsize; ++i)
		{
			m_vecNormalCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecNormalCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecNormalCard[i]->GetRelativeScale().y * 1.3f), 0.f);

			m_vecNormalCard[i]->SetRelativePos(1800.f, 1800.f, 0.f);
			m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
			m_vecNormalCard[i]->SetMove(false);
		}

		size_t vecsize2 = m_vecHeroCard.size();

		for (int i = 0; i < vecsize2; ++i)
		{
			m_vecHeroCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecHeroCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecHeroCard[i]->GetRelativeScale().y * 1.3f), 0.f);

			//m_vecHeroCard[i]->SetRender(false);
			m_vecHeroCard[i]->SetMove(false);


			m_vecHeroCard[i]->SetRelativePos(1800.f, 1800.f, 0.f);
			m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
		}
		m_bRendernormal = false;
	}
	void SelectSetting()
	{
		
		if (m_bRendernormal)
		{
			size_t vecsize = m_vecNormalCard.size();

			for (int i = 0; i < vecsize; ++i)
			{
				m_vecNormalCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecNormalCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecNormalCard[i]->GetRelativeScale().y * 1.3f), 0.f);
				m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
				m_vecNormalCard[i]->SetMove(false);
			}

			size_t vecsize2 = m_vecHeroCard.size();

			for (int i = 0; i < vecsize2; ++i)
			{
				m_vecHeroCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecHeroCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecHeroCard[i]->GetRelativeScale().y * 1.3f), 0.f);

				//m_vecHeroCard[i]->SetRender(false);
				m_vecHeroCard[i]->SetMove(false);


				m_vecHeroCard[i]->SetRelativePos(1800.f, 1800.f,0.f);
				m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
			}
		
		}
		else
		{

			size_t vecsize = m_vecNormalCard.size();

			for (int i = 0; i < vecsize; ++i)
			{
				m_vecNormalCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecNormalCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecNormalCard[i]->GetRelativeScale().y * 1.3f), 0.f);

				m_vecNormalCard[i]->SetRelativePos(1800.f, 1800.f, 0.f);
				m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
				m_vecNormalCard[i]->SetMove(false);
			}

			size_t vecsize2 = m_vecHeroCard.size();

			for (int i = 0; i < vecsize2; ++i)
			{
				m_vecHeroCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecHeroCard[i]->GetRelativeScale().x * 1.3), 519.f - ((i / 4) * m_vecHeroCard[i]->GetRelativeScale().y * 1.3f), 0.f);

				//m_vecHeroCard[i]->SetRender(false);
				m_vecHeroCard[i]->SetMove(false);


				//m_vecHeroCard[i]->SetRelativePos(1800.f, 1800.f,0.f);
				m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
			}

	
		}
		
		SetRendernormal();
		
	}
	void SelectSelectSetting()
	{

		if (m_bRendernormal)
		{
			size_t vecsize = m_vecNormalCard.size();

			for (int i = 0; i < vecsize; ++i)
			{
				m_vecNormalCard[i]->SetRelativePos(420.f + ((i % 4) * m_vecNormalCard[i]->GetRelativeScale().x * 0.5f), 489.f - ((i / 4) * m_vecNormalCard[i]->GetRelativeScale().y * 1.f), 0.f);
				m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
				m_vecNormalCard[i]->SetMove(false);
			}

			size_t vecsize2 = m_vecHeroCard.size();

			for (int i = 0; i < vecsize2; ++i)
			{
				//m_vecHeroCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecHeroCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecHeroCard[i]->GetRelativeScale().y * 1.3f), 0.f);

				//m_vecHeroCard[i]->SetRender(false);
				m_vecHeroCard[i]->SetMove(false);


				m_vecHeroCard[i]->SetRelativePos(1800.f, 1800.f, 0.f);
				m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
			}

		}
		else
		{

			size_t vecsize = m_vecNormalCard.size();

			for (int i = 0; i < vecsize; ++i)
			{
				//m_vecNormalCard[i]->SetRelativePos(151.f + ((i % 4) * m_vecNormalCard[i]->GetRelativeScale().x * 1.3f), 519.f - ((i / 4) * m_vecNormalCard[i]->GetRelativeScale().y * 1.3f), 0.f);

				m_vecNormalCard[i]->SetRelativePos(1800.f, 1800.f, 0.f);
				m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
				m_vecNormalCard[i]->SetMove(false);
			}

			size_t vecsize2 = m_vecHeroCard.size();

			for (int i = 0; i < vecsize2; ++i)
			{
				m_vecHeroCard[i]->SetRelativePos(420.f + ((i % 4) * m_vecHeroCard[i]->GetRelativeScale().x * 0.5f), 489.f - ((i / 4) * m_vecHeroCard[i]->GetRelativeScale().y * 1.f), 0.f);

				//m_vecHeroCard[i]->SetRender(false);
				m_vecHeroCard[i]->SetMove(false);


				//m_vecHeroCard[i]->SetRelativePos(1800.f, 1800.f,0.f);
				m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
			}


		}

		SetRendernormal();

	}
	void SettingGone()
	{
		
		for (int i = 0 ;i < m_vecNormalCard.size(); ++i)
		{
			m_vecNormalCard[i]->SetRelativePos(0.f, 1000.f, 0.f);
			//m_vecNormalCard[i]->SetRender(false);
			m_vecNormalCard[i]->SetStartHandPos(m_vecNormalCard[i]->GetRelativePos());
			m_vecNormalCard[i]->SetMove(false);
		}

		for (int i = 0; i < m_vecHeroCard.size(); ++i)
		{
			m_vecHeroCard[i]->SetRelativePos(0.f, 1000.f, 0.f);
		//	m_vecHeroCard[i]->SetRender(false);
			m_vecHeroCard[i]->SetStartHandPos(m_vecHeroCard[i]->GetRelativePos());
			m_vecHeroCard[i]->SetMove(false);
		}
		
	}
	void AddHeroCard(CCard* card)
	{
		card->SetRelativePos(71.f, 229.f, 0.f);
		for (int i = 0 ;i < m_vecHeroCard.size(); ++i)
		{
			card->AddWorldPos(card->GetRelativeScale().x, 0.f, 0.f);
		}
	
		card->SetDeck(this);
	
		//card->SetRender(false);
		card->SetStartHandPos(card->GetRelativePos());
		m_vecHeroCard.push_back(card);
	}
	void AddNormalCard(CCard* card)
	{
		//card->SetRelativePos(401.f, 19.f, 0.f);
		card->SetRelativePos(401.f, 19.f, 0.f);
		for (int i = 0 ;i < m_vecNormalCard.size(); ++i)
		{
			card->AddWorldPos(card->GetRelativeScale().x, 0.f, 0.f);
		}
	
	
		card->SetDeck(this);
		card->SetStartHandPos(card->GetRelativePos());
	
		m_vecNormalCard.push_back(card);
	}
	void AddNormal1Card(CCard* card)
	{
		//card->SetRelativePos(401.f, 19.f, 0.f);
		card->SetRelativePos(401.f, 19.f, 0.f);
		for (int i = 0; i < m_vecNormalCard.size(); ++i)
		{
			card->AddWorldPos(card->GetRelativeScale().x, 0.f, 0.f);
		}

		card->SetCardIndex(m_vecNormalCard.size());
		card->SetDeck(this);
		card->SetStartHandPos(card->GetRelativePos());

		m_vecNormalCard.push_back(card);
	}
	void AddHero1Card(CCard* card)
	{
		card->SetRelativePos(71.f, 229.f, 0.f);
		for (int i = 0; i < m_vecHeroCard.size(); ++i)
		{
			card->AddWorldPos(card->GetRelativeScale().x, 0.f, 0.f);
		}

		card->SetDeck(this);
		card->SetCardIndex(m_vecHeroCard.size());
		//card->SetRender(false);
		card->SetStartHandPos(card->GetRelativePos());
		m_vecHeroCard.push_back(card);
	}
	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDeck* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void RotationZ(float DeltaTime);
	void RotationZInv(float DeltaTime);
	void Fire(float DeltaTime);
	void Triple(float DeltaTime);
	void Skill2(float DeltaTime);

public:
	void AnimationFrameEnd(const std::string& Name);
	void CollisionBeginMouse(const Vector2& result, CCollider* Collider);
	void CollisionEndMouse(const Vector2& result, CCollider* Collider);
	void SetBack();
	void SetPlayer2();
	void SetTexByHeroIndex(int index);
	void SetDonSelectTime();
	void ShowCard();
	CCard* CreateCardNotPush(int Cardindex, int Heroindex, Card_Type type, Card_Class cardcalss);
protected:
	CCard* CreateCard(int Cardindex,int Heroindex,Card_Type type,Card_Class cardcalss);
	
	void SelectCardInsert1(CDeck* deck);
	void SelectCardInsert2(CDeck* deck);
	
};

