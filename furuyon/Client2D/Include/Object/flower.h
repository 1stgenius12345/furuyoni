#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/DistortionComponent.h"


class CFlower :
	public CGameObject
{
	friend class CScene;

protected:
	CFlower();
	CFlower(const CFlower& obj);
	virtual ~CFlower();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CMaterial>   m_SpriteMtrl;

	class CStartMapObj* m_StartMapObj;
	float execl;
public:
	void SetStartMapObj(class CStartMapObj* start)
	{
		m_StartMapObj = start;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CFlower* Clone();
	virtual void Animation2DNotify(const std::string& Name);


private:
	float gaussianRandom(void) {
		float v1, v2, s;

		do {
			v1 = 2 * ((float)rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
			v2 = 2 * ((float)rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
			s = v1 * v1 + v2 * v2;
		} while (s >= 1 || s == 0);

		s = sqrt((-2 * log(s)) / s);
		//
		return v1 * s;
		
	}
};

