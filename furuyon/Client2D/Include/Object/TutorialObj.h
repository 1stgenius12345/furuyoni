#pragma once
#include "GameObject.h"
#include "../UI/TutorialWidget.h"
#include "Component/SpriteComponent.h"
#include "../SceneMode/StartScene.h"

class CTutorialObj :
    public CGameObject
{
    friend class CScene;

protected:
    CTutorialObj();
    CTutorialObj(const CTutorialObj& obj);
    virtual ~CTutorialObj();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CMaterial>   m_SpriteMtrl;

    CSharedPtr<CWidgetComponent> m_TutorialWidgetComponent;
    class CTutorialWidget* m_TutorialWidget;



    int m_index;

public:
    void AddIndex(int i)
    {   
        if (m_index == 1 && i <= 0)
            return;
        if (m_index == 21 && i >= 0)
        {
            Go();
            return;
        }
           
        m_index += i;
        CreateTex();
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CTutorialObj* Clone();

public:

    void CreateTex();
    void Go();
};

