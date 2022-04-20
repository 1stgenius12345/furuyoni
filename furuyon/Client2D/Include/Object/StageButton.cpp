#include "StageButton.h"
#include "Input.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Resource/ResourceManager.h"
#include "Render/RenderManager.h"
#include "../SceneMode/GodSelectScene.h"
#include "../ClientManager.h"

#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"

CStageButton::CStageButton() 
	
{
	m_ButtonIndex = 0;
	m_Clear = false;
	m_Clearforline = true;
	m_testclear = false;
	m_testclear2 = false;
	m_faticlecount = 0;
	m_Mouseisit = false;
	m_Push = false;
	m_Down = false;
	m_Up = false;
}



CStageButton::CStageButton(const CStageButton& obj) :
	CGameObject(obj)
{
	


	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Rotation = FindSceneComponent("Rotation");
	m_Body = (CColliderBox2D*)FindSceneComponent("Body");




}

CStageButton::~CStageButton()
{
}


void CStageButton::Start()
{
	//if (!m_bRender)
	//	return;

	CExcel tempExcel;

	m_testclear = tempExcel.StageClearCheck(m_ButtonIndex, "stagecleardata.csv");
	m_testclear2 = m_testclear;

	CreatTex();








	CGameObject::Start();
}

bool CStageButton::Init()
{

	CGameObject::Init();

	m_Body = CreateSceneComponent<CColliderBox2D>("Body");
	m_Rotation = CreateSceneComponent<CSceneComponent>("Rotation");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(200.f,100.f,0.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 1.f);
	//m_Sprite->AddChild(m_PlayerInfoWidgetComponent);
	m_Body->SetExtent(100.f, 50.f);
	m_Body->SetCollisionProfile("PlayerAttack");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);
	m_Sprite->AddChild(m_Body);
	m_SpriteMtrl = m_Sprite->GetMaterial(0);
	m_SpriteMtrl->AddTexture("stage1", TEXT("stage/stage1.png"));




	m_SpriteMtrl->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.f);
	m_SpriteMtrl->SetShader("Standard2DTextureShader");
	m_Sprite->AddChild(m_Rotation);
	m_Rotation->SetPivot(0.5f, 0.5f, 0.f);




	m_PaperBurn = CreateObjectComponent<CPaperBurnComponent>("PaperBurn");

	m_PaperBurn->SetTargetMaterial(m_Sprite->GetMaterial(0));
	m_PaperBurn->SetBurnTime(1.0f);

	/*m_PaperBurn->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
	m_PaperBurn->SetCenterLineColor(255, 69, 0);
	m_PaperBurn->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);*/

	m_PaperBurn->SetEndFunction<CStageButton>(this, &CStageButton::PaperBurnEndFunction);



	





	m_Body->AddCollisionMouseCallbackFunction<CStageButton>(Collision_State::Begin, this,
		&CStageButton::CollisionBeginMouse);
	m_Body->AddCollisionMouseCallbackFunction<CStageButton>(Collision_State::End, this,
		&CStageButton::CollisionEndMouse);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStageButton::Update(float DeltaTime)
{

	/*if (!m_bRender)
	{
		m_SpriteMtrl->SetOpacity(0.f);
		m_Sprite->SetRelativePos(0.f,-500.f, 0.f);
		m_StartHandPos = Vector3(0.f, -500.f, 0.f);
		m_Sprite->AddChild(m_Body);
	}
	else
	{
		m_SpriteMtrl->SetOpacity(1.f);
	}
	*/
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		if (!m_Down && !m_Push)
			m_Down = true;

		else if (!m_Push)
		{
			m_Down = false;
			m_Push = true;
		}
	}

	else if (m_Push || m_Down)
	{
		m_Up = true;
		m_Push = false;
		m_Down = false;
	}

	else if (m_Up)
		m_Up = false;

	CGameObject::Update(DeltaTime);
	bool MouseLeftState = CInput::GetInst()->GetMouseLeftState();
	bool MouseRightState = CInput::GetInst()->GetMouseRightState();
	bool MouseRightPut = CInput::GetInst()->GetMouseRightPut();
	bool MousePut = CInput::GetInst()->GetMousePut();
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;


	if (m_Mouseisit && m_Down)
	{
		m_pScene->GetResource()->SoundPlay("Mana");
		CClientManager::GetInst()->SetAiindex(m_ButtonIndex);
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->SetSceneMode<CGodSelectScene>(false);
	}


	if (m_Clearforline && m_testclear)
	{
		m_pParticle = m_pScene->SpawnObject<CFlameEffect>("FlameEffect");
		m_pScene->GetResource()->SoundPlay("Building");
		CParticleSystemComponent* ParticleCom = (CParticleSystemComponent*)m_pParticle->FindSceneComponent("Particle");
		m_Sprite->AddChild(ParticleCom);
		m_pParticle->SetFrontButton(this);
		if (m_ButtonIndex % 5 == 0)
		{
			m_pParticle->AddRelativePos(0.f, 55.f, 0.f);
			m_pParticle->SetDir(2);
		}
		else
		{
			if ((m_ButtonIndex / 5) % 2 == 0)
			{
				m_pParticle->AddRelativePos(105.f, 0.f, 0.f);
				m_pParticle->SetDir(1);
			}
			else
			{
				m_pParticle->AddRelativePos(-105.f, 0.f, 0.f);
				m_pParticle->SetDir(3);
			}
			
		}
		
		m_Clearforline = false;
		m_testclear = false;
	}


	if (m_Clear && m_testclear2)
	{
		
		CStageButton* pStageButton = m_pScene->SpawnObject<CStageButton>("stageButton");
		if (m_ButtonIndex % 5 == 0)
		{
			pStageButton->SetRelativePos(GetRelativePos().x, GetRelativePos().y + 200.f, 0.f);
		}
		else
		{
			if ((m_ButtonIndex / 5) % 2 == 0)
			{
				pStageButton->SetRelativePos(GetRelativePos().x + 300.f, GetRelativePos().y, 0.f);
			}
			else
			{
				
				pStageButton->SetRelativePos(GetRelativePos().x - 300.f, GetRelativePos().y, 0.f);
			}
			
		}
		
		pStageButton->SetButtonIndex(m_ButtonIndex + 1);
		m_testclear2 = false;
		m_Clear = false;
	}

	
	

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CStageButton::PostUpdate(float DeltaTime)
{

	CGameObject::PostUpdate(DeltaTime);
}

