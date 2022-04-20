#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "SceneMode/MainScene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "UI/MouseWidget.h"
#include "Resource/ResourceManager.h"
#include "SceneMode/StartScene.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
    Aiindex = 0;
}

CClientManager::~CClientManager()
{
   
}

bool CClientManager::Init()
{
 
  
    CResourceManager::GetInst()->LoadSound("BGM", true, "IntroSound", "introsound.wav");
    CResourceManager::GetInst()->LoadSound("BGM", true, "fightbgm", "fightbgm.wav");
    CResourceManager::GetInst()->LoadSound("BGM", true, "selectbgm", "selectbgm.wav");
    CResourceManager::GetInst()->LoadSound("Voice", false, "titlesound", "titlesound.wav");
    CResourceManager::GetInst()->LoadSound("Voice", false, "yurinaselect", "yurinaselect.mp3");
    CResourceManager::GetInst()->LoadSound("Voice", false, "saineselect", "saineselect.mp3");
    CResourceManager::GetInst()->LoadSound("Voice", false, "tokoyoselect", "tokoyoselect.mp3");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Click", "Click.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Mana", "effect/Mana.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Ora", "effect/Ora.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "BackWard", "effect/BackWard.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "FrontWard", "effect/FrontWard.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Spell", "effect/Spell.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Building", "effect/Building.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "defeat", "effect/defeat.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "victory", "effect/victory.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "TurnEnd", "effect/TurnEnd.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "TurnStart", "effect/TurnStart.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "CardtoUse", "effect/CardtoUse.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "daeungsound", "effect/daeungsound.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "hide", "effect/hide.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "miss", "effect/miss.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "refresh", "effect/refresh.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "widget", "effect/widget.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "draw", "effect/draw.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "Oraattacksound", "effect/Oraattacksound.wav");
    CResourceManager::GetInst()->LoadSound("Effect", false, "whic", "effect/whic.mp3");
    CResourceManager::GetInst()->LoadSound("Effect", false, "cardclick", "effect/cardclick.wav");

    CResourceManager::GetInst()->SetVolume("BGM", 60.f);
    //CEngine::GetInst()->OnDebugLog();
    //CEngine::GetInst()->OnLogFPS(true);

    // 키 등록
    CInput::GetInst()->CreateKey("MoveUp", 'W');
    CInput::GetInst()->CreateKey("MoveDown", 'S');
    CInput::GetInst()->CreateKey("MoveLeft", 'A');
    CInput::GetInst()->CreateKey("MoveRight", 'D');
    CInput::GetInst()->CreateKey("Fire", VK_SPACE);
    CInput::GetInst()->CreateKey("Skill1", '1');
    CInput::GetInst()->CreateKey("Skill2", '2');
    CInput::GetInst()->CreateKey("Skill3", '3');
    CInput::GetInst()->CreateKey("Skill4", '4');
    CInput::GetInst()->CreateKey("Skill5", '5');

    CInput::GetInst()->CreateKey("esc", VK_ESCAPE);
   // CInput::GetInst()->SetControlKey("Skill2", true);

    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", Collision_Interaction::Block);

    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", Collision_Channel::Custom1);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", Collision_Channel::Custom2);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Custom1,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::Custom1,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::Custom1,
        Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("Monster", Collision_Channel::Custom2,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::Custom2,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::Custom2,
        Collision_Interaction::Ignore);

    CSceneManager::GetInst()->SetSceneMode<CStartScene>();

    CreateMouse();

    return true;
}

void CClientManager::CreateMouse()
{
    // 마우스 애니메이션 시퀀스 생성
    CResourceManager::GetInst()->CreateAnimationSequence2D("MouseDefault");

    std::vector<const TCHAR*> vecFileName;

    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));
    vecFileName.push_back(TEXT("Mouse/Default/13.png"));

    CResourceManager::GetInst()->SetAnimationSequence2DTexture("MouseDefault",
        "MouseDefault", vecFileName);

    CResourceManager::GetInst()->AddAnimationSequence2DFrame("MouseDefault",
        Vector2(0.f, 0.f), Vector2(41.f, 48.f), 13);

    CMouseWidget* Mouse = CEngine::GetInst()->CreateMouseWidget<CMouseWidget>("Mouse");

    Mouse->SetSize(41.f, 48.f);

    Mouse->CreateAnimation2D<CAnimation2D>();

    CAnimation2D* MouseAnim = Mouse->GetAnimation2D();

    MouseAnim->AddAnimationSequence2D("MouseDefault");
}
