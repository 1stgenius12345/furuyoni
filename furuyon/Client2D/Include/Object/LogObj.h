#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/WidgetComponent.h"
#include "Card.h"
#include "Deck.h"
#include "../UI/PlayerLogHUDWidget.h"

class CLogObj :
	public CGameObject
{
	friend class CScene;

protected:
	CLogObj();
	CLogObj(const CLogObj& obj);
	virtual ~CLogObj();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpriteComponent> m_GameMapBackGround;
	CSharedPtr<CMaterial>   m_SpriteMtrl2;
	
	CSharedPtr<CWidgetComponent> m_LogWidgetComponent;
	CPlayerLogHUDWidget* m_LogWidget;

	std::vector<CSharedPtr<CWidgetComponent>> m_vec_LogWidgetComponet;


	class CDeck* m_Deck;
	bool m_Look;
	float m_Excel;

protected:


public:
	
	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CLogObj* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	

public:
	void CreateLog(class CCard* card, class CCard* card2, int index, int player);
};

