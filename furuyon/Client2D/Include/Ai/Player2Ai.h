#pragma once
#include "Ref.h"
#include "../Object/Card.h"
class CPlayer2Ai :
	public CRef
{
public:
	CPlayer2Ai();
	CPlayer2Ai(const CPlayer2Ai& obj);
	virtual ~CPlayer2Ai();
private:
	class CGameMapObj* m_GameMapObj;
	std::queue<CSharedPtr<CCard>> m_queEnableAttackCard;
	std::queue<CSharedPtr<CCard>> m_queEnableSpellCard;
	std::queue<CSharedPtr<CCard>> m_queEnableBuildingCard;
	std::queue<CSharedPtr<CCard>> m_queEnableDaeungCard;
	CSharedPtr<CCard> m_EnableSpecialCard;

	int m_LikeRange;
	int m_LikeMana;
	bool m_DauegTime;

	int m_PlayerAttackMin;
	int m_PlayerAttackMax;
	int m_PlayerAttackShiled;
	int m_PlayerAttackLife;
	int m_PlayerAttackClass;

	bool m_HandBack;
	int m_Hero1;
	int m_Hero2;
public:
	void SetGameMapObj(class CGameMapObj* Obj)
	{
		m_GameMapObj = Obj;
	}
public:
	void Init();
	void Gaesi();
	void End();
	void AiHandEnable();
	int AiEnableAttackSize();
	int AiEnableSpellSize();
	int AiEnableBuildingSize();
	int AiEnableSpecialSize();
	int AiEnableSize();
	void AiEnableClear();
	int AiFocuseUse();
	bool AiHandtoBack();
	bool AiDauengCheck(class CAttackCard* card);
	CCard* AiUseDaueng();
	bool LikeRangeCheck();
	void Player1AttackCardSetting(class CAttackCard* card);
	bool UseFocus();

private:
	bool Player2UseAttackCard(class CAttackCard* card);
	bool Player2UseSpellCard(class CSpellCard* card);
	bool Player2UseBuildingCard(class CBuildingCard* card);
	bool ForWard();
	bool BackWard();
	bool Ora();
	bool Mana();
	bool Ital();
	bool UseAttackCard();
	bool UseSpellCard();
	bool UseBuildingCard();
	bool CheckCard(int Hero, int CardIndex, Card_Class cardclass, CCard* card);
	
	

	
	
};

