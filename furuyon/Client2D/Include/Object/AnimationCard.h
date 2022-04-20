#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "Card.h"


struct CardInfo
{
	int CardIndex;
	int HeroIndex;
	Card_Class CardClass;
	int Player;
	int Daeug;
};


class CAnimationCard :
	public CGameObject
{
	friend class CScene;
	friend class CDeck;

public:
	CAnimationCard();
	CAnimationCard(const CAnimationCard& obj);
	virtual ~CAnimationCard();

protected:


	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CMaterial>   m_SpriteMtrl;
	CSharedPtr<CSpriteComponent> m_sakura;
	CSharedPtr<CMaterial>  m_sakuraMtrl;
	CSharedPtr<CSpriteComponent> m_daeug;
	CSharedPtr<CMaterial>  m_daeugMtrl;
	CSharedPtr<CSpriteComponent> m_Card2;
	CSharedPtr<CMaterial>  m_Card2Mtrl;
protected:
	int m_CardIndex;
	int m_HeroIndex;
	int m_PlayerIndex;
	Card_Class m_CardClass;


	bool m_Animationtriger;
	float m_AnimationTimer;
	float m_Axcel;
	std::queue<CardInfo> m_que_CardInfo;
	class CGameMapObj* m_GameMapObj;

	int m_AnimIndex;
	bool m_Settinghide;
	bool m_Settinghidestate;
	bool m_DaeungSoundCheck;
	bool m_MissSoundCheck;

public:
	void SetPlayerIndex(int i)
	{
		m_PlayerIndex = i;
	}

	void SetAnimIndex(int i)
	{
		m_AnimIndex = i;
	}
	bool GetCardInfoEmpty() const
	{
		
		return !m_Animationtriger;
	}
	void SetGameMapObj(class CGameMapObj* obj)
	{
		m_GameMapObj = obj;
	}
	void PushCardInfo(int HeroIndex, int cardindex, Card_Class cardclass,int pla,int Daeug)
	{
		CardInfo tempinfo;
		tempinfo.CardClass = cardclass;
		tempinfo.CardIndex = cardindex;
		tempinfo.HeroIndex = HeroIndex;
		tempinfo.Player = pla;
		tempinfo.Daeug = Daeug;
		m_que_CardInfo.push(tempinfo);
	}
	int GetCardIndex() const
	{
		return m_CardIndex;
	}
	int GetHeroIndex() const
	{
		return m_HeroIndex;
	}
	

	Card_Class GetCardClass() const
	{
		return m_CardClass;
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
	const std::string TCHARToString(const TCHAR* ptsz)
	{
		int len = (int)wcslen((wchar_t*)ptsz);

		char* psz = new char[2 * len + 1];

		wcstombs_s(nullptr, psz, sizeof(wchar_t) * len, (wchar_t*)ptsz, 2 * len + 1);
		std::string s = psz;
		delete[] psz;

		return s;
	}

	
	void SetCardUnClick();
	void SetCardClick();

	bool IsHero() const
	{
		if (m_CardClass == Card_Class::Hero)
			return true;
		return false;
	}
	
	void SetHero()
	{
		m_CardClass = Card_Class::Hero;
		
	}
	

public:
	
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CAnimationCard* Clone();
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
	void CreatCard(int Cardindex, int Heroindex, Card_Class cardcalss);
	void CreatCard2(int Cardindex, int Heroindex, Card_Class cardcalss);
	void CreateTex();
	void CreateTex2();
	void SettingGone();
	void SettingHide();



};