void CStageButton::Collision(float DeltaTime)
{

	CGameObject::Collision(DeltaTime);
}

void CStageButton::Render(float DeltaTime)
{


	CGameObject::Render(DeltaTime);
}

CStageButton* CStageButton::Clone()
{
	return new CStageButton(*this);
}

void CStageButton::Animation2DNotify(const std::string& Name)
{

}

void CStageButton::CollisionBeginMouse(const Vector2& result, CCollider* Collider)
{
	m_Mouseisit = true;

	m_SpriteMtrl->AddTexture("stage0", TEXT("stage/stage0.png"));
	m_PaperBurn->StartPaperBurn();
	
}

void CStageButton::CollisionEndMouse(const Vector2& result, CCollider* Collider)
{
	m_Mouseisit = false;
	CreatTex();
	m_PaperBurn->REPaperBurn();
}

void CStageButton::PaperBurnEndFunction()
{
	
	
}

void CStageButton::CheckClear()
{




}

void CStageButton::CreatTex()
{
	TCHAR tex[20] = { 0 };
	if (m_ButtonIndex >= 7)
	{
		m_SpriteMtrl->AddTexture("stagemiss", TEXT("stage/miss.png"));
		return;
	}

	_tcsncat_s(tex, TEXT("stage/"), 6);


	_tcsncat_s(tex, TEXT("stage"), 5);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_ButtonIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_SpriteMtrl->AddTexture(std_str, tex);

}
