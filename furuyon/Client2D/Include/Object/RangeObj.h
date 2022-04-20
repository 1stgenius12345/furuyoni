#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/DistortionComponent.h"


class CRangeObj :
	public CGameObject
{
	friend class CScene;

protected:
	CRangeObj();
	CRangeObj(const CRangeObj& obj);
	virtual ~CRangeObj();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CMaterial>   m_SpriteMtrl;

	int m_index;
	bool m_front;
	bool m_back;

public:
	
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CRangeObj* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void Settingindex(int i);
	void RangeUp();
	void RangeDown();
private:
	float SettingPos(int index);
	
};

