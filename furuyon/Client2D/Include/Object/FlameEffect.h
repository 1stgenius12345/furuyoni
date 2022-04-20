#pragma once

#include "GameObject.h"
#include "Component/ParticleSystemComponent.h"
#include "Component/DistortionComponent.h"
#include "StageButton.h"
class CFlameEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CFlameEffect();
	CFlameEffect(const CFlameEffect& obj);
	virtual ~CFlameEffect();

protected:
	CSharedPtr<CParticleSystemComponent> m_Particle;
	CSharedPtr<CDistortionComponent>	m_Distortion;
	bool m_End;
	class CStageButton* m_FrontButton;
	class CStageButton* m_BackButton;
	static bool m_staticEnd;
	Vector3 m_TempEndpos;

	int m_Dir;

public:
	void SetDir(int i)
	{
		m_Dir = i;
	}
	void SetBackButton(class CStageButton* button)
	{
		m_BackButton = button;
	}
	void SetFrontButton(class CStageButton* button)
	{
		m_FrontButton = button;
	}
	bool GetEnd() const
	{
		return m_End;
	}
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CFlameEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

