#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "Card.h"
#include "../UI/SelectHUDWidget.h"
#include "Deck.h"

class CSelectCard :
	public CGameObject
{
	friend class CScene;

protected:
	CSelectCard();
	CSelectCard(const CSelectCard& obj);
	virtual ~CSelectCard();

protected:
	CSharedPtr<CColliderBox2D> m_NormalSelect;
	CSharedPtr<CColliderBox2D> m_HeroSelect;
	CSharedPtr<CMaterial>   m_SpriteMtrl2;
	CSharedPtr<CSpriteComponent> m_GameMapBackGround;

	CSharedPtr<CMaterial>   m_SpriteMtrl3;
	CSharedPtr<CSpriteComponent> m_CardBackGround;

	CSharedPtr<CWidgetComponent> m_SelectWidgetComponent;
	class CSelectHUDWidget* m_SelectWidget;


	class CDeck* m_Deck;

protected:
	bool m_NormalInthebox;
	bool m_HeroInthebox;
	class CCard* m_pCard;

public:
	
	void SetDeck(class CDeck* deck)
	{
		m_Deck = deck;
	}
	void SetSelectWidget(class CSelectHUDWidget* widget)
	{
		m_SelectWidget = widget;
	}
	class CSelectHUDWidget* GetSelectWidget() const
	{
		return m_SelectWidget;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSelectCard* Clone();
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
	void CollisionBeginNormal(const HitResult& result, CCollider* Collider);
	void CollisionBeginHero(const HitResult& result, CCollider* Collider);
	void CollisionEndNormal(const HitResult& result, CCollider* Collider);
	void CollisionEndHero(const HitResult& result, CCollider* Collider);
	void CollisionEndMouse(const Vector2& result, CCollider* Collider);
};

