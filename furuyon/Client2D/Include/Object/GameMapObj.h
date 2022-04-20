
#pragma once

#include "GameObject.h"
#include "Component/TileMapComponent.h"
#include "Component/SpriteComponent.h"
#include "Card.h"
#include "Deck.h"
#include "AttackCard.h"
#include "../UI/FocusHUDWidget.h"
#include "../UI/GaeSiPhaseHUDWidget.h"
#include "../UI/HeroHUDUI.h"
#include "../UI/Hero2HUDUI.h"
#include "../UI/GameMapWindow.h"
#include "../UI/PhaseHUDWidget.h"
#include "../UI/MulrigunHUDWidget.h"
#include "../UI/CardUseHUDWidget.h"
#include "../UI/GameMapAnimation.h"
#include "../Ai/Player2Ai.h"
#include "RangeObj.h"
#include "../UI/BackHUDWidget.h"
struct AttackInfo
{
	int Min;
	int Max;
	int sh;
	int li;
	
	
};

class CGameMapObj :
	public CGameObject
{
	friend class CScene;

protected:
	CGameMapObj();
	CGameMapObj(const CGameMapObj& obj);
	virtual ~CGameMapObj();

protected:
	class CLogObj* m_LogObj;
	CPlayer2Ai* m_Ai;
protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	//CSharedPtr<CSpriteComponent> m_BackCard;
	//CSharedPtr<CMaterial>   m_SpriteMtrl;
	CSharedPtr<CSpriteComponent> m_GameMapBackGround;
	CSharedPtr<CMaterial>   m_SpriteMtrl2;
	CSharedPtr<CSpriteComponent> m_HeroDeckBackGround;
	CSharedPtr<CMaterial>   m_HeroDeckBackGroundMtrl;
	CSharedPtr<CSpriteComponent> m_Hero2DeckBackGround;
	CSharedPtr<CMaterial>   m_Hero2DeckBackGroundMtrl;
	CSharedPtr<CSpriteComponent> m_AlphaBlack;
	CSharedPtr<CMaterial>   m_AlphaBlackMtrl;
	CSharedPtr<CSpriteComponent> m_Cardlist;
	CSharedPtr<CMaterial>   m_CardlistMtrl;
	int m_Range;
	int m_Dust;

	// Player1
	int m_Player1_Life;
	int m_Player1_Shiled;
	int m_Player1_Mana;
	int m_Player1_focus;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Deck;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Hand;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Use;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Back;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Hero;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_Building;
	std::vector<CSharedPtr<CCard>> m_vecPlayer1_HeorUse;

	CSharedPtr<CColliderBox2D> m_vecPlayer1_focus_Collider;

	class CDeck* m_Player1_Deck;
	// Player1
	int m_Player2_Life;
	int m_Player2_Shiled;
	int m_Player2_Mana;
	int m_Player2_focus;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Deck;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Hand;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Use;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Back;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Hero;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_Building;
	std::vector<CSharedPtr<CCard>> m_vecPlayer2_HeorUse;
	std::stack<CSharedPtr<CCard>> m_stackCreateAttackCard;
	std::stack<CSharedPtr<CCard>> m_stackUseCard;
	//std::queue<CSharedPtr<CAttackCard>> m_queAttackCard;
	std::vector<CSharedPtr<CCard>> m_vecplayer1DauegCard;

	std::vector<CSharedPtr<CRangeObj>> m_vecRange;
	class CDeck* m_Player2_Deck;

	bool m_Backtriger;
	class CCard* m_SceneCard;
	int m_Card5Tick;
	class CAttackCard* m_bozoCard;
	class CAttackCard* m_bozoCard1;
	class CAttackCard* m_bozoCard2;
	class CAttackCard* m_bozoCard10;
	// Widget
	CSharedPtr<CWidgetComponent> m_FocusWidgetComponent;
	CFocusHUDWidget* m_FocusWidget;
	CSharedPtr<CWidgetComponent> m_GaeSiPhaseWidgetComponent;
	CGaeSiPhaseHUDWidget* m_GaeSiPhaseWidget;
	CSharedPtr<CWidgetComponent> m_HeroWidgetComponent;
	CHeroHUDUI* m_HeroWidget;
	CSharedPtr<CWidgetComponent> m_GameMapWidgetComponent;
	CGameMapWindow* m_GameMapWidget;
	CSharedPtr<CWidgetComponent> m_Hero2WidgetComponent;
	CHero2HUDUI* m_Hero2Widget;
	CSharedPtr<CWidgetComponent> m_PhaseWidgetComponent;
	CPhaseHUDWidget* m_PhaseWidget;
	CSharedPtr<CWidgetComponent> m_MuligunWidgetComponent;
	CMulrigunHUDWidget* m_MuligunWidget;
	CSharedPtr<CWidgetComponent> m_CardUseWidgetComponent;
	CCardUseHUDWidget* m_CardUseWidget;
	CSharedPtr<CWidgetComponent> m_BackWidgetComponent;
	CBackHUDWidget* m_BackWidget;
	//CSharedPtr<CWidgetComponent> m_GameMapAnimationComponent;
	//CGameMapAnimation* m_GameMapAnimation;
	bool m_SelectTiming;
	bool m_FocusTriger;
	bool m_UseTriger;


	float m_defaulttimer;
	int m_turn;
	int m_Player1Gaesi;
	bool m_Player1GaesiEnd;
	int m_Player1Main;
	bool m_Player1MainEnd;
	int m_Player1End;
	bool m_Player1EndEnd;
	int m_Player2Gaesi;
	bool m_Player2GaesiEnd;
	int m_Player2Main;
	bool m_Player2MainEnd;
	int m_Player2End;
	bool m_Player2EndEnd;
	bool m_Muligun;
	bool m_MuligunEnd;



	int m_TenreokuCheck;
	int m_TenreokuCheckPlayer2;
	int m_buff_Range_Min;
	int m_buff_Don_Daeug;
	int m_buff_Shiled_Attack;
	int m_buff_Life_Attack;
	
	int m_chogeok;
	bool m_hero;
	bool m_Hero1_Card4_Normal;
	bool m_Hero1_Card4_Normal_Player2;
	int m_Hero1_Card6_Normal;
	bool m_Hero1_Card6_Normal_Player2;
	bool m_Hero1_Card2_Hero;
	bool m_Hero1_Card2_Hero_Player2;
	bool m_Hero3_Card4_Normal;
	bool m_Hero3_Card4_Normal_Player2;
	bool m_Hero3_Card6_Normal;
	bool m_Hero3_Card6_Normal_Player2;
	int m_Hero3_Card6_Normal_UITriger;
	float m_TestDelayTime;
	bool m_Player1_win;
	bool m_player2_win;
	bool m_player1_teum;
	bool m_player2_teum;
	bool m_player1_Attackselect;
	bool m_player1_AttackselectEnd;
	bool m_Player1_AttackSelectResult;
	class CAnimationCard* m_AnimationCard;

	int m_player1_AttackSelectShiledtemp;
	int m_player1_AttackSelectLifetemp;
	bool m_player1_DauegSelect;
	int m_DALIN_Range;
	bool m_Player1_Select_USEANDBACK;
	bool m_LogLook;
	bool m_player1use;
	bool m_player1back;
	bool m_Ai1use;
	bool m_Ai1back;
	bool m_usebackwidgetcheck;
	bool m_Player1Press;
	bool m_AiPress;
	int m_WhoFirst;
	bool m_Down;
	bool m_Up;
	bool m_Push;
public:
	void SetWhoFirst(int i)
	{
		m_WhoFirst = i;
	}
	bool GetAiPress() const
	{
		return m_AiPress;
	}
	bool GetPlayer1Press() const
	{
		return m_Player1Press;
	}
	bool GetPlayer2Win() const
	{
		return m_player2_win;
	}
	bool GetPlayer1Win() const
	{
		return m_Player1_win;
	}
	bool GetSelectUSEANDBACK() const
	{
		return m_Player1_Select_USEANDBACK;
	}
	void SetSelectUSEANDBACK(bool b)
	{
		m_Player1_Select_USEANDBACK = b;
	}
	void AddDALINRange(int i)
	{
		m_DALIN_Range += i;
	}
	int GetDALINRange() const
	{
		return m_DALIN_Range;
	}
	void SetDALINRagne(int i)
	{
		m_DALIN_Range = i;
	}
	void SetPlayer1Teum(bool b)
	{
		m_player1_teum = b;
	}
	void SetPlayer1DauegCard(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecplayer1DauegCard = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1DauegCard() const
	{
		return m_vecplayer1DauegCard;
	}
	void SetTestDelayTime(float fl)
	{
		m_TestDelayTime = fl;
	}
	void Setplayer1_Attackselect(bool b)
	{
		m_player1_Attackselect = b;
	}
	void Setplayer1_AttackselectEnd(bool b)
	{
		m_player1_AttackselectEnd = b;
	}
	void SetPlayer1_AttackSelectResult(bool b)
	{
		m_Player1_AttackSelectResult = b;
	}
	int GetBuffRangeMin() const
	{
		return m_buff_Range_Min;
	}
	void PushAnimationCard2(int Hero, int card, Card_Class cardclass);
	void PushAnimationCard(CCard* card, int daeug);
	int GetTenreokuCheckPlayer2() const
	{
		return m_TenreokuCheckPlayer2;
	}
	void AddTenreokuCheckPlayer2(int i)
	{
		m_TenreokuCheckPlayer2 += i;
	}
	void SetTenreokuCheckPlayer2(int i)
	{
		m_TenreokuCheckPlayer2 = i;
	}
	void SetPlayer2VecHeroUse(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_HeorUse = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecHeorUse() const
	{
		return m_vecPlayer2_HeorUse;
	}
	void SetPlayer2VecBuilding(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_Building = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecBuilding() const
	{
		return m_vecPlayer2_Building;
	}
	void SetPlayer2VecHero(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_Hero = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecHero() const
	{
		return m_vecPlayer2_Hero;
	}
	void SetPlayer2VecBack(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_Back = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecBack() const
	{
		return m_vecPlayer2_Back;
	}
	void SetPlayer2VecUse(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_Use = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecUse() const
	{
		return m_vecPlayer2_Use;
	}
	void SetPlayer2VecHand(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer2_Hand = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecHand() const
	{
		return m_vecPlayer2_Hand;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2VecDeck() const
	{
		return m_vecPlayer2_Deck;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1VecUse() const
	{
		return m_vecPlayer1_Use;
	}
	void SetPlayer1VecUse(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer1_Use = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1VecHand() const
	{
		return m_vecPlayer1_Hand;
	}
	void SetPlayer1VecHand(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer1_Hand = vec;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1VecBack() const
	{
		return m_vecPlayer1_Back;
	}
	void SetPlayer1VecBack(std::vector<CSharedPtr<CCard>> vec)
	{
		m_vecPlayer1_Back = vec;
	}
	size_t GetPlayer2DeckSize() const
	{
		return m_vecPlayer2_Deck.size();
	}
	size_t GetPlayer1DeckSize() const
	{
		return m_vecPlayer1_Deck.size();
	}
	void SetPlayer2Gaesi(bool b)
	{
		m_Player2Gaesi = b;
	}
	void SetPlayer1GaesiEnd(bool b)
	{
		m_Player1GaesiEnd = b;
	}
	void SetPlayer1Gaesi(bool b)
	{
		m_Player1Gaesi = b;
	}
	bool GetPlayer2MainEnd() const
	{
		return m_Player2MainEnd;
	}
	void SetPlayer2MainEnd(bool b)
	{
		m_Player2MainEnd = b;
	}
	void SetPlayer2End(bool b)
	{
		m_Player2End = b;
	}
	void SetPlayer2Main(bool b)
	{
		m_Player2Main = b;
	}
	bool GetPlayer1MainEnd() const
	{
		return m_Player1MainEnd;
	}
	void SetPlayer1MainEnd(bool b)
	{
		m_Player1MainEnd = b;
	}
	void SetPlayer1End(bool b)
	{
		m_Player1End = b;
	}
	void SetPlayer1EndEnd(bool b)
	{
		m_Player1EndEnd = b;
	}
	void SetPlayer1Main(bool b)
	{
		m_Player1Main = b;
	}
	void SetMuligun(bool b)
	{
		m_Muligun = b;
	}
	void SetMuligunEnd(bool b)
	{
		m_MuligunEnd = b;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1Hero() const
	{
		return m_vecPlayer1_Hero;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1Hand() const
	{
		return m_vecPlayer1_Hand;
	}
	CSharedPtr<CSpriteComponent> GetAlphaBlack() const
	{
		return m_AlphaBlack;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1Buildingvector() const
	{
		return m_vecPlayer1_Building;
	}
	CSharedPtr<CSpriteComponent>  GetPlayer2BackGround() const
	{
		return  m_Hero2DeckBackGround;
	}
	CSharedPtr<CSpriteComponent>  GetPlayer1BackGround() const
	{
		return  m_HeroDeckBackGround;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer2Backvector() const
	{
		return m_vecPlayer2_Hero;
	}
	std::vector<CSharedPtr<CCard>> GetPlayer1Backvector() const
	{
		return m_vecPlayer1_Hero;
	}
	void AddPlayer2Life(int focus)
	{
		m_player2_teum = true;
		m_GameMapWidget->PushAnimation(Player2LifeNumber);
		m_Player2_Life += focus;
		if (m_Player2_Life <= 0)
		{
			if(m_player2_win == false)
				m_Player1_win = true;
		}
	}
	int GetPlayer2Life() const
	{
		return m_Player2_Life;
	}
	void SetPlayer2Life(int life)
	{
		m_Player2_Life = life;
	}
	void AddPlayer2Shiled(int focus)
	{	// 충음정 Ai 설계
		m_GameMapWidget->PushAnimation(Player2ShiledNumber);
		if (focus == -100)
		{
			m_Player2_Shiled -= 1;
			return;
		}
		if (focus < 0)
		{
			if (m_Hero3_Card6_Normal_Player2)
			{
				AiHero3Card6Check(focus);
				return;
			}
		}

		m_Player2_Shiled += focus;
	}
	int GetPlayer2Shiled() const
	{
		return m_Player2_Shiled;
	}
	void SetPlayer2Shiled(int Shiled)
	{
		m_Player2_Shiled = Shiled;
	}
	void AddPlayer2Mana(int focus)
	{
		m_GameMapWidget->PushAnimation(Player2ManaNumber);
		m_Player2_Mana += focus;
	}
	int GetPlayer2Mana() const
	{
		return m_Player2_Mana;
	}
	void SetPlayer2Mana(int focus)
	{
		m_Player2_Mana = focus;
	}
	void AddPlayer2focus(int focus)
	{
		if (focus == 1 && m_AiPress == true)
		{
			m_AiPress = false;
			return;
		}
		m_GameMapWidget->PushAnimation(Player2FocusNumber);
		m_Player2_focus += focus;
		if (m_Player2_focus >= 2)
			m_Player2_focus = 2;
	}
	int GetPlayer2focus() const
	{
		return m_Player2_focus;
	}
	void SetPlayer2focus(int focus)
	{
		m_Player2_focus = focus;
	}
	void AddPlayer1Life(int focus)
	{
		m_player1_teum = true;
		m_GameMapWidget->PushAnimation(Player1LifeNumber);
		m_Player1_Life += focus;
		if (m_Player1_Life <= 0)
		{
			if (m_Player1_win == false)
				m_player2_win = true;
		}
	}
	int GetPlayer1Life() const
	{
		return m_Player1_Life;
	}
	void SetPlayer1Life(int life)
	{
		m_Player1_Life = life;
	}
	void AddPlayer1Shiled(int focus)
	{
		m_GameMapWidget->PushAnimation(Player1ShiledNumber);
		if (focus == -100)
		{
			m_Player1_Shiled -= 1;
			return;
		}
		if (focus < 0)
		{
			if (m_Hero3_Card6_Normal)
			{
				PlayerHeor3Card6Check(focus);
				return;
			}

		}
		
		m_Player1_Shiled += focus;
	}
	int GetPlayer1Shiled() const
	{
		return m_Player1_Shiled;
	}
	void SetPlayer1Shiled(int Shiled)
	{
		m_Player1_Shiled = Shiled;
	}
	void AddPlayer1Mana(int focus)
	{
		m_GameMapWidget->PushAnimation(Player1ManaNumber);
		m_Player1_Mana += focus;
	}
	int GetPlayer1Mana() const
	{
		return m_Player1_Mana;
	}
	void SetPlayer1Mana(int focus)
	{
		m_Player1_Mana = focus;
	}
	void AddPlayer1focus(int i)
	{
		if (i == 1 && m_Player1Press == true)
		{
			m_Player1Press = false;
			return;
		}

		m_GameMapWidget->PushAnimation(Player1FocusNumber);
		m_Player1_focus += i;
		if (m_Player1_focus >= 2)
			m_Player1_focus = 2;
	}
	int GetPlayer1focus() const
	{
		return m_Player1_focus;
	}
	void SetPlayer1focus(int focus)
	{
		m_Player1_focus = focus;
	}
	void AddDust(int i)
	{
		m_GameMapWidget->PushAnimation(DustNumber);
		m_Dust += i;
	}
	int GetDust() const
	{
		return m_Dust;
	}
	void SetDust(int dust)
	{
		m_Dust = dust;
	}
	void AddRange(int i)
	{
		m_GameMapWidget->PushAnimation(RangeNumber);


		if (i == 1)
			RangeUp();
		else if (i == -1)
			RangeDown();


		m_Range += i;
	}
	int GetRange() const
	{
		return m_Range;
	}
	void SetRange(int range)
	{
		m_Range = range;
	}
	bool GetSelectTiming() const
	{
		return m_SelectTiming;
	}
	void SetSelectTiming(bool b)
	{
		m_SelectTiming = b;
	}
	void SetPlayer1HeroCard(CCard* card)
	{
		CCard* temp = m_Player1_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer1_Hero.push_back(temp);
	}
	int GetPlayer2HeroCardSize() const
	{
		return m_vecPlayer2_Hero.size();
	}
	void SetPlayer2HeroCard(CCard* card)
	{
		CCard* temp = m_Player2_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer2_Hero.push_back(temp);
	}
	void SetPlayer1handCard(CCard* card)
	{	
		CCard* temp = m_Player1_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer1_Hand.push_back(temp);
	}
	void SetPlayer2handCard(CCard* card)
	{
		CCard* temp = m_Player2_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer2_Hand.push_back(temp);
	}
	void SetPlayer1DeckCard(CCard* card)
	{
		CCard* temp = m_Player1_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer1_Deck.push_back(temp);
	}
	void SetPlayer2DeckCard(CCard* card)
	{
		CCard* temp = m_Player2_Deck->CreateCardNotPush(card->GetCardIndex(), card->GetHeroIndex(), card->GetCardType(), card->GetCardClass());
		m_vecPlayer2_Deck.push_back(temp);
	}
	void SetPlayer1Deck(class CDeck* deck)
	{
		m_Player1_Deck = deck;
	}
	void SetPlayer2Deck(class CDeck* deck)
	{
		m_Player2_Deck = deck;
	}
public:
	void StartGameHandSetting();
	void HandSortSetting();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGameMapObj* Clone();

public:
	void Player1CardToBack();
	void PlayerCardToUse();

private:
	void CollisionBackEnd(const HitResult& result, CCollider* Collider);
	void CollisionUseEnd(const HitResult& result, CCollider* Collider);
	void CollisionFocusMouseStart(const Vector2& pos, CCollider* Collider);
	void CollisionFocusMouseEnd(const Vector2& pos, CCollider* Collider);

private:
	void Player1BackCheck();
	void Player1UseFocus();
	
	void Player1UseCheck();
public:
	bool Player1UseAttackCard(class CAttackCard* card);
	bool Player1UseSpellCard(class CSpellCard* card);
	bool Player1UseBuildingCard(class CBuildingCard* card);


public:
	int DrawACard(int drawCounter);
	int DrawACard2(int drawCounter);
	void RefreshDeck();
	void RefreshDeck2();
	void OpenHeroDeck();
	void CloseHeroDeck();
	void HeroDeckSorting();
	void Player1BuildingSetPos();
	void Mulrigungo(CCard* first, CCard* Second, CCard* Thrid);
	void Player1CardBurn();
	void Player1BuildingUseAnimation();
private:
	void DrawTest(float DeltaTime);
	void Player1UseLook(float DeltaTime);
	void Player1BackLook(float DeltaTime);
	void AiUseLook(float DeltaTime);
	void AiBackLook(float DeltaTime);
	void RefreshTest(float DeltaTime);
public:
	void UseAttackBYIndex(int player, class CAttackCard* attackcard);
	void UseAttackBYIndex(int player, CCard* card);
	void UseSpellBYIndex(int player, int hero,int normal,Card_Class cardclass, int spell);
	void UseSpellBYIndex(int player, CCard* card);
	void UseDaeugBYCard(CCard* card);
	void UseBuildingBreakBYIndex(int player, int hero, int normal, Card_Class cardclass);
	void UseBuildingBreakBYIndex(int player, CCard* card);
	void UseBuildingBYIndex(int player, int hero, int normal, Card_Class cardclass);
	void UseBuildingBYIndex(int player, CCard* card);
	void AttackEndEffect(int player, int hero, int normal, Card_Class cardclass);
public:
	bool AttackUseCard(int Player,class CAttackCard* attackcard);
public:
	void buffreset();
	void Player1Gaesi();
	void Player1GaesiBuilding();
	void Player2GaesiBuilding();
public:
	bool CreateAttack(int player,int min, int max, int sh, int li, int hero,int normal,int dondaeug, Card_Class cardclass, CAttackCard* card);
	void Player2End();
	void AttackonTheStack(CAttackCard* attackcard);
private:
	void UseBuildingUsingBYIndex(int hero, int normal, Card_Class cardclass);
	void AiMainPhase();
	void AiHandEnable();
	void Player1Mainend();
	void Player2Mainend();
	AttackInfo AttackCardDamageCalculate(int min, int max, int sh, int li, int hero, int player);
public:
	bool Player1Daueg(CCard* card);
	bool AiDaueg();
	void Player1OpenDauegButton(class CAttackCard* card);
	void Player1DauegExit(CCard* card);
	void UseCard(CCard* card);
	void SetDauegAnimation();
	
	void Turnendbuffreset(int player);
	void GaesiStart();
	void PlayerHeor3Card6Check(int focus);
	void AiHero3Card6Check(int focus);
	void Player1BuildingZeroCheck();
	void Player2BuildingZeroCheck();
	class CBuildingCard* PlayerHero3Card6();
	void HandSortSetting2();
	void Player1CardManaCost(CCard* card);
	void AnimationHide();
	void CreateAttackAiDaeugCheck(CCard* card);
	void LogCreate(CCard* card, CCard* card2, int index, int player);
	void SettingPlayer1Use();
	void SettingPlayer1Back();
	void SettingAiUse();
	void SettingAiBack();
	void SettingPlayer1UseBacksellecttime();
	void SettingPlayer1UseBackUnSellecttime();
	void SettingAllgone();
	int SumPlayer2HeroManaCost();
	bool Hero8Card4(CCard* card, CCard* card1);
	void RefreshFree();
	void Refresh2Free();
	void Player1HandtoUse(CCard* card);
	void Player1HandUnSellect();
	void Player1HeroDeckUnSellectTime();
	int Player1HandNotAttack();
	void ManaSound();
	void OraSound();
	void ForwardSound();
	void BackWardSound();
	void ItalSound();
	void TurnEndSound();
	void DaeungSound();
	void HideSound();
	void DrawSound();
	void RefreshSound();
	void MissSound();
	void CardUseCloseWidget();
	bool Player1FocusCheck();
	bool Player2FocusCheck();
	void RangeUp();
	void RangeDown();
	void WhicSound();
	void ESCButton(float Delata);
	void CardClickSound();

	
};	

