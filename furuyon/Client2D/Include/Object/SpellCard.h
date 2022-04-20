#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "Card.h"

class CSpellCard :
	public CCard
{
	friend class CScene;
public:
	CSpellCard();
	CSpellCard(const CSpellCard& obj);
	virtual ~CSpellCard();

protected:
	int m_SpellTriger;

public:
	int GetSpellTriger() const
	{
		return m_SpellTriger;
	}
	void SetSpellTriger(int i)
	{
		m_SpellTriger = i;
	}

public:

	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSpellCard* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	virtual void CreateCardSetting();

public:


public:
	void SpellCardSetting(int triger,int dae,int jeo);
	void SpellCardSetting(int triger, int dae, int jeo, int mana);
};

