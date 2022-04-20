#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

class CStageObj :
    public CGameObject
{
    friend class CScene;

protected:
    CStageObj();
    CStageObj(const CStageObj& obj);
    virtual ~CStageObj();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CMaterial>   m_SpriteMtrl;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CMaterial>   m_SpriteMtrl2;
    CSharedPtr<CSpriteComponent> m_Sprite3;
    CSharedPtr<CMaterial>   m_SpriteMtrl3;





    bool m_Start2;
    float m_BlurCount;

public:
    void SetStart2(bool b)
    {
        m_Start2 = b;
    }
    bool GetStart2() const
    {
        return m_Start2;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CStageObj* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
    void SetBackGround();
    void MoveUp(float DeltaTime);
    void CreateButton();
};

