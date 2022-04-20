#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "Component/PaperBurnComponent.h"
#include "FlameEffect.h"
#include "StageObj.h"
#include "Excel.h"
//#include "../UI/SelectHUDWidget.h"




class CStageButton :
	public CGameObject
{
	friend class CScene;
	friend class CDeck;

public:
	CStageButton();
	CStageButton(const CStageButton& obj);
	virtual ~CStageButton();

protected:


	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CMaterial>   m_SpriteMtrl;
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CPaperBurnComponent> m_PaperBurn;

	CSharedPtr<CColliderBox2D> m_Body;
	
	class CFlameEffect* m_pParticle;
	class CStageObj* m_StageObj;

	int m_ButtonIndex;
	
	bool m_Clear;
	bool m_Clearforline;
	bool m_testclear;
	bool m_testclear2;
	int m_faticlecount;
	bool m_Mouseisit;
	bool m_Push;
	bool m_Down;
	bool m_Up;
protected:

public:
	void SetButtonIndex(int i)
	{
		m_ButtonIndex = i;
	}
	void SetClaer(bool cl)
	{
	
		m_Clear = true;
	
	
	}
	void SetStageObj(class CStageObj* stage)
	{
		m_StageObj = stage;
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
public:
	//static bool m_MouseClick;
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStageButton* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void CollisionBeginMouse(const Vector2& result, CCollider* Collider);
	void CollisionEndMouse(const Vector2& result, CCollider* Collider);
	void PaperBurnEndFunction();
	void CheckClear();
	void CreatTex();
};

