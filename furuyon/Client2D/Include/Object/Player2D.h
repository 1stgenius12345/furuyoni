#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"
#include "../UI/StageHUDWidget.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& obj);
	virtual ~CPlayer2D();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSceneComponent> m_Rotation;
	CSharedPtr<CSceneComponent> m_Muzzle;
	CSharedPtr<CSpringArm2D> m_Arm;
	CSharedPtr<CCamera> m_Camera;
	CSharedPtr<CColliderBox2D> m_Body;


	// Widget
	CSharedPtr<CWidgetComponent> m_StageWidgetComponent;
	CStageHUDWidget* m_StageWidget;

	float m_Excely;
	float m_Excelx;

protected:
	bool    m_ChildFire;
	float   m_ChildFireTime;
	float   m_ChildFireTimeMax;
	float   m_ChildFireDurationTime;
	float   m_ChildFireDurationTimeMax;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayer2D* Clone();
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
};

