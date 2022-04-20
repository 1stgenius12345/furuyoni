#include "AnimationCard.h"
#include "Input.h"
#include "Deck.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Resource/ResourceManager.h"
#include "Render/RenderManager.h"
#include "GameMapObj.h"



//bool CAnimationCard::m_MouseClick = false;

CAnimationCard::CAnimationCard() :
	m_CardIndex(0),
	m_HeroIndex(0),
	m_PlayerIndex(0),
	m_CardClass(Card_Class::Normal),
	m_Animationtriger(false),
	m_AnimationTimer(0.f),
	m_Axcel(0.f),
	m_AnimIndex(0),
	m_Settinghide(false),
	m_Settinghidestate(true)
	
{
	m_MissSoundCheck = false;
	m_DaeungSoundCheck = true;
}



CAnimationCard::CAnimationCard(const CAnimationCard& obj) :
	CGameObject(obj)
{

	
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	

}

CAnimationCard::~CAnimationCard()
{
}

void CAnimationCard::SetCardUnClick()
{


}

void CAnimationCard::SetCardClick()
{
	

}

void CAnimationCard::Start()
{
	//if (!m_bRender)
	//	return;
	CGameObject::Start();
}

bool CAnimationCard::Init()
{

	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_sakura = CreateSceneComponent<CSpriteComponent>("m_sakura");
	m_daeug = CreateSceneComponent<CSpriteComponent>("m_daeug");
	m_Card2 = CreateSceneComponent<CSpriteComponent>("m_Card2");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(640.f, 360.f, 0.f);
	m_Sprite->SetRelativeScale(744.f / 10.f / 5.f, 1038.f / 10.f / 5.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 1.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back);


	m_SpriteMtrl = m_Sprite->GetMaterial(0);
	m_SpriteMtrl->AddTexture("CardSample", TEXT("card/back.jpg"));
	m_SpriteMtrl->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_SpriteMtrl->SetEmissiveColor(1.5f, 1.f, 1.f, 1.f);
	m_SpriteMtrl->SetShader("Standard2DTextureShader");


	// »çÄí¶ó 
	m_Sprite->AddChild(m_sakura);
	m_sakura->SetRelativeScale(1280.f / 1.f / 5.f, 585.f / 1.f / 5.f, 0.f);
	m_sakura->SetWorldRotationZ(0.f);
	m_sakura->SetRelativePos(0.f, 0.f, 0.f);
	m_sakura->SetPivot(0.5f, 0.5f, 1.f);
	m_sakura->SetRender2DType(Render_Type_2D::RT2D_MAP);


	m_sakuraMtrl = m_sakura->GetMaterial(0);
	m_sakuraMtrl->AddTexture("º¢²É¹è°æ", TEXT("º¢²É¹è°æ.png"));
	m_sakuraMtrl->SetBaseColor(0.f, 0.f, 0.f, 0.f);
	m_sakuraMtrl->SetShader("Standard2DTextureShader");

	// ´ëÀÀ¹®ÀÚ 
	m_Sprite->AddChild(m_daeug);
	m_daeug->SetRelativeScale(316.f*1.1f,317.f * 1.1f,0.f);
	m_daeug->SetWorldRotationZ(0.f);
	m_daeug->SetRelativePos(0.f, 0.f, 0.f);
	m_daeug->SetPivot(0.5f, 0.5f, 1.f);
	m_daeug->SetRender2DType(Render_Type_2D::RT2D_Default);


	m_daeugMtrl = m_daeug->GetMaterial(0);
	m_daeugMtrl->AddTexture("´ëÀÀ¹®ÀÚ", TEXT("´ëÀÀ¹®ÀÚ.png"));
	m_daeugMtrl->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_daeugMtrl->SetShader("Standard2DTextureShader");


	// µÎ¹ø¤ŠÄ«µå
	m_Sprite->AddChild(m_Card2);
	m_Card2->SetRelativePos(0.f, -100.f, 0.f);
	m_Card2->SetRelativeScale(744.f, 1038.f,0.f);
	m_Card2->SetPivot(0.5f, 0.5f, 1.f);
	m_Card2->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_Card2Mtrl = m_Card2->GetMaterial(0);
	m_Card2Mtrl->SetOpacity(0.f);
	m_Card2Mtrl->AddTexture("CardSample", TEXT("card/back.jpg"));
	m_Card2Mtrl->SetEmissiveColor(1.f, 1.f, 1.f, 1.f);
	m_Card2Mtrl->SetShader("Standard2DTextureShader");








	// ÃÊ±âÈ­
	m_SpriteMtrl->SetOpacity(0.f);
	m_sakuraMtrl->SetOpacity(0.f);
	m_AnimationTimer = 0.f;
	m_Axcel = 10.f;
	m_daeugMtrl->SetOpacity(0.f);
	m_Card2Mtrl->SetOpacity(0.f);


	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAnimationCard::Update(float DeltaTime)
{
	
	

	bool mouseput =	CInput::GetInst()->GetMousePut();
	float ratio = m_Sprite->GetRelativeScale().y / m_Sprite->GetRelativeScale().x;
	float ratio2 = m_sakura->GetRelativeScale().y / m_sakura->GetRelativeScale().x;
	float ratio3 = m_daeug->GetRelativeScale().y / m_daeug->GetRelativeScale().x;
	if (m_Animationtriger)
	{
		// ¼û±â±â
	if (m_Settinghide)
	{
		if (m_Settinghidestate)
		{
			m_Card2Mtrl->SetOpacity(0.f);
			m_SpriteMtrl->SetOpacity(0.f);
			m_Settinghidestate = false;
		}
		else
		{
			if (m_PlayerIndex == 1 && !m_GameMapObj->GetPlayer1Win() && !m_GameMapObj->GetPlayer2Win())
			{
				//m_Card2Mtrl->SetOpacity(1.f);
			}
			
			m_SpriteMtrl->SetOpacity(1.f);
			m_Settinghidestate = true;
		}
		m_Settinghide = false;
	}


		m_Axcel += DeltaTime * m_Axcel;
		m_AnimationTimer += DeltaTime;
		if (m_AnimationTimer < 0.2f)
		{

			
			m_Sprite->AddRelativeScale(m_Axcel, m_Axcel * ratio, 0.f);
			m_sakura->AddRelativeScale(m_Axcel, m_Axcel * ratio2, 0.f);
		
			m_sakuraMtrl->AddBaseColor(m_Axcel * 0.005f, m_Axcel * 0.00375f, m_Axcel * 0.004f, DeltaTime * 100.f);
			
			
		}
		else if (m_AnimationTimer > 0.2f && m_AnimationTimer < 1.5f)
		{	
			if (m_MissSoundCheck)
			{
				m_GameMapObj->MissSound();
				m_MissSoundCheck = false;
			}
				
			m_Sprite->AddRelativeScale(10.f *DeltaTime, 10.f * DeltaTime * ratio, 0.f);
			m_sakura->AddRelativeScale(150.f * DeltaTime, 150.f * DeltaTime * ratio2, 0.f);
			m_sakuraMtrl->AddOpacity(-DeltaTime/5.f);
			m_sakura->AddWorldRotationZ(DeltaTime*10.f);
			m_sakuraMtrl->AddBaseColor(DeltaTime * 0.001f, DeltaTime * 0.001f, DeltaTime * 0.001f, DeltaTime * 0.f);
			m_Axcel = 10.f; 
		}
		else if (m_AnimationTimer > 1.5f && m_AnimationTimer < 1.6f)
		{	
			
			m_Axcel = 1.5f;
			if (m_GameMapObj->GetSelectTiming() && m_PlayerIndex ==2)
			{
				m_AnimationTimer -= DeltaTime;
				m_sakuraMtrl->SetOpacity(0.f);
				m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
				//m_Animationtriger = false;
				//m_SpriteMtrl->SetOpacity(0.f);
				//m_que_CardInfo.pop();
			}
			else if (m_AnimIndex == 0 && m_GameMapObj->GetSelectTiming())
			{
				m_AnimationTimer -= DeltaTime;
				m_sakuraMtrl->SetOpacity(0.f);
				m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);
				//m_Animationtriger = false;
				//m_SpriteMtrl->SetOpacity(0.f);
				//m_que_CardInfo.pop();
			}
			else if(m_GameMapObj->GetSelectTiming() && m_PlayerIndex == 1)
			{
				m_sakuraMtrl->SetOpacity(0.f);
			}
			
		}
		else if (m_AnimationTimer > 1.6f && m_AnimationTimer < 2.0f)
		{
			
			if (m_AnimIndex == 0)
			{
				m_daeugMtrl->SetOpacity(0.f);
				m_Card2Mtrl->SetOpacity(0.f);
				m_SpriteMtrl->SetOpacity(0.f);
				m_sakuraMtrl->SetOpacity(0.f);
				m_AnimIndex = 0;
				m_Animationtriger = false;
			}
			else
			{
				if (m_PlayerIndex == 2)
				{
					if (m_que_CardInfo.size() > 0 && m_AnimIndex == 1)
					{
						CardInfo tempinfo1 = m_que_CardInfo.front();

						m_CardClass = tempinfo1.CardClass;
						m_HeroIndex = tempinfo1.HeroIndex;
						m_CardIndex = tempinfo1.CardIndex;
						CreateTex2();
						if (tempinfo1.Player == 1)
							m_Card2Mtrl->SetBaseColor(1.2f, 1.f, 1.f, 1.f);
						else
							m_Card2Mtrl->SetBaseColor(1.f, 1.f, 1.2f, 1.f);
					
						m_que_CardInfo.pop();
					}
					m_PlayerIndex = 0;
				}
				m_Sprite->AddRelativeScale(-m_Axcel, -m_Axcel * ratio, 0.f);
				if (m_DaeungSoundCheck)
				{
					m_GameMapObj->DaeungSound();
					m_DaeungSoundCheck = false;
				}
			
				m_daeugMtrl->SetOpacity(1.f);
			}
			
			m_Axcel = 10.f;
		}
		else if (m_AnimationTimer> 2.0 && m_AnimationTimer <4.0f)
		{
			m_Card2Mtrl->SetOpacity(1.f);
	
			Vector3 startpoint = Vector3(0.f, 0.f, 0.f);
			startpoint = startpoint - m_Card2->GetRelativePos();
			if (startpoint.y > 0.f)
			{
				m_Card2->AddRelativeScale(-startpoint.y * DeltaTime* 7.f, -startpoint.y * DeltaTime * ratio * 7.f, 0.f);
				m_Card2->AddRelativePos(0.f, startpoint.y * DeltaTime * 10.f + 10.f * DeltaTime, 0.f);
			}
			//m_Card2->AddRelativeScale(-m_Axcel, -m_Axcel * ratio, 0.f);
		}
		else if (m_AnimationTimer > 4.0f)
		{	
			if (m_GameMapObj->GetSelectTiming() && m_PlayerIndex == 1)
			{
				
			}
			else
			{
				m_sakura->SetRelativeScale(1280.f / 1.f / 2.f, 585.f / 1.f / 2.f, 0.f);
				m_sakura->SetWorldRotationZ(0.f);
				m_sakuraMtrl->SetBaseColor(0.f, 0.f, 0.f, 0.f);
				m_Axcel = 10.f;
				m_sakuraMtrl->SetOpacity(0.f);
				m_daeugMtrl->SetOpacity(0.f);
				m_Card2Mtrl->SetOpacity(0.f);
				m_AnimationTimer = 0.f;
				m_AnimIndex = 0;
				m_PlayerIndex = 0;
				m_Sprite->SetRelativePos(640.f, 360.f, 0.f);
				m_Sprite->SetRelativeScale(744.f / 10.f / 1.3f, 1038.f / 10.f / 1.3f, 0.f);
			}
		}
	}
	else if (m_que_CardInfo.size() > 0)
	{
		m_GameMapObj->WhicSound();
		m_MissSoundCheck = false;
		m_DaeungSoundCheck = true;
		CardInfo tempinfo = m_que_CardInfo.front();
		if(tempinfo.Player == 1)
			m_SpriteMtrl->SetBaseColor(1.2f, 1.f, 1.f, 1.f);
		else
			m_SpriteMtrl->SetBaseColor(1.f, 1.f, 1.2f, 1.f);
		m_CardClass = tempinfo.CardClass;
		m_HeroIndex = tempinfo.HeroIndex;
		m_CardIndex = tempinfo.CardIndex;
		m_PlayerIndex = tempinfo.Player;
		m_AnimIndex = tempinfo.Daeug;
	//	m_AnimIndex = 0;
		CreateTex();
		m_que_CardInfo.pop();
		m_SpriteMtrl->SetOpacity(1.f);
		m_sakuraMtrl->SetOpacity(1.f);
		m_daeugMtrl->SetOpacity(0.f);
		m_Card2Mtrl->SetOpacity(0.f);
		m_Animationtriger = true;
		m_AnimationTimer = 0.f;
		m_Axcel = 10.f;
		m_sakuraMtrl->SetBaseColor(0.f, 0.f, 0.f, 0.f);
		m_Sprite->SetRelativePos(640.f, 360.f, 0.f);
		m_Sprite->SetRelativeScale(744.f / 10.f / 1.3f, 1038.f / 10.f / 1.3f, 0.f);
		m_sakura->SetRelativeScale(1280.f / 1.f / 2.f, 585.f / 1.f / 2.f, 0.f);
		m_sakura->SetWorldRotationZ(0.f);
		m_Card2->SetRelativeScale(744.f, 1038.f, 0.f);
		m_Card2->SetRelativePos(0.f, -600.f, 0.f);
		if (m_que_CardInfo.size() > 0 && m_AnimIndex == 1)
		{
			CardInfo tempinfo1 = m_que_CardInfo.front();

			m_CardClass = tempinfo1.CardClass;
			m_HeroIndex = tempinfo1.HeroIndex;
			m_CardIndex = tempinfo1.CardIndex;
			CreateTex2();
			if (tempinfo1.Player == 1)
				m_Card2Mtrl->SetBaseColor(1.2f, 1.f, 1.f, 1.f);
			else
				m_Card2Mtrl->SetBaseColor(1.f, 1.f, 1.2f, 1.f);
			m_que_CardInfo.pop();
		}
	}
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAnimationCard::PostUpdate(float DeltaTime)
{
	
	CGameObject::PostUpdate(DeltaTime);
}

void CAnimationCard::Collision(float DeltaTime)
{

	CGameObject::Collision(DeltaTime);
}

void CAnimationCard::Render(float DeltaTime)
{

	CGameObject::Render(DeltaTime);
}

CAnimationCard* CAnimationCard::Clone()
{
	return new CAnimationCard(*this);
}

void CAnimationCard::Animation2DNotify(const std::string& Name)
{

}

void CAnimationCard::CreateCardSetting()
{
}


void CAnimationCard::MoveUp(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CAnimationCard::MoveDown(float DeltaTime)
{
	AddRelativePos(GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CAnimationCard::RotationZ(float DeltaTime)
{
	AddRelativeRotationZ(360.f * DeltaTime);
}

void CAnimationCard::RotationZInv(float DeltaTime)
{
	AddRelativeRotationZ(-360.f * DeltaTime);
}

void CAnimationCard::Fire(float DeltaTime)
{

}

void CAnimationCard::Triple(float DeltaTime)
{

}

void CAnimationCard::Skill2(float DeltaTime)
{

}

void CAnimationCard::AnimationFrameEnd(const std::string& Name)
{

}

void CAnimationCard::CreatCard(int Cardindex, int Heroindex,Card_Class cardcalss)
{
	
	m_CardIndex = Cardindex;
	m_HeroIndex = Heroindex;
	m_CardClass = cardcalss;

	CreateTex();	
	m_Animationtriger = true;

}

void CAnimationCard::CreatCard2(int Cardindex, int Heroindex, Card_Class cardcalss)
{
	m_CardIndex = Cardindex;
	m_HeroIndex = Heroindex;
	m_CardClass = cardcalss;

	CreateTex2();
	m_Animationtriger = true;
}

void CAnimationCard::CreateTex()
{	
	if (m_HeroIndex == 0 && m_CardIndex == 0)
	{
		SetBack();
		return;
	}
	else if(m_HeroIndex == 0 && m_CardIndex == 1)
	{
		m_SpriteMtrl->AddTexture("ÀüÁø", TEXT("ÀüÁø.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 2)
	{
		m_SpriteMtrl->AddTexture("ÈÄÅð", TEXT("ÈÄÅð.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 3)
	{
		m_SpriteMtrl->AddTexture("ÈÖ°¨±â", TEXT("ÈÖ°¨±â.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 4)
	{
		m_SpriteMtrl->AddTexture("Ç°±â", TEXT("Ç°±â.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 5)
	{
		m_SpriteMtrl->AddTexture("ÀÌÅ»", TEXT("ÀÌÅ».png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 6)
	{
		m_MissSoundCheck = true;
		m_SpriteMtrl->AddTexture("½ÅÀÇÈ¸ÇÇ", TEXT("½ÅÀÇÈ¸ÇÇ.png"));
		return;
	}

	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_CardIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);

	if (m_CardClass == Card_Class::Normal)
		_tcsncat_s(tex, TEXT("Normal/"), 7);
	else
		_tcsncat_s(tex, TEXT("Hero/"), 5);

	TCHAR ds1[3] = { 0 };
	_stprintf_s(ds1, _countof(ds1), TEXT("%d"), m_HeroIndex);

	_tcsncat_s(tex, ds1, 1);
	_tcsncat_s(tex, TEXT("/"), 1);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_CardIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_SpriteMtrl->AddTexture(std_str, tex);
}

void CAnimationCard::CreateTex2()
{
	if (m_HeroIndex == 0 && m_CardIndex == 0)
	{
		SetBack();
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 1)
	{
		m_SpriteMtrl->AddTexture("ÀüÁø", TEXT("ÀüÁø.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 2)
	{
		m_SpriteMtrl->AddTexture("ÈÄÅð", TEXT("ÈÄÅð.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 3)
	{
		m_SpriteMtrl->AddTexture("ÈÖ°¨±â", TEXT("ÈÖ°¨±â.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 4)
	{
		m_SpriteMtrl->AddTexture("Ç°±â", TEXT("Ç°±â.png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 5)
	{
		m_SpriteMtrl->AddTexture("ÀÌÅ»", TEXT("ÀÌÅ».png"));
		return;
	}
	else if (m_HeroIndex == 0 && m_CardIndex == 6)
	{
		m_MissSoundCheck = true;
		m_SpriteMtrl->AddTexture("½ÅÀÇÈ¸ÇÇ", TEXT("½ÅÀÇÈ¸ÇÇ.png"));
		return;
	}

	TCHAR tex[20] = { 0 };

	TCHAR ds[3] = { 0 };
	_stprintf_s(ds, _countof(ds), TEXT("%d"), m_CardIndex);

	_tcsncat_s(tex, TEXT("card/"), 5);

	if (m_CardClass == Card_Class::Normal)
		_tcsncat_s(tex, TEXT("Normal/"), 7);
	else
		_tcsncat_s(tex, TEXT("Hero/"), 5);

	TCHAR ds1[3] = { 0 };
	_stprintf_s(ds1, _countof(ds1), TEXT("%d"), m_HeroIndex);

	_tcsncat_s(tex, ds1, 1);
	_tcsncat_s(tex, TEXT("/"), 1);

	TCHAR ds2[3] = { 0 };
	_stprintf_s(ds2, _countof(ds2), TEXT("%d"), m_CardIndex);

	_tcsncat_s(tex, ds2, 1);
	_tcsncat_s(tex, TEXT(".png"), 4);

	std::string std_str = TCHARToString(tex);

	m_Card2Mtrl->AddTexture(std_str, tex);
}

void CAnimationCard::SettingGone()
{
	SetRelativePos(0.f, 1000.f, 0.f);
}

void CAnimationCard::SettingHide()
{
	m_Settinghide = true;
}
