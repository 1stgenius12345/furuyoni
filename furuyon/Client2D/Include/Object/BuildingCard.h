#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/BuildingHUDWidget.h"
#include "Card.h"

class CBuildingCard :
	public CCard
{
	friend class CScene;
public:
	CBuildingCard();
	CBuildingCard(const CBuildingCard& obj);
	virtual ~CBuildingCard();

protected:

	// Widget
	CSharedPtr<CWidgetComponent> m_NabWidgetComponent;
	CBuildingHUDWidget* m_NabWidget;

	int m_Nab;
	int m_Nabpoint;
	bool m_teum;

public:
	bool Getteum() const
	{
		return m_teum;
	}
	void Setteum(bool i)
	{
		m_teum = i;
	}
	void AddNab(int i)
	{
		m_Nab += i;
	}
	int GetNab() const
	{
		return m_Nab;
	}
	void SetNab(int i)
	{
		m_Nab = i;
	}
	void AddNabPoint(int i)
	{
		m_Nabpoint += i;
	}
	int GetNabpoint() const
	{
		return m_Nabpoint;
	}
	void SetNabPoint(int i)
	{
		m_Nabpoint = i;
	}

public:

	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBuildingCard* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	virtual void CreateCardSetting();


public:

private:
	void BuildingCardSetting(int nab, int dae, int jeo);
	void BuildingCardSetting(int nab, int dae, int jeo,int mana);
	
};

