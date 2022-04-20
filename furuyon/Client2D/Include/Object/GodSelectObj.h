#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "Card.h"
#include "../UI/GodSelectHUDWidget.h"
#include "Deck.h"

class CGodSelectObj :
	public CGameObject
{
	friend class CScene;

protected:
	CGodSelectObj();
	CGodSelectObj(const CGodSelectObj& obj);
	virtual ~CGodSelectObj();

protected:
	CSharedPtr<CColliderBox2D> m_NormalSelect;
	CSharedPtr<CColliderBox2D> m_HeroSelect;
	CSharedPtr<CMaterial>   m_SpriteMtrl2;
	CSharedPtr<CSpriteComponent> m_GameMapBackGround;

	CSharedPtr<CMaterial>   m_SpriteMtrl3;
	CSharedPtr<CSpriteComponent> m_CardBackGround;

	CSharedPtr<CMaterial>   m_SpriteMtrl4;
	CSharedPtr<CSpriteComponent> m_SelectMegami;

	CSharedPtr<CWidgetComponent> m_SelectWidgetComponent;
	class CGodSelectHUDWidget* m_SelectWidget;


	class CDeck* m_Deck;

protected:
	bool m_NormalInthebox;
	bool m_HeroInthebox;
	class CCard* m_pCard;

public:

	const std::string TCHARToString(const TCHAR* ptsz)
	{
		int len = (int)wcslen((wchar_t*)ptsz);

		char* psz = new char[2 * len + 1];

		wcstombs_s(nullptr, psz, sizeof(wchar_t) * len, (wchar_t*)ptsz, 2 * len + 1);
		std::string s = psz;
		delete[] psz;

		return s;
	}

	void SetDeck(class CDeck* deck)
	{
		m_Deck = deck;
	}
	void SetSelectWidget(class CGodSelectHUDWidget* widget)
	{
		m_SelectWidget = widget;
	}
	class CGodSelectHUDWidget* GetSelectWidget() const
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
	virtual CGodSelectObj* Clone();
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
	void SetMegami3(int index);
};

