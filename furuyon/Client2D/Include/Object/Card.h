#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/PlayerWorldInfoWidget.h"
//#include "../UI/SelectHUDWidget.h"




enum class Card_Type
{
	Attack,
	Spell,
	Building
};
enum class Card_Class
{
	Normal,
	Hero
};

class CCard :
	public CGameObject
{
	friend class CScene;
	friend class CDeck;
	
public:
	CCard();
	CCard(const CCard& obj);
	virtual ~CCard();

protected:

	
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CMaterial>   m_SpriteMtrl;
	CSharedPtr<CSceneComponent> m_Rotation;
	//CSharedPtr<CSceneComponent> m_Muzzle;
	//CSharedPtr<CSpriteComponent> m_SpriteLeftChild;
	//CSharedPtr<CSpriteComponent> m_SpriteRightChild;
	//CSharedPtr<CSceneComponent> m_LeftMuzzle;
	//CSharedPtr<CSceneComponent> m_RightMuzzle;
	//CSharedPtr<CSpringArm2D> m_Arm;
	//CSharedPtr<CCamera> m_Camera;

	CSharedPtr<CColliderBox2D> m_Body;
	//CSharedPtr<CWidgetComponent> m_PlayerInfoWidgetComponent;
	//CPlayerWorldInfoWidget* m_PlayerInfoWidget;

//	class CAnimation2D* m_Animation2D;

protected:
	
	int m_CardIndex;
	int m_HeroIndex;
	//const TCHAR* m_CardName;
	std::string m_CardContents;


	float  m_TempWorldZ;
	bool m_MouseIsit = false;
	bool m_bMove;
	bool m_bRender;
	bool m_Select;

	Vector3 m_StartHandPos;

    class CDeck* m_pDeck;

	Card_Type m_CardType;
	Card_Class m_CardClass;


	float m_CardClickDelay;
	float m_CardClickDelayMAX;

	bool m_Loopup;
	bool m_Use;

	int m_Daeung;
	int m_Tenreok;
	int m_ManaCost;

	bool m_Lookable;
	bool m_SelectTime;
	int m_Player;
	bool m_Daeung_Triger;
public:
	void SetLoopup(bool b)
	{
		m_Loopup = b;
	}
	bool GetDaeungTriger() const
	{
		return m_Daeung_Triger;
	}
	void SetDaeungTriger(bool b)
	{
		m_Daeung_Triger = b;
	}
	int GetPlayer() const
	{
		return m_Player;
	}
	void SetPlayer(int i)
	{
		m_Player = i;
	}
	void SetCardIndex(int i)
	{
		m_CardIndex = i;
	}
	void SetHeroIndex(int i)
	{
		m_HeroIndex = i;
	}
	int GetDaeung() const
	{
		return m_Daeung;
	}
	bool GettLook() const
	{
		return m_Loopup;
	}
	void SetSelect(bool b)
	{
		m_Select = b;
	}
	bool GetSelectTime() const
	{
		return m_SelectTime;
	}
	void SetSelectTime(bool b)
	{
		m_SelectTime = b;
	}
	int GetTenreok() const
	{
		return m_Tenreok;
	}
	int GetCardIndex() const
	{
		return m_CardIndex;
	}
	int GetHeroIndex() const
	{
		return m_HeroIndex;
	}
	int GetManaCosT() const
	{
		return m_ManaCost;
	}
	Card_Type GetCardType() const
	{
		return m_CardType;
	}
	void SetCardType(Card_Type type) 
	{
		m_CardType = type;
	}
	Card_Class GetCardClass() const
	{
		return m_CardClass;
	}
	bool GetLookable() const
	{
		return m_Lookable;
	}
	void SetLookable(bool b)
	{
		m_Lookable = b;
	}
	void SetBack()
	{
		if (m_CardClass == Card_Class::Normal)
		{
			m_SpriteMtrl->AddTexture("back", TEXT("card/back.jpg"));
		}
		else
		{
			m_SpriteMtrl->AddTexture("backHero", TEXT("card/backHero.jpg"));
		}
	
	}
	bool GetUse() const
	{
		return m_Use;
	}
	void SetUse(bool b)
	{
		m_Use = b;
	}
	const std::string TCHARToString(const TCHAR* ptsz)
	{
		int len = (int)wcslen((wchar_t*)ptsz);

		char* psz = new char[2 * len + 1];

		wcstombs_s(nullptr,psz, sizeof(wchar_t)*len, (wchar_t*)ptsz, 2 * len + 1);
		std::string s = psz;


		
		delete[] psz;

		return s;
	}

	void CardInfoBack(CCard* card)
	{
		m_CardIndex = card->m_CardIndex;
		m_HeroIndex = card->m_HeroIndex;
		m_CardClass = card->m_CardClass;
		m_CardType = card->m_CardType;
		
	}
	bool GetSelect() const
	{
		return m_Select;
	}

	class CDeck* GetDeck() const
	{
		return m_pDeck;
	}
	void SetCardClickDelayMakeZero()
	{
		m_CardClickDelay = 0.f;
	}
	void SetCardUnClick();
	void SetCardClick();

	bool IsHero() const
	{
		if (m_CardClass == Card_Class::Hero)
			return true;
		return false;
	}
	void SetTypeAttack()
	{
		m_CardType = Card_Type::Attack;
	}
	void SetTypeBuilding()
	{
		m_CardType = Card_Type::Building;
	}
	void SetTypeSpell()
	{
		m_CardType = Card_Type::Spell;
	}
	void SetHero()
	{
		m_CardClass = Card_Class::Hero;
		//m_Body->SetCollisionProfile("PlayerAttack");
	}
	void SetRender(bool render)
	{
		m_bRender = render;
	}
	void SetMove(bool move)
	{
		m_bMove = move;
	}
	void SetDeck(class CDeck* deck)
	{
		m_pDeck = deck;
	}
	void SetStartHandPosByfloat(float x, float y, float z)
	{
		m_StartHandPos.x = x;
		m_StartHandPos.y = y;
		m_StartHandPos.z = z;
	}
	void SetStartHandPos(Vector3 Pos)
	{
		m_StartHandPos = Pos;
	}

	/*void SetCardName(const TCHAR* name)
	{
		m_PlayerInfoWidget->SetCardName(name);
	}*/
	/*void SetCardInfo(int RangeMin, int RangeMax, int AttackShield, int AttackLife, const TCHAR* Name,const std::string& TextureName, const TCHAR* Texture)
	{
		m_PlayerInfoWidget->SetRangeMin(RangeMin);
		m_PlayerInfoWidget->SetRangeMax(RangeMax);
		m_PlayerInfoWidget->SetAttackShield(AttackShield);
		m_PlayerInfoWidget->SetAttackLife(AttackLife);
		m_PlayerInfoWidget->SetCardName(Name);
		m_PlayerInfoWidget->SetTexture(TextureName,Texture);
	}*/

public:
	//static bool m_MouseClick;
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCard* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	virtual void CreateCardSetting();
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
	void LoopUptherCard();
	void CreatCard(CDeck* deck,int Cardindex, int Heroindex, Card_Type type, Card_Class cardcalss);
	void CreateTex();
	void LoadCard(CDeck* deck, int Cardindex, int Heroindex, Card_Type type, Card_Class cardcals);
	void SettingGone();
	void SellectTextureSetting();
	void UnSellectTextureSetting();
	void SetRenderBack();
	void SetRenderDefault();


};

