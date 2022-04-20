
#include "GameMapObj.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

#include "Device.h"
#include "Input.h"
#include "AttackCard.h"
#include "BuildingCard.h"
#include "SpellCard.h"
#include "AnimationCard.h"
#include "LogObj.h"
#include "Excel.h"
CGameMapObj::CGameMapObj() :
	m_LogObj(nullptr),
	m_Range(10),
	m_Dust(0),
	m_Player1_Life(10),
	m_Player1_Shiled(3),
	m_Player1_Mana(0),
	m_Player1_focus(0),
	m_Player1_Deck(nullptr),
	m_Player2_Life(10),
	m_Player2_Shiled(3),
	m_Player2_Mana(0),
	m_Player2_focus(0),
	m_Player2_Deck(nullptr),
	m_Backtriger(false),
	m_SceneCard(nullptr),
	m_Card5Tick(0),
	m_FocusWidget(nullptr),
	m_GaeSiPhaseWidget(nullptr),
	m_HeroWidget(nullptr),
	m_GameMapWidget(nullptr),
	m_Hero2Widget(nullptr),
	m_PhaseWidget(nullptr),
	m_MuligunWidget(nullptr),
	m_CardUseWidget(nullptr),
	m_SelectTiming(false),
	m_FocusTriger(false),
	m_UseTriger(false),
	m_defaulttimer(0.f),
	m_turn(0),
	m_Player1Gaesi(0),
	m_Player1GaesiEnd(false),
	m_Player1Main(0),
	m_Player1MainEnd(false),
	m_Player1End(0),
	m_Player1EndEnd(false),
	m_Player2Gaesi(0),
	m_Player2GaesiEnd(false),
	m_Player2Main(0),
	m_Player2MainEnd(false),
	m_Player2End(0),
	m_Player2EndEnd(false),
	m_Muligun(false),
	m_MuligunEnd(false),
	m_TenreokuCheck(0),
	m_TenreokuCheckPlayer2(0),
	m_buff_Range_Min(0),
	m_buff_Don_Daeug(0),
	m_buff_Shiled_Attack(0),
	m_buff_Life_Attack(0),
	m_chogeok(0),
	m_Hero1_Card4_Normal(0),
	m_Hero1_Card4_Normal_Player2(0),
	m_Hero1_Card6_Normal(0),
	m_Hero1_Card6_Normal_Player2(false),
	m_Hero1_Card2_Hero(true),
	m_Hero1_Card2_Hero_Player2(true),
	m_Hero3_Card4_Normal(false),
	m_Hero3_Card4_Normal_Player2(false),
	m_Hero3_Card6_Normal(false),
	m_Hero3_Card6_Normal_Player2(false),
	m_Hero3_Card6_Normal_UITriger(0),
	m_TestDelayTime(0.f),
	m_Player1_win(false),
	m_player2_win(false),
	m_player1_teum(false),
	m_player2_teum(false),
	m_player1_Attackselect(false),
	m_player1_AttackselectEnd(false),
	m_Player1_AttackSelectResult(false),
	m_AnimationCard(nullptr),
	m_player1_AttackSelectShiledtemp(0),
	m_player1_AttackSelectLifetemp(0),
	m_player1_DauegSelect(false),
	m_DALIN_Range(2),
	m_Player1_Select_USEANDBACK(false),
	m_LogLook(false),
	m_player1use(false),
	m_player1back(false),
	m_Ai1use(false),
	m_Ai1back(false),
	m_usebackwidgetcheck(false),
	m_Player1Press(false),
	m_AiPress(false),
	m_WhoFirst(0)
{
	m_bozoCard = new CAttackCard;
	m_bozoCard1 = new CAttackCard;
	m_bozoCard2 = new CAttackCard;
	m_Ai = new CPlayer2Ai;
	m_Ai->SetGameMapObj(this);
	m_Down = false;
	m_Up = false;
	m_Push = false;
}

CGameMapObj::CGameMapObj(const CGameMapObj& obj) :
	CGameObject(obj)
{
	
}

CGameMapObj::~CGameMapObj()
{
	SAFE_DELETE(m_bozoCard);
	SAFE_DELETE(m_bozoCard1);
	SAFE_DELETE(m_bozoCard2);
	SAFE_DELETE(m_Ai);
}

void CGameMapObj::PushAnimationCard2(int Hero, int card, Card_Class cardclass)
{
	m_AnimationCard->PushCardInfo(Hero, card, cardclass,1,0);
}

void CGameMapObj::PushAnimationCard(CCard* card,int daeug)
{
	if (card->GetCardType() == Card_Type::Spell)
		m_pScene->GetResource()->SoundPlay("Spell");
	else if(card->GetCardType() == Card_Type::Building)
		m_pScene->GetResource()->SoundPlay("Building");
	m_AnimationCard->PushCardInfo(card->GetHeroIndex(), card->GetCardIndex(), card->GetCardClass(),card->GetPlayer(),daeug);
}

void CGameMapObj::StartGameHandSetting()
{
	srand(GetTickCount());

	int Arr[7] = {};
	for (int i = 0; i < 7; ++i)
	{
		Arr[i] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		int S1 = rand() % 7;
		int S2 = rand() % 7;

		int temp = Arr[S1];
		Arr[S1] = Arr[S2];
		Arr[S2] = temp;
	}

	SetPlayer1handCard(m_Player1_Deck->GetNormalCardByindex(Arr[0]));
	SetPlayer1handCard(m_Player1_Deck->GetNormalCardByindex(Arr[1]));
	SetPlayer1handCard(m_Player1_Deck->GetNormalCardByindex(Arr[2]));
	SetPlayer1DeckCard(m_Player1_Deck->GetNormalCardByindex(Arr[3]));
	SetPlayer1DeckCard(m_Player1_Deck->GetNormalCardByindex(Arr[4]));
	SetPlayer1DeckCard(m_Player1_Deck->GetNormalCardByindex(Arr[5]));
	SetPlayer1DeckCard(m_Player1_Deck->GetNormalCardByindex(Arr[6]));
	SetPlayer1HeroCard(m_Player1_Deck->GetHeroCardByindex(0));
	SetPlayer1HeroCard(m_Player1_Deck->GetHeroCardByindex(1));
	SetPlayer1HeroCard(m_Player1_Deck->GetHeroCardByindex(2));
	m_Player1_Deck->SettingGone();
	for (int i = 0 ;i < m_vecPlayer1_Deck.size(); i++)
	{
		m_vecPlayer1_Deck[i]->SetPlayer(1);
		m_vecPlayer1_Deck[i]->SettingGone();
	}
	for (int i = 0; i < m_vecPlayer1_Hand.size(); i++)
	{
		m_vecPlayer1_Hand[i]->SetPlayer(1);
	}
	for (int i = 0; i < m_vecPlayer1_Hero.size(); i++)
	{
		m_vecPlayer1_Hero[i]->SetPlayer(1);
	}

	for (int i = 0; i < 10; i++)
	{
		int S1 = rand() % 7;
		int S2 = rand() % 7;

		int temp = Arr[S1];
		Arr[S1] = Arr[S2];
		Arr[S2] = temp;
	}
	SetPlayer2handCard(m_Player2_Deck->GetNormalCardByindex(Arr[0]));
	SetPlayer2handCard(m_Player2_Deck->GetNormalCardByindex(Arr[1]));
	SetPlayer2handCard(m_Player2_Deck->GetNormalCardByindex(Arr[2]));
	SetPlayer2DeckCard(m_Player2_Deck->GetNormalCardByindex(Arr[3]));
	SetPlayer2DeckCard(m_Player2_Deck->GetNormalCardByindex(Arr[4]));
	SetPlayer2DeckCard(m_Player2_Deck->GetNormalCardByindex(Arr[5]));
	SetPlayer2DeckCard(m_Player2_Deck->GetNormalCardByindex(Arr[6]));
	SetPlayer2HeroCard(m_Player2_Deck->GetHeroCardByindex(0));
	SetPlayer2HeroCard(m_Player2_Deck->GetHeroCardByindex(1));
	SetPlayer2HeroCard(m_Player2_Deck->GetHeroCardByindex(2));
	m_Player2_Deck->SettingGone();
	for (int i = 0; i < m_vecPlayer2_Deck.size(); i++)
	{
		m_vecPlayer2_Deck[i]->SetPlayer(2);
		m_vecPlayer2_Deck[i]->SetBack();
		m_vecPlayer2_Deck[i]->SettingGone();
	}
	
	for (int i = 0; i < m_vecPlayer2_Hand.size(); i++)
	{
		m_vecPlayer2_Hand[i]->SetPlayer(2);
		m_vecPlayer2_Hand[i]->SetBack();
	}
	for (int i = 0; i < m_vecPlayer2_Hero.size(); i++)
	{
		m_vecPlayer2_Hero[i]->SetPlayer(2);
		m_vecPlayer2_Hero[i]->SetBack();
	}


	HandSortSetting();
}

void CGameMapObj::HandSortSetting()
{
	size_t size = m_vecPlayer1_Hand.size();

	
	for (int i = 0; i < size; ++i)
	{
		m_vecPlayer1_Hand[i]->SetRelativePos(709.4f - (72.1f * size)+ 744.f / 4.f / 1.3f * i + 10.f, 19.f, 0.f);
		m_vecPlayer1_Hand[i]->SetStartHandPos(m_vecPlayer1_Hand[i]->GetRelativePos());
		m_vecPlayer1_Hand[i]->SetMove(false);
		m_vecPlayer1_Hand[i]->SetSelectTime(false);
		m_vecPlayer1_Hand[i]->SetUse(false);
		m_vecPlayer1_Hand[i]->SetSelect(false);
		m_vecPlayer1_Hand[i]->UnSellectTextureSetting();
		
	}

	size_t size2 = m_vecPlayer2_Hand.size();

	for (int i = 0; i < size2; ++i)
	{
		m_vecPlayer2_Hand[i]->SetRelativePos(709.4f - (72.1f * size2)+ 744.f / 4.f / 1.3f * i + 10.f, 781.f, 0.f);
		m_vecPlayer2_Hand[i]->SetStartHandPos(m_vecPlayer2_Hand[i]->GetRelativePos());
		m_vecPlayer2_Hand[i]->SetMove(false);
		m_vecPlayer2_Hand[i]->SetUse(false);
		m_vecPlayer2_Hand[i]->SetSelectTime(false);
		m_vecPlayer2_Hand[i]->SetSelect(false);
		m_vecPlayer2_Hand[i]->UnSellectTextureSetting();
		
	}
	HeroDeckSorting();
}

void CGameMapObj::Start()
{
	if (CClientManager::GetInst()->GetAiIndex() > 0)
	{
		CExcel tempExcel;

		tempExcel.StageSetting(CClientManager::GetInst()->GetAiIndex(), m_Range, m_Dust, m_Player1_Life, m_Player1_Shiled, m_Player1_Mana, m_Player1_focus, m_Player2_Life, m_Player2_Shiled, m_Player2_Mana, m_Player2_focus ,"mapdata.csv");
	}










	for (int i = 0; i < m_vecRange.size(); ++i)
	{
		for (int j = 0; j < 10 - m_Range; ++j)
		{
			m_vecRange[i]->RangeDown();
		}
	}




	CGameObject::Start();
}

bool CGameMapObj::Init()
{
	CGameObject::Init();

	/////////
	// 
	m_LogObj = m_pScene->SpawnObject<CLogObj>("m_LogObj");
	/////////////
	// 스폰

	m_AnimationCard = m_pScene->SpawnObject<CAnimationCard>("AnimationCard");
	m_AnimationCard->SetGameMapObj(this);


	CRangeObj* pRangeObj1 = m_pScene->SpawnObject<CRangeObj>("pRangeObj1");
	CRangeObj* pRangeObj2 = m_pScene->SpawnObject<CRangeObj>("pRangeObj2");
	CRangeObj* pRangeObj3 = m_pScene->SpawnObject<CRangeObj>("pRangeObj3");
	CRangeObj* pRangeObj4 = m_pScene->SpawnObject<CRangeObj>("pRangeObj4");
	CRangeObj* pRangeObj5 = m_pScene->SpawnObject<CRangeObj>("pRangeObj5");
	CRangeObj* pRangeObj6 = m_pScene->SpawnObject<CRangeObj>("pRangeObj6");
	CRangeObj* pRangeObj7 = m_pScene->SpawnObject<CRangeObj>("pRangeObj7");
	CRangeObj* pRangeObj8 = m_pScene->SpawnObject<CRangeObj>("pRangeObj8");
	CRangeObj* pRangeObj9 = m_pScene->SpawnObject<CRangeObj>("pRangeObj9");
	CRangeObj* pRangeObj10 = m_pScene->SpawnObject<CRangeObj>("pRangeObj10");
	pRangeObj1	 ->	 Settingindex(1);
	pRangeObj2	 ->	 Settingindex(2);
	pRangeObj3	 ->	 Settingindex(3);
	pRangeObj4	 ->	 Settingindex(4);
	pRangeObj5	 ->	 Settingindex(5);
	pRangeObj6	 ->	 Settingindex(6);
	pRangeObj7	 ->	 Settingindex(7);
	pRangeObj8	 ->	 Settingindex(8);
	pRangeObj9	 ->	 Settingindex(9);
	pRangeObj10	 ->	 Settingindex(10);
	m_vecRange.push_back(pRangeObj1);
	m_vecRange.push_back(pRangeObj2);
	m_vecRange.push_back(pRangeObj3);
	m_vecRange.push_back(pRangeObj4);
	m_vecRange.push_back(pRangeObj5);
	m_vecRange.push_back(pRangeObj6);
	m_vecRange.push_back(pRangeObj7);
	m_vecRange.push_back(pRangeObj8);
	m_vecRange.push_back(pRangeObj9);
	m_vecRange.push_back(pRangeObj10);
	/////////////////
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_GameMapBackGround = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_HeroDeckBackGround = CreateSceneComponent<CSpriteComponent>("m_HeroDeckBackGround");
	m_Hero2DeckBackGround = CreateSceneComponent<CSpriteComponent>("m_Hero2DeckBackGround");
	m_AlphaBlack = CreateSceneComponent<CSpriteComponent>("m_AlphaBlack");
	m_Cardlist = CreateSceneComponent<CSpriteComponent>("m_Cardlist");
	m_FocusWidgetComponent = CreateSceneComponent<CWidgetComponent>("FocusWidgetComponent");
	m_GaeSiPhaseWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_GaeSiPhaseWidgetComponent");
	m_HeroWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_HeroWidgetComponent");
	m_GameMapWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_GameMapWidgetComponent");
	m_Hero2WidgetComponent = CreateSceneComponent<CWidgetComponent>("m_Hero2WidgetComponent");
	m_PhaseWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_PhaseWidgetComponent");
	m_MuligunWidgetComponent= CreateSceneComponent<CWidgetComponent>("m_MuligunWidgetComponent");
	m_CardUseWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_CardUseWidgetComponent");
	m_BackWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_BackWidgetComponent");

	//m_GameMapAnimationComponent = CreateSceneComponent<CWidgetComponent>("m_GameMapAnimationComponent");
	//	m_BackCard = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(0.f, 0.f, 1.f);
	m_Sprite->SetRelativePos(15.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	


	
	m_vecPlayer1_focus_Collider	   = CreateSceneComponent<CColliderBox2D>("focus");



	m_Sprite->AddChild(m_vecPlayer1_focus_Collider);

	//m_Sprite->AddChild(m_BackCard);
	m_Sprite->AddChild(m_GameMapBackGround);
	m_Sprite->AddChild(m_HeroDeckBackGround);
	m_Sprite->AddChild(m_Hero2DeckBackGround);
	m_Sprite->AddChild(m_AlphaBlack);
	m_Sprite->AddChild(m_Cardlist);

	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;




	
	m_vecPlayer1_focus_Collider	 ->AddRelativePos(Center.x + 540.f, Center.y - 90.f, 0.f);
	
	
	m_vecPlayer1_focus_Collider	 ->SetExtent(60.f, 50.f);
	

	m_vecPlayer1_focus_Collider		->SetCollisionProfile("Monster");

	//// 덮음패 
	//m_BackCard->SetRelativeScale(744.f / 4.f / 1.3f, 1038.f / 4.f / 1.3f,0.f);
	//m_BackCard->SetPivot(0.5f, 0.5f, 0.5f);
	//m_BackCard->AddRelativeRotationZ(90.f);
	//m_BackCard->SetRelativePos(Center.x + 275.f, Center.y - 150.f, 0.f);
	//m_SpriteMtrl = m_BackCard->GetMaterial(0);
	//m_SpriteMtrl->AddTexture("backempty", TEXT("card/backempty.jpg"));
	//m_SpriteMtrl->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.f);
	//m_SpriteMtrl->SetShader("Standard2DTextureShader");

	// 게임맵
	m_GameMapBackGround->SetRelativeScale(1280.f, 720.f, 0.f);
	m_GameMapBackGround->SetPivot(0.5f, 0.5f, 0.5f);
	m_GameMapBackGround->SetRender2DType(Render_Type_2D::RT2D_BACKMAP);
	m_GameMapBackGround->SetRelativePos(Center.x - 15.f, Center.y , 0.f);
	m_SpriteMtrl2 = m_GameMapBackGround->GetMaterial(0);
	m_SpriteMtrl2->AddTexture("GameBackGround", TEXT("GameBackGround.png"));
	m_SpriteMtrl2->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_SpriteMtrl2->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.f);
	m_SpriteMtrl2->SetShader("Standard2DTextureShader");

	// 비장패 배경
	m_HeroDeckBackGround->SetRelativeScale(600.f * 1280.f / 1606.f, 308.f * 720.f / 903.f, 0.f);
	m_HeroDeckBackGround->SetPivot(0.f, 0.f, 0.f);
	m_HeroDeckBackGround->SetRender2DType(Render_Type_2D::RT2D_BACKMAP);
	m_HeroDeckBackGround->SetRelativePos(-621.f * 1280.f / 1606.f, 441.f * 720.f / 903.f - 308.f * 720.f / 903.f,0.f);
	m_HeroDeckBackGroundMtrl = m_HeroDeckBackGround->GetMaterial(0);
	m_HeroDeckBackGroundMtrl->AddTexture("HeroDeckBack", TEXT("HeroDeckBack.png"));
	m_HeroDeckBackGroundMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
	m_HeroDeckBackGroundMtrl->SetShader("Standard2DTextureShader");

	// 상대비장패 배경
	m_Hero2DeckBackGround->SetRelativeScale(600.f * 1280.f / 1606.f, 308.f * 720.f / 903.f, 0.f);
	m_Hero2DeckBackGround->SetPivot(0.f, 0.f, 0.f);
	m_Hero2DeckBackGround->SetRender2DType(Render_Type_2D::RT2D_BACKMAP);
	m_Hero2DeckBackGround->SetRelativePos(1280.f - 70.f * 1280.f / 1606.f+ 56.f * 1280.f / 1606.f, 450.f,0.f);
	m_Hero2DeckBackGroundMtrl = m_Hero2DeckBackGround->GetMaterial(0);
	m_Hero2DeckBackGroundMtrl->AddTexture("Hero2DeckBack", TEXT("Hero2DeckBack.png"));
	m_Hero2DeckBackGroundMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
	m_Hero2DeckBackGroundMtrl->SetShader("Standard2DTextureShader");

	// 알파블랙
	m_AlphaBlack->SetRelativeScale(0.f, 0.f,0.f);
	m_AlphaBlack->SetPivot(0.f, 0.f, 0.f);
	m_AlphaBlack->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_AlphaBlack->SetRelativePos(-15.f,0.f,0.f);
	m_AlphaBlackMtrl = m_AlphaBlack->GetMaterial(0);
	m_AlphaBlackMtrl->AddTexture("AlphaBlack", TEXT("AlphaBlack.png"));
	m_AlphaBlackMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
	m_AlphaBlackMtrl->SetShader("Standard2DTextureShader");

	// 리스트뒷배경

	m_Cardlist->SetRelativeScale(0.f,0.f, 0.f);
	m_Cardlist->SetPivot(0.f, 0.f, 0.f);
	m_Cardlist->SetRender2DType(Render_Type_2D::RT2D_MAP);

	m_Cardlist->SetRelativePos(37.f * 1280.f / 1603.f-15.f, 94.f * 720.f / 905.f
		, 0.f);
	m_CardlistMtrl = m_Cardlist->GetMaterial(0);
	m_CardlistMtrl->AddTexture("MyUseGround", TEXT("MyUseGround.png"));
	m_CardlistMtrl->SetEmissiveColor(1.2f, 1.2f, 1.2f, 1.2f);
	m_CardlistMtrl->SetShader("Standard2DTextureShader");






	//기본맵 위젯 관리
	m_GameMapWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_GameMapWidget = m_GameMapWidgetComponent->CreateWidget<CGameMapWindow>("m_GameMapWidget");
	m_GameMapWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_GameMapWidgetComponent);


	// 기본동작 위젯 관리
	m_FocusWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Particle);
	m_FocusWidget = m_FocusWidgetComponent->CreateWidget<CFocusHUDWidget>("FocusWidget");
	m_FocusWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_FocusWidgetComponent);

	// 개시 페이즈

	m_GaeSiPhaseWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_GaeSiPhaseWidget = m_GaeSiPhaseWidgetComponent->CreateWidget<CGaeSiPhaseHUDWidget>("GaeSiPhaseWidget");
	m_GaeSiPhaseWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_GaeSiPhaseWidgetComponent);


	// 비장패 버튼만들기용
	m_HeroWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_HeroWidget = m_HeroWidgetComponent->CreateWidget<CHeroHUDUI>("HeroWidget");
	m_HeroWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_HeroWidgetComponent);

	// 상대 비장패 버튼만들기용
	m_Hero2WidgetComponent->SetRender2DType(Render_Type_2D::RT2D_MAP);
	m_Hero2Widget = m_Hero2WidgetComponent->CreateWidget<CHero2HUDUI>("Hero2Widget");
	m_Hero2Widget->SetGameMapObj(this);
	m_Sprite->AddChild(m_Hero2WidgetComponent);

	// 페이즈 UI 및 턴종료 버튼 만들기
	m_PhaseWidgetComponent->SetPivot(0.5f, 0.5f, 0.f);
	m_PhaseWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_PhaseWidget = m_PhaseWidgetComponent->CreateWidget<CPhaseHUDWidget>("CPhaseHUDWidget");
	m_PhaseWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_PhaseWidgetComponent);

	// 멀리건용 UI
	m_MuligunWidgetComponent->SetPivot(0.5f, 0.5f, 0.f);
	m_MuligunWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_MuligunWidget = m_MuligunWidgetComponent->CreateWidget<CMulrigunHUDWidget>("m_MuligunWidget");
	m_MuligunWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_MuligunWidgetComponent);

	// 카드사용 UI
	m_CardUseWidgetComponent->SetPivot(0.5f, 0.5f, 0.f);
	m_CardUseWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_CardUseWidget = m_CardUseWidgetComponent->CreateWidget<CCardUseHUDWidget>("m_CardUseWidget");
	m_CardUseWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_CardUseWidgetComponent);

	// 카드사용 UI
	m_BackWidgetComponent->SetPivot(0.5f, 0.5f, 0.f);
	m_BackWidget = m_BackWidgetComponent->CreateWidget<CBackHUDWidget>("m_BackWidget");
	m_Sprite->AddChild(m_BackWidgetComponent);

	// 스타트애니메이션
	/*m_GameMapAnimationComponent->SetPivot(0.f, 0.f, 0.f);
	m_GameMapAnimationComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_GameMapAnimation = m_GameMapAnimationComponent->CreateWidget<CGameMapAnimation>("m_GameMapAnimation");
	m_GameMapAnimation->SetGameMapObj(this);
	m_Sprite->AddChild(m_GameMapAnimationComponent);*/


	m_vecPlayer1_focus_Collider->AddCollisionMouseCallbackFunction< CGameMapObj>(Collision_State::Begin, this, &CGameMapObj::CollisionFocusMouseStart);
	m_vecPlayer1_focus_Collider->AddCollisionMouseCallbackFunction< CGameMapObj>(Collision_State::End, this, &CGameMapObj::CollisionFocusMouseEnd);

	CInput::GetInst()->AddKeyCallback<CGameMapObj>("Skill1", KT_Down, this, &CGameMapObj::DrawTest);
	CInput::GetInst()->AddKeyCallback<CGameMapObj>("Skill2", KT_Down, this, &CGameMapObj::Player1UseLook);
	CInput::GetInst()->AddKeyCallback<CGameMapObj>("Skill3", KT_Down, this, &CGameMapObj::Player1BackLook);
	CInput::GetInst()->AddKeyCallback<CGameMapObj>("Skill4", KT_Down, this, &CGameMapObj::AiUseLook);
	CInput::GetInst()->AddKeyCallback<CGameMapObj>("Skill5", KT_Down, this, &CGameMapObj::AiBackLook);
	CInput::GetInst()->AddKeyCallback<CGameMapObj>("esc", KT_Down, this, &CGameMapObj::ESCButton);
	return true;
}

void CGameMapObj::Update(float DeltaTime)
{
	bool MousePut = CInput::GetInst()->GetMousePut();
	bool MouseRightPut = CInput::GetInst()->GetMouseRightPut();
	bool MouseRightClick = CInput::GetInst()->GetMouseRightState();





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

































	m_Card5Tick++;
	if (m_Card5Tick > 20)
	{
		m_Card5Tick = 0;
	
		if (m_Backtriger)
			m_Backtriger = false;
		if (m_UseTriger)
			m_UseTriger = false;

	}
	// 로그보여주기
	if (m_LogLook)
	{
		m_LogObj->SetRelativePos(300.f, 360.f, 0.f);
	}
	else
	{
		m_LogObj->SetRelativePos(-1200.f, 0.f, 0.f);
	}
	if (m_usebackwidgetcheck)
	{
		m_pScene->GetResource()->SoundPlay("widget");
		if (m_player1use)
		{
			SettingPlayer1Use();
			
		}
		if (m_player1back)
		{
			SettingPlayer1Back();
			
		}
		if (m_Ai1use)
		{
			SettingAiUse();
			
		}
		if (m_Ai1back)
		{
			SettingAiBack();
			
		}
		m_usebackwidgetcheck = false;
	}

	/// <summary>
	/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="DeltaTime"></param>
	/// 	/// <summary>
	/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="DeltaTime"></param>
/// 
	CGameObject::Update(DeltaTime);
	// Back 

	if (m_Player1_win && m_AnimationCard->GetCardInfoEmpty())
	{

		if (CClientManager::GetInst()->GetAiIndex() > 0)
		{
			CExcel tempExcel;

			tempExcel.StageClear(CClientManager::GetInst()->GetAiIndex(), "stagecleardata.csv");
		}


		m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1Win, nullptr, 0, 0);
		m_pScene->GetResource()->SoundPlay("victory");
		m_Player1_win = false;
		//m_SelectTiming = false;

	}
	else if(m_player2_win && m_AnimationCard->GetCardInfoEmpty())
	{
		m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player2Win, nullptr, 0, 0);
		m_pScene->GetResource()->SoundPlay("defeat");
		m_player2_win = false;
		//m_SelectTiming = false;
	}



	// 화면 검게해주는거
	if (m_SelectTiming)
	{
		GetAlphaBlack()->SetRelativeScale(1280.f, 720.f, 0.f);
		if (m_LogLook)
		{
			m_LogObj->SetRelativePos(300.f, 360.f, 0.f);
		}
		else
		{
			m_LogObj->SetRelativePos(-1200.f, 0.f, 0.f);
		}
		return;
	}
	else
	{
		GetAlphaBlack()->SetRelativeScale(0.f, 0.f, 0.f);
	}
	if (m_stackCreateAttackCard.size() > 0)
	{
		CCard* temp = m_stackCreateAttackCard.top();
		bool tempbool = Player1Daueg(temp);
	
		
		m_GaeSiPhaseWidget->ClickDaeung((CAttackCard*)temp , tempbool);

	
	
		m_stackCreateAttackCard.pop();
		return;
	}
	//
	if (m_stackUseCard.size() > 0)
	{
		if (m_bozoCard == m_stackUseCard.top())
		{
			int i = 0;
		}
		m_stackUseCard.top()->SetUse(true);
		if (m_stackUseCard.top()->GetCardType() == Card_Type::Attack)
		{
			UseAttackBYIndex(m_stackUseCard.top()->GetPlayer(), m_stackUseCard.top());
		
		}
		else if (m_stackUseCard.top()->GetCardType() == Card_Type::Spell)
		{
			
			UseSpellBYIndex(m_stackUseCard.top()->GetPlayer(), m_stackUseCard.top());
		
		
		
		}
		else if (m_stackUseCard.top()->GetCardType() == Card_Type::Building)
		{
			CCard* tempcard = m_stackUseCard.top();
			CBuildingCard* tempbuilding = (CBuildingCard*)tempcard;
		
			tempbuilding->SetNabPoint(0);
			tempbuilding->SetUse(true);
			if (tempbuilding->GetPlayer() == 1)
			{
				m_SelectTiming = true;
				m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Building, tempbuilding, tempbuilding->GetNab(), 0);
			}
			else
			{	// Ai식 납 넣기
				int tempNab = (tempbuilding)->GetNab();
				for (int i = 0; i < tempNab; ++i)
				{
					if (GetDust() > 0)
					{
						tempbuilding->AddNabPoint(1);
						AddDust(-1);
					}
					else
					{
						if (GetPlayer2Shiled() > 0)
						{
							tempbuilding->AddNabPoint(1);
							AddPlayer2Shiled(-100);
						}
						else
							break;
						
					}
				}
				Player1BuildingSetPos();
				UseBuildingBYIndex(tempbuilding->GetPlayer(), tempbuilding);
			}
	


			if (tempbuilding->GetNab() == 0)
				UseBuildingBreakBYIndex(tempbuilding->GetPlayer(), tempbuilding);
			
		}
	


		if (m_stackUseCard.top()->GetPlayer())
			m_TenreokuCheck++;
		else
			m_TenreokuCheckPlayer2++;
	
		if (m_stackUseCard.top()->GetDaeungTriger() == 1)
		{
			m_stackUseCard.top()->SetDaeungTriger(false);
			UseDaeugBYCard(m_stackUseCard.top());
		}


		m_stackUseCard.pop();

	}

	// 공격 뭘로맞을거야?
	if (m_player1_Attackselect)
	{
		m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1AttackSelect, m_bozoCard10, m_player1_AttackSelectShiledtemp, m_player1_AttackSelectLifetemp);
		m_bozoCard10 = nullptr;
		m_player1_Attackselect = false;
	}
	//무음벽 체크
	if (m_Hero3_Card6_Normal_UITriger != 0)
	{
		m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1Hero3Card6, PlayerHero3Card6(), m_Hero3_Card6_Normal_UITriger, 0);

		m_Hero3_Card6_Normal_UITriger = 0;
	}




	// 게임시작시 멀리건 
	if (m_Muligun)
	{
		HeroDeckSorting();
		m_MuligunWidget->CloseWidget();
		m_Muligun = false;
	}

	// 멀리건이 끝난는가?
	if (m_MuligunEnd)
	{	
		m_SelectTiming = false;
		m_TestDelayTime += DeltaTime;
		HandSortSetting();
		if (m_WhoFirst == 1)
		{
			
			if (m_TestDelayTime >= 1.5f)
			{
				m_pScene->GetResource()->SoundPlay("TurnStart");
				SetPlayer2focus(1);
				m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Main);
				m_MuligunEnd = false;
			}
			
		}
		else if(m_WhoFirst == 2)
		{
			if (m_TestDelayTime >= 1.5f)
			{
				m_pScene->GetResource()->SoundPlay("TurnStart");
				SetPlayer1focus(1);
				m_Player2Main = true;
				m_PhaseWidget->CreatePhaseUI(PhaseType::Player2Main);
				m_MuligunEnd = false;
			}
			
		}
		
	}

	// 개시페이즈 시작 
	if (m_Player1Gaesi &&  m_AnimationCard->GetCardInfoEmpty())
	{
		GaesiStart();
		//m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Gaeshi);
		Player1Gaesi();
		
		m_Player1Gaesi = false;
	}

	if (m_Player1GaesiEnd && m_AnimationCard->GetCardInfoEmpty()&& m_stackUseCard.size() == 0)
	{
		
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 0.5f)
		{
			m_pScene->GetResource()->SoundPlay("TurnStart");
			HandSortSetting();
			m_TestDelayTime = 0;
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Main);
			m_Player1GaesiEnd = false;
			m_TenreokuCheck = 0;
		}
		
	}


////////////////////////////////////
// 플레이어 메인 처리 
	if (m_Player1Main &&!m_player1use && !m_player1back && !m_Ai1use && m_AnimationCard->GetCardInfoEmpty() && m_stackUseCard.size() == 0 && !m_Ai1back && !m_Player1MainEnd && !m_Player1_win && !m_player2_win)
	{

		if (!m_SelectTiming && MouseRightClick)
		{
			if (MouseRightPut)
			{
				if (m_Player1_Select_USEANDBACK)
				{
					
					
					m_CardUseWidget->CloseWidget();
				
				}
				
			}
			if (m_Down)
			{	
				
				if (m_FocusTriger && m_Player1_focus >= 0)
				{
					m_CardUseWidget->CloseWidget();
					Player1UseFocus();
				}
					

				if (m_Player1_Select_USEANDBACK && m_pScene->GetCard() != nullptr)
				{	
					
					m_SceneCard = m_pScene->GetCard();
				
					
					if (m_SceneCard)
					{	
						if (!m_SceneCard->GetUse() && m_SceneCard->GetPlayer() == 1)
						{
							int tempWidgetIndex = 0;
							if (m_TenreokuCheck > 0 && m_SceneCard->GetTenreok() == 1)
							{
								tempWidgetIndex = 1;
							}
							if (m_SceneCard->GetCardClass() == Card_Class::Normal)
							{
								m_CardUseWidget->OpenWidget(m_SceneCard->GetRelativePos().x, m_SceneCard->GetRelativePos().y, 1, tempWidgetIndex);
							}
							else
							{
								m_CardUseWidget->OpenWidget(m_SceneCard->GetRelativePos().x, m_SceneCard->GetRelativePos().y, 2, tempWidgetIndex);
							}

						}
					

					}
					/*else
					{
						m_CardUseWidget->CloseWidget();
					}*/
				}
				else if(m_pScene->GetCard() != nullptr)
				{
					m_SceneCard = m_pScene->GetCard();
					
					if (m_SceneCard)
					{
						if (!m_SceneCard->GetUse() && m_SceneCard->GetPlayer() == 1)
						{
							int tempWidgetIndex = 0;
							if (m_TenreokuCheck > 0 && m_SceneCard->GetTenreok() == 1)
							{
								tempWidgetIndex = 1;
							}
							if (m_SceneCard->GetCardClass() == Card_Class::Normal)
							{
								m_CardUseWidget->OpenWidget(m_SceneCard->GetRelativePos().x, m_SceneCard->GetRelativePos().y, 1, tempWidgetIndex);
							}
							else
							{
								m_CardUseWidget->OpenWidget(m_SceneCard->GetRelativePos().x, m_SceneCard->GetRelativePos().y, 2, tempWidgetIndex);
							}
						}
					}
				}
			}
		}
	}



///////////////////////////
	if (m_Player1Main && m_Player1MainEnd && m_AnimationCard->GetCardInfoEmpty())
	{
		m_CardUseWidget->CloseWidget();
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime > 2.f)
		{
			m_TestDelayTime = 0;
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Exit);
			m_Player1Main = false;
			m_Player1MainEnd = false;
			Player1Mainend();
		}
		
	}
	
	if (m_Player1End && m_AnimationCard->GetCardInfoEmpty())
	{
		// 플레이어가 2장이상일떄 카드 선택해서 버리는 곳 
		if (m_vecPlayer1_Hand.size() > 2)
		{
		
			m_TestDelayTime += DeltaTime;
			if (m_TestDelayTime >= 2.f)
			{
				m_TestDelayTime = 0;
				m_MuligunWidget->ClosePlayer1EndWidget();
				m_Player1End = false;
				
			}
		}
		else
		{
			m_TestDelayTime += DeltaTime;
			if (m_TestDelayTime >= 2.f)
			{
				m_TestDelayTime = 0;
				m_Player1EndEnd = true;
				m_Player1End = false;
				
			}
		}
			

	
	}

	if (m_Player1EndEnd && m_AnimationCard->GetCardInfoEmpty())
	{	
		if (m_turn == 0)
		{
			m_pScene->GetResource()->SoundPlay("TurnStart");
			m_Player2Main = true;
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player2Main);
		
		}
		else
		{
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player2Gasehi);
			
		}
	
	
		Turnendbuffreset(1);
		m_Player1EndEnd = false;
	}

	if (m_Player2Gaesi)
	{	
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 1.5f)
		{
			GaesiStart();
			m_TestDelayTime = 0;
			m_Ai->Gaesi();
			Player1BuildingSetPos();
			m_Player2GaesiEnd = true;
			m_Player2Gaesi = false;
			
		}
	

	
	}
	if (m_Player2GaesiEnd && m_AnimationCard->GetCardInfoEmpty() && m_stackUseCard.size() == 0)
	{
	

		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 1.6f)
		{
			m_TestDelayTime = 0;
			m_pScene->GetResource()->SoundPlay("TurnStart");
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player2Main);
			HandSortSetting();
			m_Player2GaesiEnd = false;
			m_TenreokuCheckPlayer2 = 0;
		}
	
	}

	
	



	if (m_Player2Main && m_AnimationCard->GetCardInfoEmpty())
	{
		// AI 메인페이즈
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 2.5f)
		{
			m_TestDelayTime = 0;
			if(!m_Player2MainEnd)
				m_Ai->Init();
			
		}
	
	
	}
	if (m_Player2Main &&m_Player2MainEnd && m_AnimationCard->GetCardInfoEmpty())
	{
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 1.f)
		{
			m_TestDelayTime = 0;
			m_PhaseWidget->CreatePhaseUI(PhaseType::Player2Exit);
			m_Player2Main = false;
			m_Player2MainEnd = false;
			Player2Mainend();
		}
		
	}
	if (m_Player2End)
	{
		m_TestDelayTime += DeltaTime;
		if (m_TestDelayTime >= 1.5f)
		{
			m_TestDelayTime = 0;
			m_Ai->End();
			HandSortSetting();
			m_Player2EndEnd = true;
			m_Player2End = false;
		}
	}
	if (m_Player2EndEnd && m_AnimationCard->GetCardInfoEmpty())
	{
		
		m_TestDelayTime += DeltaTime;
		
		if (m_turn == 0)
		{

		
			if (m_TestDelayTime >= 0.5f)
			{
				Turnendbuffreset(2);
				HandSortSetting();
				m_TestDelayTime = 0;
				m_pScene->GetResource()->SoundPlay("TurnStart");
				m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Main);
				m_Player2EndEnd = false;
				m_TenreokuCheck = 0;
			}
		

		}
		else
		{
			if (m_TestDelayTime >= 1.5f)
			{
				Turnendbuffreset(2);
				HandSortSetting();
				m_TestDelayTime = 0;
				m_PhaseWidget->CreatePhaseUI(PhaseType::Player1Gaeshi);
				m_Player2EndEnd = false;

			}
		}
	}
	


	//////////////////////
	// 항상 체크하는곳 ex) 즉재기
	if (m_Hero1_Card2_Hero)
	{
		if (GetPlayer1Life() <= 3)
		{
			for (int i = 0; i < m_vecPlayer1_HeorUse.size(); ++i)
			{
				if (m_vecPlayer1_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer1_HeorUse[i]->GetHeroIndex() == 1)
				{	
					m_vecPlayer1_Hero.push_back(m_vecPlayer1_HeorUse[i]);
					m_vecPlayer1_HeorUse.erase(m_vecPlayer1_HeorUse.begin() + i);
				//	m_AnimationCard->PushCardInfo(1,2,Card_Class::Hero,1);
					HeroDeckSorting();
					break;
				}
			}
			m_Hero1_Card2_Hero = false;
		}
	}
	if (m_Hero1_Card2_Hero_Player2)
	{
		if (GetPlayer2Life() <= 3)
		{
			for (int i = 0; i < m_vecPlayer2_HeorUse.size(); ++i)
			{
				if (m_vecPlayer2_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer2_HeorUse[i]->GetHeroIndex() == 1)
				{
					m_vecPlayer2_Hero.push_back(m_vecPlayer2_HeorUse[i]);
					m_vecPlayer2_HeorUse.erase(m_vecPlayer2_HeorUse.begin() + i);
					//m_AnimationCard->PushCardInfo(1, 2, Card_Class::Hero,2);
					HeroDeckSorting();
					break;
				}
			}
			m_Hero1_Card2_Hero_Player2 = false;
		}
	}
	//////////////////////
	// 틈 체크

	if (m_player1_teum)
	{
		size_t Player1Building = m_vecPlayer1_Building.size();
		for (int i = 0; i < m_vecPlayer1_Building.size(); ++i)
		{
			CCard* tempcard = m_vecPlayer1_Building[i];
			if (((CBuildingCard*)tempcard)->Getteum() == 1)
			{
				int Nab = ((CBuildingCard*)tempcard)->GetNabpoint();
				((CBuildingCard*)tempcard)->AddNabPoint(-Nab);
				AddDust(Nab);
				((CBuildingCard*)tempcard)->SetUse(false);
				tempcard->SettingGone();
				if (tempcard->GetCardClass() == Card_Class::Hero)
				{
					m_vecPlayer1_HeorUse.push_back(tempcard);
				}
				else
				{
					m_vecPlayer1_Back.push_back(tempcard);
				}
				m_vecPlayer1_Building.erase(m_vecPlayer1_Building.begin() + i);
				--i;
			}
		}
	}
	if (m_player2_teum)
	{
		size_t Player1Building = m_vecPlayer2_Building.size();
		for (int i = 0; i < m_vecPlayer2_Building.size(); ++i)
		{
			CCard* tempcard = m_vecPlayer2_Building[i];
			if (((CBuildingCard*)tempcard)->Getteum() == 1)
			{
				((CBuildingCard*)tempcard)->SetUse(false);
				int Nab = ((CBuildingCard*)tempcard)->GetNabpoint();
				((CBuildingCard*)tempcard)->AddNabPoint(-Nab);
				AddDust(Nab);
				tempcard->SettingGone();
				if (tempcard->GetCardClass() == Card_Class::Hero)
				{
					m_vecPlayer2_HeorUse.push_back(tempcard);
				}
				else
				{
				
					m_vecPlayer2_Back.push_back(tempcard);
				}
				m_vecPlayer2_Building.erase(m_vecPlayer2_Building.begin() + i);
				--i;
			}
		}
	}
	
}
/// <summary>
	/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="DeltaTime"></param>
	/// 	/// <summary>
	/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="DeltaTime"></param>
void CGameMapObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CGameMapObj::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CGameMapObj::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CGameMapObj* CGameMapObj::Clone()
{
	return new CGameMapObj(*this);
}

void CGameMapObj::Player1CardToBack()
{	
	m_pScene->GetResource()->SoundPlay("CardtoBack");
	size_t Handvecsize = m_vecPlayer1_Hand.size();
	if (m_SceneCard == nullptr || m_SceneCard->GetCardClass()== Card_Class::Hero)
		return;
	
	auto iter = m_vecPlayer1_Hand.begin();
	auto iterend = m_vecPlayer1_Hand.end();
	for (; iter != iterend; ++iter)
	{
		if(*iter == m_SceneCard)
		{
			m_vecPlayer1_Back.push_back(*iter);
			(*iter)->SettingGone();
			m_vecPlayer1_Hand.erase(iter);
			break;
		}
	}

	m_FocusWidget->OpenWidget(1);


	Player1BackCheck();
	HandSortSetting();
	m_SelectTiming = true;
	m_SceneCard = nullptr;
	m_pScene->NullCard();
}


void CGameMapObj::CollisionBackEnd(const HitResult& result, CCollider* Collider)
{
	m_Card5Tick = 0;
	m_Backtriger = true;
	
}

void CGameMapObj::CollisionUseEnd(const HitResult& result, CCollider* Collider)
{
	m_Card5Tick = 0;
	m_UseTriger = true;
}



void CGameMapObj::CollisionFocusMouseStart(const Vector2& pos, CCollider* Collider)
{
	m_FocusTriger = true;
}

void CGameMapObj::CollisionFocusMouseEnd(const Vector2& pos, CCollider* Collider)
{
	m_FocusTriger = false;
}


void CGameMapObj::Player1BackCheck()
{
	/*size_t Player1vecBackSize = m_vecPlayer1_Back.size();
	if (Player1vecBackSize == 0)
	{
		m_SpriteMtrl->AddTexture("backempty", TEXT("card/backempty.jpg"));
	}
	else
	{
		m_SpriteMtrl->AddTexture("back1", TEXT("card/back.jpg"));
	}*/
}

void CGameMapObj::Player1UseFocus()
{	
	if (m_Player1_focus <= 0 || Player1FocusCheck() == false)
		return;
	m_TenreokuCheck++;
	m_FocusWidget->OpenWidget(0);
	m_SelectTiming = true;
	AddPlayer1focus(-1);
	
	
}

void CGameMapObj::PlayerCardToUse()
{

	if (m_SceneCard == nullptr)
		return;
	if (m_SceneCard->GetCardClass() == Card_Class::Hero && m_SceneCard->GetCardIndex() == 3 && m_SceneCard->GetHeroIndex() == 3)
	{
		return;
	}


	size_t Player1HandSize = m_vecPlayer1_Hand.size();

	for (int i = 0; i < Player1HandSize; ++i)
	{
		if (m_vecPlayer1_Hand[i] == m_SceneCard)
		{
			
			switch (m_SceneCard->GetCardType())
			{
			case Card_Type::Attack:
				if (Player1UseAttackCard((CAttackCard*)m_SceneCard))
				{
					m_vecPlayer1_Use.push_back(m_vecPlayer1_Hand[i]);
					m_vecPlayer1_Hand[i]->SettingGone();
					m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin()+i);
					Player1HandSize = m_vecPlayer1_Hand.size();
					if (m_SceneCard->GetCardType() == Card_Type::Attack && m_Ai->AiDauengCheck((CAttackCard*)m_SceneCard) && m_buff_Don_Daeug ==0&& ((CAttackCard*)m_SceneCard)->GetDaeugbool() == false)
					{
						
						m_stackUseCard.push(m_SceneCard);
						PushAnimationCard(m_SceneCard,1);
						LogCreate(m_SceneCard,nullptr,0,1);
						LogCreate(m_Ai->AiUseDaueng(), m_SceneCard, 0, 2);
					
						m_Ai->Player1AttackCardSetting((CAttackCard*)m_SceneCard);
					}
					else
					{
						m_buff_Don_Daeug = 0;
						m_stackUseCard.push(m_SceneCard);
						LogCreate(m_SceneCard, nullptr, 0, 1);
						
						PushAnimationCard(m_SceneCard,0);
					}
					break;
				}
				break;
			case Card_Type::Spell:
				if (Player1UseSpellCard((CSpellCard*)m_SceneCard))
				{
					m_vecPlayer1_Use.push_back(m_vecPlayer1_Hand[i]);
					m_vecPlayer1_Hand[i]->SettingGone();
					m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
					Player1HandSize = m_vecPlayer1_Hand.size();
					m_stackUseCard.push(m_SceneCard);
					PushAnimationCard(m_SceneCard,0);
					LogCreate(m_SceneCard, nullptr, 0, 1);
					break;
				}
				break;
			case Card_Type::Building:
				if (Player1UseBuildingCard((CBuildingCard*)m_SceneCard))
				{	
					m_vecPlayer1_Building.push_back(m_vecPlayer1_Hand[i]);
					m_vecPlayer1_Hand[i]->SetRelativePos(620.f, 360.f, 0.f);
					m_vecPlayer1_Hand[i]->SetStartHandPos(Vector3(620.f, 360.f, 0.f));
					m_vecPlayer1_Hand[i]->SetMove(false);
					m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
					Player1HandSize = m_vecPlayer1_Hand.size();
					m_stackUseCard.push(m_SceneCard);
					PushAnimationCard(m_SceneCard,0);
					LogCreate(m_SceneCard, nullptr, 0, 1);
					break;
				}
				break;
			default:
				break;
			}
			
		
		}
	}
	size_t Player1HeroHandSize = m_vecPlayer1_Hero.size();

	for (int i = 0; i < Player1HeroHandSize; ++i)
	{
		if (m_vecPlayer1_Hero[i] == m_SceneCard)
		{
			switch (m_SceneCard->GetCardType())
			{
			case Card_Type::Attack:

				if (Player1UseAttackCard((CAttackCard*)m_SceneCard))
				{	
					
					m_vecPlayer1_HeorUse.push_back(m_vecPlayer1_Hero[i]);
					m_vecPlayer1_Hero[i]->SettingGone();
					m_vecPlayer1_Hero.erase(m_vecPlayer1_Hero.begin()+i);
					Player1HeroHandSize = m_vecPlayer1_Hero.size();
					if (m_SceneCard->GetCardType() == Card_Type::Attack && m_Ai->AiDauengCheck((CAttackCard*)m_SceneCard) && m_buff_Don_Daeug == 0&& ((CAttackCard*)m_SceneCard)->GetDaeugbool() == false)
					{
						Player1CardManaCost(m_SceneCard);
						m_stackUseCard.push(m_SceneCard);
						PushAnimationCard(m_SceneCard,1);
						m_AnimationCard->SetAnimIndex(2);
					
						LogCreate(m_SceneCard, nullptr, 0, 1);
						LogCreate(m_Ai->AiUseDaueng(), m_SceneCard, 0, 2);
						m_Ai->Player1AttackCardSetting((CAttackCard*)m_SceneCard);
					}
					else
					{
						Player1CardManaCost(m_SceneCard);
						m_buff_Don_Daeug = 0;
						m_stackUseCard.push(m_SceneCard);
						PushAnimationCard(m_SceneCard,0);
						LogCreate(m_SceneCard, nullptr, 0, 1);
					}
					break;
				}
				break;
			case Card_Type::Spell:
				if (Player1UseSpellCard((CSpellCard*)m_SceneCard))
				{
					Player1CardManaCost(m_SceneCard);
					m_vecPlayer1_HeorUse.push_back(m_vecPlayer1_Hero[i]);
					m_vecPlayer1_Hero[i]->SettingGone();
					m_vecPlayer1_Hero.erase(m_vecPlayer1_Hero.begin() + i);
					Player1HeroHandSize = m_vecPlayer1_Hero.size();
					m_stackUseCard.push(m_SceneCard);
					PushAnimationCard(m_SceneCard,0);
					LogCreate(m_SceneCard, nullptr, 0, 1);
					break;
				}
				break;
			case Card_Type::Building:
				if (Player1UseBuildingCard((CBuildingCard*)m_SceneCard))
				{
					Player1CardManaCost(m_SceneCard);
					m_vecPlayer1_Building.push_back(m_vecPlayer1_Hero[i]);
					m_vecPlayer1_Hero[i]->SetRelativePos(620.f, 360.f, 0.f);
					m_vecPlayer1_Hero[i]->SetStartHandPos(Vector3(620.f, 360.f, 0.f));
					m_vecPlayer1_Hero[i]->SetMove(false);
					m_vecPlayer1_Hero.erase(m_vecPlayer1_Hero.begin() + i);
					Player1HeroHandSize = m_vecPlayer1_Hero.size();
					m_stackUseCard.push(m_SceneCard);
					PushAnimationCard(m_SceneCard,0);
					LogCreate(m_SceneCard, nullptr, 0, 1);
					break;
				}
				break;
			default:
				break;
			}
			
		}
	}


	
//	Player1UseCheck();
	m_pScene->GetResource()->SoundPlay("CardtoUse");
	HandSortSetting();
//	m_SelectTiming = true;
	m_SceneCard = nullptr;
	m_pScene->NullCard();

}

void CGameMapObj::Player1UseCheck()
{
	m_vecPlayer1_Use.back()->SetRelativePos(640.f - 75.f, 360.f - 150.f, 0.f);
	m_vecPlayer1_Use.back()->SetStartHandPos(Vector3(640.f - 75.f, 360.f - 150.f,0.f));

	//640.f - 75.f, 360.f - 150.f, 0.f
}

bool CGameMapObj::Player1UseAttackCard(CAttackCard* card)
{	
	// 거리 관련 버프 처리
	if (m_Hero1_Card4_Normal || m_Hero1_Card4_Normal_Player2)
		m_buff_Range_Min++;


	int cardindex = card->GetCardIndex();
	int heroindex = card->GetHeroIndex();
	int RangeMin = card->GetMin() - m_buff_Range_Min;
	int RangeMax = card->GetMax();
	//int ShieldDamage;
	//int LifeDamage;
	int ManaCost = card->GetManaCosT();
	Card_Class CardClass = card->GetCardClass();

	if (cardindex == 3 && heroindex == 1 && CardClass == Card_Class::Hero)
	{
		if (card->GetPlayer() == 1)
		{
			if (m_Player1_Life > 3)
			{
				m_buff_Range_Min = 0;
				m_SelectTiming = false;
				return false;
			}
		}
		else
		{
			if (m_Player2_Life > 3)
			{
				m_buff_Range_Min = 0;
				m_SelectTiming = false;
				return false;
			}
		}
		
	}

	if (card->GetPlayer() == 1)
	{
		if (m_TenreokuCheck > 0 && card->GetTenreok() == 1)
		{
			m_buff_Range_Min = 0;
			m_SelectTiming = false;
			return false;
		}

	}
	




	if (RangeMin <= m_Range && m_Range <= RangeMax)
	{
		if (card->GetPlayer() == 1)
		{
			if (card->GetManaCosT() <= m_Player1_Mana)
			{

			}
			else
			{
				m_buff_Range_Min = 0;
				m_SelectTiming = false;
				return false;
			}
		}
		else
		{
			if (card->GetManaCosT() <= m_Player2_Mana)
			{

			}
			else
			{
				m_buff_Range_Min = 0;
				m_SelectTiming = false;
				return false;
			}
		}

		m_buff_Range_Min = 0;
		m_SelectTiming = false;
		return true;
	}
	else
	{
		m_buff_Range_Min = 0;
		m_SelectTiming = false;
		return false;
		// 공격거리안됨
	}


	m_buff_Range_Min = 0;
	return true;
}

bool CGameMapObj::Player1UseSpellCard(CSpellCard* card)
{
	if (card->GetPlayer() == 1)
	{
		if (m_TenreokuCheck > 0 && card->GetTenreok() == 1)
		{

			m_SelectTiming = false;
			return false;
		}
	}
	int manabuff = 0;
	if (card->GetCardIndex() == 1 && card->GetHeroIndex() == 3 && card->GetCardClass() == Card_Class::Hero)
	{	if(card->GetPlayer() == 1)
			manabuff = m_Player2_Shiled;
		else
			manabuff = m_Player1_Shiled;
		
	}
	if (card->GetCardClass() == Card_Class::Hero)
	{
		if (card->GetPlayer() == 1)
		{
			if (card->GetManaCosT()- manabuff <= m_Player1_Mana)
			{

			}
			else
			{
				m_SelectTiming = false;
				return false;
			}
		}
		else
		{
			if (card->GetManaCosT() - manabuff <= m_Player2_Mana)
			{

			}
			else
			{
				m_SelectTiming = false;
				return false;
			}
		}
	}

	//m_Player1UseSpellCard = card;
	return true;
}

bool CGameMapObj::Player1UseBuildingCard(CBuildingCard* card)
{
	if (card->GetPlayer() == 1)
	{
		if (m_TenreokuCheck > 0 && card->GetTenreok() == 1)
		{

			m_SelectTiming = false;
			return false;
		}
	}

	if (card->GetCardClass() == Card_Class::Hero)
	{
		if (card->GetPlayer() == 1)
		{
			if (card->GetManaCosT() <= m_Player1_Mana)
			{

			}
			else
			{
				m_SelectTiming = false;
				return false;
			}
		}
		else
		{
			if (card->GetManaCosT() <= m_Player2_Mana)
			{

			}
			else
			{
				m_SelectTiming = false;
				return false;
			}
		}

	
	}
	
	//m_Player1UseBuildingCard = card;
	return true;
}








int CGameMapObj::DrawACard(int drawCounter)
{	
	m_GameMapWidget->PushAnimation(Player1DeckNumber);
	size_t sizevec = m_vecPlayer1_Deck.size();

	if (sizevec >= drawCounter)
	{
		for (int i = 0; i < drawCounter; ++i)
		{
			m_vecPlayer1_Deck.back()->CreateTex();
			m_vecPlayer1_Hand.push_back(m_vecPlayer1_Deck.back());
			m_vecPlayer1_Deck.pop_back();
			
		}
		
		return 0;
		
	}
	else
	{

		for (int i = 0; i < sizevec; ++i)
		{
			m_vecPlayer1_Deck.back()->CreateTex();
			m_vecPlayer1_Hand.push_back(m_vecPlayer1_Deck.back());
			m_vecPlayer1_Deck.pop_back();
		}
		
		return drawCounter - sizevec;
	
	}


}

int CGameMapObj::DrawACard2(int drawCounter)
{
	m_GameMapWidget->PushAnimation(Player2DeckNumber);
	size_t sizevec = m_vecPlayer2_Deck.size();

	if (sizevec >= drawCounter)
	{
		for (int i = 0; i < drawCounter; ++i)
		{
			m_vecPlayer2_Deck.back()->SetBack();
			m_vecPlayer2_Hand.push_back(m_vecPlayer2_Deck.back());
			m_vecPlayer2_Deck.pop_back();
		}
		
		return 0;

	}
	else
	{

		for (int i = 0; i < sizevec; ++i)
		{
			m_vecPlayer2_Deck.back()->SetBack();
			m_vecPlayer2_Hand.push_back(m_vecPlayer2_Deck.back());
			m_vecPlayer2_Deck.pop_back();
		}
		
		return drawCounter - sizevec;

	}

}

void CGameMapObj::RefreshDeck()
{	// 테스트
	
	size_t BackSize = m_vecPlayer1_Back.size();
	size_t UseSize = m_vecPlayer1_Use.size();
	if (BackSize == 0 && UseSize == 0)
	{	
		AddPlayer1Life(-1);
		m_player1_teum = false;
		AddPlayer1Mana(1);
		srand(GetTickCount());

		int DeckSize = m_vecPlayer1_Deck.size();
		int* Arr = new int[DeckSize];
		for (int i = 0; i < DeckSize; ++i)
		{
			Arr[i] = i;
		}
		for (int i = 0; i < 50; i++)
		{
			int S1 = rand() % DeckSize;
			int S2 = rand() % DeckSize;

			CCard* temp = m_vecPlayer1_Deck[S1];
			m_vecPlayer1_Deck[S1] = m_vecPlayer1_Deck[S2];
			m_vecPlayer1_Deck[S2] = temp;
		}
		delete Arr;
		return;
	}
		

	for (int i = 0; i < BackSize; ++i)
	{	

		m_vecPlayer1_Deck.push_back(m_vecPlayer1_Back[i]);
		m_vecPlayer1_Deck.back()->SettingGone();
		//m_vecPlayer1_Deck.back()->SetUse(false);
	}
	for (int i = 0; i < UseSize; ++i)
	{
	
		m_vecPlayer1_Deck.push_back(m_vecPlayer1_Use[i]);
		m_vecPlayer1_Deck.back()->SettingGone();
		m_vecPlayer1_Deck.back()->SetUse(false);
	}
	m_vecPlayer1_Back.clear();
	m_vecPlayer1_Use.clear();


	srand(GetTickCount());

	int DeckSize = m_vecPlayer1_Deck.size();
	int* Arr = new int[DeckSize];
	for (int i = 0; i < DeckSize; ++i)
	{
		Arr[i] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		int S1 = rand() % DeckSize;
		int S2 = rand() % DeckSize;

		CCard* temp = m_vecPlayer1_Deck[S1];
		m_vecPlayer1_Deck[S1] = m_vecPlayer1_Deck[S2];
		m_vecPlayer1_Deck[S2] = temp;
	}
	delete Arr;
	AddPlayer1Life(-1);
	AddPlayer1Mana(1);
	m_player1_teum = false;
	Player1BackCheck();
}

void CGameMapObj::RefreshDeck2()
{
	size_t BackSize = m_vecPlayer2_Back.size();
	size_t UseSize = m_vecPlayer2_Use.size();
	if (BackSize == 0 && UseSize == 0)
	{
		AddPlayer2Life(-1);
		AddPlayer2Mana(1);
		m_player2_teum = false;
		srand(GetTickCount());

		int DeckSize = m_vecPlayer2_Deck.size();
		int* Arr = new int[DeckSize];
		for (int i = 0; i < DeckSize; ++i)
		{
			Arr[i] = i;
		}
		for (int i = 0; i < 50; i++)
		{
			int S1 = rand() % DeckSize;
			int S2 = rand() % DeckSize;

			CCard* temp = m_vecPlayer2_Deck[S1];
			m_vecPlayer2_Deck[S1] = m_vecPlayer2_Deck[S2];
			m_vecPlayer2_Deck[S2] = temp;
		}
		delete Arr;
		return;
	}


	for (int i = 0; i < BackSize; ++i)
	{

		m_vecPlayer2_Deck.push_back(m_vecPlayer2_Back[i]);
		m_vecPlayer2_Deck.back()->SettingGone();
		//m_vecPlayer1_Deck.back()->SetUse(false);
	}
	for (int i = 0; i < UseSize; ++i)
	{

		m_vecPlayer2_Deck.push_back(m_vecPlayer2_Use[i]);
		m_vecPlayer2_Deck.back()->SettingGone();
		m_vecPlayer2_Deck.back()->SetUse(false);
	}
	m_vecPlayer2_Back.clear();
	m_vecPlayer2_Use.clear();


	srand(GetTickCount());

	int DeckSize = m_vecPlayer2_Deck.size();
	int* Arr = new int[DeckSize];
	for (int i = 0; i < DeckSize; ++i)
	{
		Arr[i] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		int S1 = rand() % DeckSize;
		int S2 = rand() % DeckSize;

		CCard* temp = m_vecPlayer2_Deck[S1];
		m_vecPlayer2_Deck[S1] = m_vecPlayer2_Deck[S2];
		m_vecPlayer2_Deck[S2] = temp;
	}
	delete Arr;
	AddPlayer2Life(-1);
	m_player2_teum = false;
	AddPlayer2Mana(1);


}

void CGameMapObj::OpenHeroDeck()
{
}

void CGameMapObj::CloseHeroDeck()
{
}

void CGameMapObj::HeroDeckSorting()
{	
	bool tempopen = m_HeroWidget->GetOpen();
	bool tempPlayer2Open = m_Hero2Widget->GetOpen();
	if (tempopen)
	{
		size_t size = m_vecPlayer1_Hero.size();

		if (size == 0)
			return;

		for (int i = 0; i < size; ++i)
		{
			m_vecPlayer1_Hero[i]->SetRelativePos(71.f+ m_vecPlayer1_Hero[i]->GetRelativeScale().x * i + 10.f,  229.f, 0.f);
			
			m_vecPlayer1_Hero[i]->SetStartHandPos(m_vecPlayer1_Hero[i]->GetRelativePos());
			m_vecPlayer1_Hero[i]->SetMove(false);
			m_vecPlayer1_Hero[i]->SetLookable(true);
			m_vecPlayer1_Hero[i]->SetSelect(false);
			m_vecPlayer1_Hero[i]->SetUse(false);
			m_vecPlayer1_Hero[i]->UnSellectTextureSetting();
		}
	}
	else
	{
		size_t size = m_vecPlayer1_Hero.size();

		if (size == 0)
			return;

		for (int i = 0; i < size; ++i)
		{	// HeroHUDUI 참조
			m_vecPlayer1_Hero[i]->SetRelativePos(71.f- (30.f+563.f * 1280.f / 1606.f - 21.f * 1280.f / 1606.f)+ m_vecPlayer1_Hero[i]->GetRelativeScale().x * i + 10.f, 229.f, 0.f);
			
			m_vecPlayer1_Hero[i]->SetStartHandPos(m_vecPlayer1_Hero[i]->GetRelativePos());
			m_vecPlayer1_Hero[i]->SetMove(false);
			m_vecPlayer1_Hero[i]->SetLookable(true);
			m_vecPlayer1_Hero[i]->SetSelect(false);
			m_vecPlayer1_Hero[i]->SetUse(false);
			m_vecPlayer1_Hero[i]->UnSellectTextureSetting();
		}
	}



	if (tempPlayer2Open)
	{
		size_t size = m_vecPlayer2_Hero.size();

		if (size == 0)
			return;

		for (int i = 0; i < size; ++i)
		{
			m_vecPlayer2_Hero[i]->SetRelativePos(1450.f - (30.f + 563.f * 1280.f / 1606.f - 21.f * 1280.f / 1606.f)- 744.f / 8.f / 1.3f+ m_vecPlayer2_Hero[i]->GetRelativeScale().x * i + 10.f, 470.f+ 1038.f / 8.f / 1.3f, 0.f);
			
			m_vecPlayer2_Hero[i]->SetStartHandPos(m_vecPlayer2_Hero[i]->GetRelativePos());
			m_vecPlayer2_Hero[i]->SetMove(false);
			m_vecPlayer2_Hero[i]->SetUse(false);
		}
	}
	else
	{
		size_t size = m_vecPlayer2_Hero.size();

		if (size == 0)
			return;

		for (int i = 0; i < size; ++i)
		{	// HeroHUDUI 참조
			m_vecPlayer2_Hero[i]->SetRelativePos(1450.f-744.f / 8.f / 1.3f+ m_vecPlayer2_Hero[i]->GetRelativeScale().x * i + 10.f, 470.f+ 1038.f / 8.f / 1.3f, 0.f);
		
			m_vecPlayer2_Hero[i]->SetStartHandPos(m_vecPlayer2_Hero[i]->GetRelativePos());
			m_vecPlayer2_Hero[i]->SetMove(false);
			m_vecPlayer2_Hero[i]->SetUse(false);
		}
	}



	
}

void CGameMapObj::Player1BuildingSetPos()
{
	size_t size = m_vecPlayer1_Building.size();


	for (int i = 0; i < size; ++i)
	{
		m_vecPlayer1_Building[i]->SetRelativePos(970.f - (72.1f * size)+ m_vecPlayer1_Building[i]->GetRelativeScale().x * i + 10.f, 250.f, 0.f);
		m_vecPlayer1_Building[i]->SetRelativeScale(744.f / 10.f / 1.3f, 1038.f / 10.f / 1.3f, 0.f);
	
		m_vecPlayer1_Building[i]->SetStartHandPos(m_vecPlayer1_Building[i]->GetRelativePos());
		m_vecPlayer1_Building[i]->SetMove(false);
		m_vecPlayer1_Building[i]->UnSellectTextureSetting();
		m_vecPlayer1_Building[i]->SetSelect(false);
	}

	size_t size2 = m_vecPlayer2_Building.size();


	for (int i = 0; i < size2; ++i)
	{
		m_vecPlayer2_Building[i]->SetRelativePos(400.f - (72.1f * size)+ m_vecPlayer2_Building[i]->GetRelativeScale().x * i + 10.f, 250.f, 0.f);
		m_vecPlayer2_Building[i]->SetRelativeScale(744.f / 10.f / 1.3f, 1038.f / 10.f / 1.3f, 0.f);
		
		m_vecPlayer2_Building[i]->SetStartHandPos(m_vecPlayer2_Building[i]->GetRelativePos());
		m_vecPlayer2_Building[i]->SetMove(false);
		m_vecPlayer2_Building[i]->CreateTex();

	}
	
}

void CGameMapObj::Mulrigungo(CCard* first, CCard* Second, CCard* Thrid)
{
	std::vector<CCard*> vectemp;
	int tempDraw = 0;

	for (int i = 0; i < m_vecPlayer1_Deck.size();)
	{
		vectemp.push_back(m_vecPlayer1_Deck.back());
		m_vecPlayer1_Deck.pop_back();
	}
	if (first != nullptr)
	{	
		for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
		{
			if (first == m_vecPlayer1_Hand[i])
			{	
				m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
				break;
			}
		}
		m_vecPlayer1_Deck.push_back(first);
		tempDraw++;
	}
	if (Second != nullptr)
	{
		for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
		{
			if (Second == m_vecPlayer1_Hand[i])
			{
				m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
				break;
			}
		}
		m_vecPlayer1_Deck.push_back(Second);
		tempDraw++;
	}
	if (Thrid != nullptr)
	{
		for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
		{
			if (Thrid == m_vecPlayer1_Hand[i])
			{
				m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
				break;
			}
		}
		m_vecPlayer1_Deck.push_back(Thrid);
		tempDraw++;
	}

	

	for (int i = 0; i < vectemp.size();)
	{
		m_vecPlayer1_Deck.push_back(vectemp.back());
		vectemp.pop_back();
	}

	DrawACard(tempDraw);
	
}

void CGameMapObj::Player1CardBurn()
{
	for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
	{
		if (m_vecPlayer1_Hand[i]->GetSelect())
		{
			m_vecPlayer1_Hand[i]->UnSellectTextureSetting();
			m_vecPlayer1_Hand[i]->SetSelect(false);
			LogCreate(m_vecPlayer1_Hand[i], nullptr, 2, 1);
			m_vecPlayer1_Back.push_back(m_vecPlayer1_Hand[i]);
			m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
			--i;
		}
	}
	HandSortSetting();
	m_Player1EndEnd = true;
}

void CGameMapObj::Player1BuildingUseAnimation()
{
}

void CGameMapObj::DrawTest(float DeltaTime)
{
	m_pScene->GetResource()->SoundPlay("widget");
	if (m_LogLook)
		m_LogLook = false;
	else
		m_LogLook = true;
}

void CGameMapObj::Player1UseLook(float DeltaTime)
{
	if (m_player1use)
	{	
		SettingAllgone();
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = false;
		m_Ai1back = false;
	}
	else
	{
		m_usebackwidgetcheck = true;
		SettingAllgone();
		m_Ai1back = false;
		m_player1use = true;
		m_player1back = false;
		m_Ai1use = false;
	}
		
}

void CGameMapObj::Player1BackLook(float DeltaTime)
{
	if (m_player1back)
	{
		SettingAllgone();
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = false;
		m_Ai1back = false;
	}
	else
	{
		m_usebackwidgetcheck = true;
		SettingAllgone();
		m_Ai1back = false;
		m_player1use = false;
		m_player1back = true;
		m_Ai1use = false;
	}
}

void CGameMapObj::AiUseLook(float DeltaTime)
{
	if (m_Ai1use)
	{
		SettingAllgone();
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = false;
		m_Ai1back = false;
	}
	else
	{
		m_usebackwidgetcheck = true;
		SettingAllgone();
		m_Ai1back = false;
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = true;
	}
}


void CGameMapObj::AiBackLook(float DeltaTime)
{
	if (m_Ai1back)
	{
		SettingAllgone();
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = false;
		m_Ai1back = false;
	}
	else
	{
		m_usebackwidgetcheck = true;
		SettingAllgone();
		m_Ai1back = true;
		m_player1use = false;
		m_player1back = false;
		m_Ai1use = false;
	}
}

void CGameMapObj::RefreshTest(float DeltaTime)
{
	

	Player1Gaesi();
	

}

void CGameMapObj::UseAttackBYIndex(int player,CAttackCard* attackCard)
{	
	if (attackCard->GetCardClass() == Card_Class::Normal)
	{

		switch (attackCard->GetHeroIndex())
		{
		// 유리나
		case 1:
			switch (attackCard->GetCardIndex())
			{
			case 0:
				AttackUseCard(player, attackCard);


				break;
			case 1:
				if (player == 1)
				{
					if (m_Player1_Life <= 3)
					{
						m_buff_Shiled_Attack++;
					}
				}
				else
				{
					if (m_Player2_Life <= 3)
					{
						m_buff_Shiled_Attack++;
					}
				}
				AttackUseCard(player, attackCard);

				break;
			case 2:
				if (player == 1)
				{
					if (m_Player1_Life <= 3)
					{
						m_buff_Shiled_Attack++;
					}
				}
				else
				{
					if (m_Player2_Life <= 3)
					{
						m_buff_Shiled_Attack++;
					}
				}
				AttackUseCard(player, attackCard);

				break;
			case 3:
				if (m_Range <= 2)
				{
					m_buff_Shiled_Attack--;
					m_buff_Life_Attack--;
				}
				AttackUseCard(player, attackCard);
				// 전력!
				if (player == 1)
				{
					m_Player1MainEnd = true;
				}
				else
				{
					m_Player2MainEnd = true;
				}
				break;
			case 5:
				AttackUseCard(player, attackCard);

				break;
			default:
				break;
			}
			break;
		// 사이네
		case 3:
			switch (attackCard->GetCardIndex())
			{
			case 0:
				AttackUseCard(player, attackCard);
				break;
			case 1:
				AttackUseCard(player, attackCard);
				break;
			case 2:
				AttackUseCard(player, attackCard);
				break;
				// 충음정 보조용
			case 5:
				AttackUseCard(player, attackCard);
				break;
			// 팔방 보조용
			case 7:
				AttackUseCard(player, attackCard);
				break;
			// 율동호극 보조용
			case 8:
				AttackUseCard(player, attackCard);
				break;
			default:
				break;
			}
			break;
			// 토코요
		case 8:
			switch (attackCard->GetCardIndex())
			{
			case 0:
				AttackUseCard(player, attackCard);
				break;
			case 1:
				AttackUseCard(player, attackCard);
				break;
			case 6:
				AttackUseCard(player, attackCard);
				break;
			default:
				break;
			}
			break;


		default:
			break;
		}
	}
	else
	{
		switch (attackCard->GetHeroIndex())
		{
		case 1:
			switch (attackCard->GetCardIndex())
				{
				case 0:
					AttackUseCard(player, attackCard);
					break;
				case 1:
					AttackUseCard(player, attackCard);
					// 종단!!
					if (player == 1)
					{
						m_Player1MainEnd = true;
					}
					else
					{
						m_Player2MainEnd = true;
					}
					break;

				case 3:
					AttackUseCard(player, attackCard);
					// 전력!
					if (player == 1)
					{
						m_Player1MainEnd = true;
					}
					else
					{
						m_Player2MainEnd = true;
					}
					break;
				default:
					break;
				}
			break;
			// 사이네 전력 공격카드
		case 3:
			switch (attackCard->GetCardIndex())
				{
				
				case 2:
					AttackUseCard(player, attackCard);
					break;
				case 3:
					AttackUseCard(player, attackCard);
					break;
				default:
					break;
				}
			break;
			// 토코요 전력 공격카드
		case 8:
			switch (attackCard->GetCardIndex())
			{

			case 0:
				AttackUseCard(player, attackCard);
				break;
			case 1:
				AttackUseCard(player, attackCard);
				break;
			case 2:
				AttackUseCard(player, attackCard);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void CGameMapObj::UseAttackBYIndex(int player, CCard* card)
{
	int Hero = card->GetHeroIndex();
	int Cardindex = card->GetCardIndex();
	Card_Class CardClass = card->GetCardClass();
	UseAttackBYIndex(player, (CAttackCard*)card);
}

void CGameMapObj::UseSpellBYIndex(int player,int hero, int normal, Card_Class cardclass,int spell)
{	
	CCard* tempcard = nullptr;
	int tempint = 0;
	if (cardclass == Card_Class::Normal)
	{

		switch (hero)
		{
		case 1:

			switch (normal)
			{
			case 4:
				if (player == 1)
				{
					AddPlayer1focus(1);
					m_Hero1_Card4_Normal = true;
				}
				else
				{
					AddPlayer2focus(1);
					m_Hero1_Card4_Normal_Player2 = true;
				}
			default:
				break;
			}
			break;
			// 사이네
		case 3:
			switch (normal)
			{
			// 간파 간격 더스트 선택
			case 3:
				if (player == 1)
				{
					m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1DustRange,nullptr,1,0);
				}
				else
				{
					if (!m_Ai->LikeRangeCheck())
					{	
						if (m_Dust > 0)
						{
							AddDust(-1);
							AddRange(1);
						}
					
					}
					else
					{
						if (m_Range > 0)
						{
							AddDust(1);
							AddRange(-1);
						}
					
					}
				}
				break;
			default:
				break;
			}
			break;
			// 토코요
		case 8:
			switch (normal)
			{
				// 날뛰는 토끼
			case 2:
				if (GetRange() <= 3)
				{
					if (GetDust() > 0)
					{
						AddDust(-1);
						AddRange(1);
					}
					if (GetDust() > 0)
					{
						AddDust(-1);
						AddRange(1);
					}
				}
				break;
				// 시의 춤
			case 3:
				if (player == 1)
				{
					AddPlayer1focus(1);
					m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1Hero8card3, nullptr, 0, 0);
				}
				else
				{
					AddPlayer2focus(1);
					if (m_Ai->LikeRangeCheck() && GetPlayer2Shiled() <= 4)
					{
						
						if (m_Player2_Mana > 0)
						{
							AddPlayer2Mana(-1);
							AddPlayer2Shiled(1);
						}
					}
					else
					{
						
						if (GetPlayer2Shiled() > 0)
						{
							AddPlayer2Shiled(-100);
							AddRange(1);
						}

					}
				}
				break;
				// 부채 뒤집기
			case 4:
				if (player == 1)
				{
					if (GetDust() > 0 && GetPlayer1Shiled() <= 4)
					{
						AddDust(-1);
						AddPlayer1Shiled(1);
					}
					if (GetDust() > 0 && GetPlayer1Shiled() <= 4)
					{
						AddDust(-1);
						AddPlayer1Shiled(1);
					}
					if (m_vecPlayer2_Use.size() != 0 || m_vecPlayer2_Back.size() != 0)
						m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Player1Hero8card4, nullptr, 0, 0);
					
				}
				else
				{	
					tempint = 2;
					tempcard  = m_vecPlayer2_Use.back();
					m_vecPlayer2_Use.pop_back();
					while (tempint != 0)
					{
						if (m_vecPlayer2_Use.size() == 0 && m_vecPlayer2_Back.size() == 0)
							break;
						if (m_vecPlayer2_Use.size() > 0)
						{
							m_vecPlayer2_Deck.insert(m_vecPlayer2_Deck.begin(),m_vecPlayer2_Use.back());
							m_vecPlayer2_Use.pop_back();
							--tempint;
							m_GameMapWidget->PushAnimation(Player2DeckNumber);
							continue;
						}
						else if (m_vecPlayer2_Back.size() > 0)
						{
							m_vecPlayer2_Deck.insert(m_vecPlayer2_Deck.begin(), m_vecPlayer2_Back.back());
							m_vecPlayer2_Back.pop_back();
							--tempint;
							m_GameMapWidget->PushAnimation(Player2DeckNumber);
							continue;
						}
					}
					m_vecPlayer2_Use.push_back(tempcard);
					tempcard = nullptr;
					if (GetDust() > 0 && GetPlayer2Shiled() <= 4)
					{
						AddDust(-1);
						AddPlayer2Shiled(1);
					}
					if (GetDust() > 0 && GetPlayer2Shiled() <= 4)
					{
						AddDust(-1);
						AddPlayer2Shiled(1);
					}
				}
				// 전력
				if (player == 1)
				{
					m_Player1MainEnd = true;
				}
				else
				{
					m_Player2MainEnd = true;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (hero)
		{
		case 1:
			switch (normal)
			{
			case 2:
				if (player == 1)
				{
					for (int i = 0; i < 5; ++i)
					{
						if (m_Dust <= 0)
							break;
						if (m_Player1_Shiled >= 5)
							break;
						AddDust(-1);
						AddPlayer1Shiled(1);
					}
			
				}
				else
				{
					for (int i = 0; i < 5; ++i)
					{
						if (m_Dust <= 0)
							break;
						if (m_Player2_Shiled >= 5)
							break;
						AddDust(-1);
						AddPlayer2Shiled(1);
					}
				
				}
				break;
			default:
				break;
			}
			break;
			// 사이네 비장패 율동호극
		case 3:
			switch (normal)
			{
			case 0:
				m_stackUseCard.pop();
				m_bozoCard2->SetPlayer(player);
				m_bozoCard2->SetCardType(Card_Type::Attack);
				m_bozoCard2->AttackCardSetting(3, 5, 2, 2, 0, 0, 0);
				m_bozoCard2->SetHeroIndex(3);
				m_bozoCard2->SetCardIndex(8);
				CreateAttackAiDaeugCheck(m_bozoCard2);
			
				m_bozoCard1->SetPlayer(player);
				m_bozoCard1->SetCardType(Card_Type::Attack);
				m_bozoCard1->AttackCardSetting(4, 5, 1, 1, 0, 0, 0);
				m_bozoCard1->SetHeroIndex(3);
				m_bozoCard1->SetCardIndex(8);
				CreateAttackAiDaeugCheck(m_bozoCard1);
		
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(3, 4, 1, 1, 0, 0, 0);
				m_bozoCard->SetHeroIndex(3);
				m_bozoCard->SetCardIndex(8);
				CreateAttackAiDaeugCheck(m_bozoCard);
				m_stackUseCard.push(m_bozoCard2);
				
				break;
			case 1:
				if (player == 1)
				{
					if (m_Player2_Shiled > 0)
					{
						AddPlayer2Shiled(-100);
						AddRange(1);
					}
					if (m_Player2_Shiled > 0)
					{
						AddPlayer2Shiled(-100);
						AddRange(1);
					}
				}
				else
				{
					if (m_Player1_Shiled > 0)
					{
						AddPlayer1Shiled(-100);
						AddRange(1);
					}
					if (m_Player1_Shiled > 0)
					{
						AddPlayer1Shiled(-100);
						AddRange(1);
					}
				}
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (normal)
			{
			case 3:
				if (player == 1)
				{
					SetPlayer1focus(2);
					SetPlayer2focus(0);
					m_AiPress = true;
				}
				else
				{	
					
					SetPlayer1focus(0);
					SetPlayer2focus(2);
					m_Player1Press = true;
				}
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

void CGameMapObj::UseSpellBYIndex(int player, CCard* card)
{
	int Hero = card->GetHeroIndex();
	int Cardindex = card->GetCardIndex();
	Card_Class CardClass = card->GetCardClass();
	int SpellTriger = ((CSpellCard*)card)->GetSpellTriger();
	UseSpellBYIndex(player, Hero, Cardindex, CardClass, SpellTriger);
}

void CGameMapObj::UseDaeugBYCard(CCard* card)
{
	CCard* tempcard;

	if (card->GetCardClass() == Card_Class::Normal)
	{

		switch (card->GetHeroIndex())
		{
			// 유리나
		case 1:
			switch (card->GetCardIndex())
			{
			
				
			default:
				break;
			}
			break;
			// 사이네
		case 3:
			switch (card->GetCardIndex())
			{
			case 5:
				--m_buff_Shiled_Attack;
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (card->GetCardIndex())
			{
			case 1:
				tempcard = m_stackUseCard.top();
				m_stackUseCard.pop();
				if (tempcard->GetPlayer() == 1)
				{
					if (GetPlayer1focus() == 2)
					{

						// 비장패일때는 무효화안되게 만들기
						if (m_stackUseCard.top()->GetCardClass() == Card_Class::Normal)
						{
							m_TenreokuCheckPlayer2++;
							m_stackUseCard.pop();
						}
							
					}
				}
				else
				{
					if (GetPlayer2focus() == 2)
					{
						if (m_stackUseCard.top()->GetCardClass() == Card_Class::Normal)
						{
							m_TenreokuCheck++;
							m_stackUseCard.pop();
						}
						
					}
				}
				m_stackUseCard.push(tempcard);
				
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
	else
	{
		switch (card->GetHeroIndex())
		{
		case 1:
			switch (card->GetCardIndex())
			{
			case 1:
				--m_buff_Shiled_Attack;
				--m_buff_Shiled_Attack;
				break;	
			default:
				break;
			}
			break;
			// 사이네
		case 3:
			switch (card->GetCardIndex())
			{
			case 2:
				--m_buff_Shiled_Attack;
				--m_buff_Life_Attack;
				break;
			default:
				break;
			}
			break;
			// 토코요
		case 8:
			switch (card->GetCardIndex())
			{
				// 영원의 꽃
			case 0:
				tempcard = m_stackUseCard.top();
				m_stackUseCard.pop();
				if (card->GetPlayer() == 1)
				{
					
					m_TenreokuCheckPlayer2++;
					m_stackUseCard.pop();
					
				}
				else
				{
					
					m_TenreokuCheck++;
					m_stackUseCard.pop();				
					
				}
				m_stackUseCard.push(tempcard);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

bool CGameMapObj::AttackUseCard(int Player, class CAttackCard* attackcard)
{
	
	int ManaCost = attackcard->GetManaCosT();
	Card_Class CardClass = attackcard->GetCardClass();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	// 카드효과로 버프주는곳
	
	// 플레이어 1일떄
	AttackInfo tempat = AttackCardDamageCalculate(attackcard->GetMin(), attackcard->GetMax(), attackcard->GetDSh(), attackcard->GetDLi(), attackcard->GetHeroIndex(), Player);
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
	int	RangeMin = tempat.Min;
	int RangeMax = tempat.Max;
	int ShieldDamage = tempat.sh;
	int LifeDamage = tempat.li;
	ManaCost = attackcard->GetManaCosT();
	

	if (RangeMin <= m_Range && m_Range <= RangeMax)
	{

		/*if (CardClass == Card_Class::Hero)
		{
			if (Player == 1)
			{
				if (ManaCost <= m_Player1_Mana)
				{
					m_Player1_Mana -= ManaCost;
					m_Dust += ManaCost;
				}
				else
				{
					m_chogeok = 0;
					m_SelectTiming = false;
					return false;
				}
			}
			else
			{
				if (ManaCost <= m_Player2_Mana)
				{
					m_Player2_Mana -= ManaCost;
					m_Dust += ManaCost;
				}
				else
				{
					
				}
			}

		}*/
		
	}
	else
	{
		PushAnimationCard2(0, 6, Card_Class::Normal);
		m_chogeok = 0;
		m_SelectTiming = false;
		return false;
	}
	return CreateAttack(Player, RangeMin, RangeMax, ShieldDamage, LifeDamage, attackcard->GetHeroIndex(), attackcard->GetCardIndex(),attackcard->GetDaeugbool(), attackcard->GetCardClass(), attackcard);
	
}

void CGameMapObj::buffreset()
{
	m_buff_Range_Min	   =0;
	m_buff_Don_Daeug	   =0;
	m_buff_Shiled_Attack  =0;
	m_buff_Life_Attack	   =0;

	//m_other_buff1.buff1 = 0;
	//m_other_buff1.buff2 = 0;
	//m_other_buff1.HeroIndex = 0;
	//m_other_buff2.HeroIndex = 0;
	//m_other_buff2.buff1 = 0;
	//m_other_buff2.buff2 = 0;

}

void CGameMapObj::Player1Gaesi()
{
	
	AddPlayer1focus(1);
	/// <summary>
	/// 원래는 선택해서 부여패를 떄게 해야함 나중에 추가예정
	/// </summary>
	Player1GaesiBuilding();
	Player2GaesiBuilding();
	Player1BuildingSetPos();
	m_TenreokuCheck = 0;



	m_GaeSiPhaseWidget->ClickForwardBytype(GameMapButtonType::Gaeshi, nullptr, 0, 0);
}

void CGameMapObj::Player1GaesiBuilding()
{
	size_t Player1Building = m_vecPlayer1_Building.size();
	for (int i = 0; i < Player1Building; ++i)
	{
		CCard* tempcard = m_vecPlayer1_Building[i];
		((CBuildingCard*)tempcard)->AddNabPoint(-1);
		AddDust(1);
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			UseBuildingBreakBYIndex(1, tempcard->GetHeroIndex(), tempcard->GetCardIndex(), tempcard->GetCardClass());
		}
	}

	/// <summary>
	/// /////////////////////
	/// </summary>
	/// 
	for (int i = 0; i < m_vecPlayer1_Building.size(); ++i)
	{
		CCard* tempcard = m_vecPlayer1_Building[i];
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			((CBuildingCard*)tempcard)->SetUse(false);
			tempcard->SettingGone();
			if (tempcard->GetCardClass() == Card_Class::Hero)
			{
				m_vecPlayer1_HeorUse.push_back(tempcard);
			}
			else
			{
				m_vecPlayer1_Use.push_back(tempcard);
			}
			m_vecPlayer1_Building.erase(m_vecPlayer1_Building.begin() + i);
			--i;
		}
	}
}

void CGameMapObj::Player2GaesiBuilding()
{
	size_t Player2Building = m_vecPlayer2_Building.size();
	for (int i = 0; i < Player2Building; ++i)
	{
		CCard* tempcard = m_vecPlayer2_Building[i];
		((CBuildingCard*)tempcard)->AddNabPoint(-1);
		AddDust(1);
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			UseBuildingBreakBYIndex(2, tempcard->GetHeroIndex(), tempcard->GetCardIndex(), tempcard->GetCardClass());
		}
	}

	/// <summary>
	/// /////////////////////
	/// </summary>
	for (int i = 0; i < m_vecPlayer2_Building.size(); ++i)
	{
		CCard* tempcard = m_vecPlayer2_Building[i];
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			((CBuildingCard*)tempcard)->SetUse(false);
			tempcard->SettingGone();
			if (tempcard->GetCardClass() == Card_Class::Hero)
			{
				m_vecPlayer2_HeorUse.push_back(tempcard);
			}
			else
			{
				m_vecPlayer2_Use.push_back(tempcard);
			}
			tempcard->SetBack();
			m_vecPlayer2_Building.erase(m_vecPlayer2_Building.begin() + i);
			--i;
		}
	}

}

void CGameMapObj::UseBuildingBreakBYIndex(int player, int hero, int normal, Card_Class cardclass)
{
	if (cardclass == Card_Class::Normal)
	{

		switch (hero)
		{
		// 유리나
		case 1:
			switch (normal)
			{
			case 6:
				if (player == 1)
				{
					m_Hero1_Card6_Normal = 0;
				}
				else
				{
					m_Hero1_Card6_Normal_Player2 = 0;
				}
				
				break;
			case 5:
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(1, 4, 3, -1, 0, 0, 0);
				m_bozoCard->SetHeroIndex(1);
				m_bozoCard->SetCardIndex(5);
				CreateAttackAiDaeugCheck(m_bozoCard);
				
			//	CreateAttack(player, 1, 4, 3, -1, hero, 0);
				
				break;
			default:
				break;
			}
			break;

			// 사이네
		case 3:
			switch (normal)
			{
			case 4:
				if (player == 1)
				{
					AddDALINRange(-1);
					m_Hero3_Card4_Normal = 0;
				}
				else
				{
					AddDALINRange(-1);
					m_Hero3_Card4_Normal_Player2 = 0;
				}
				break;
			// 충음정
			// 파기시 공격 생성 후 더스트 -> 간격
			case 5:
				if(m_stackUseCard.size() > 0)
					m_stackUseCard.pop();
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(0, 10, 1, -1, 0, 0, 0);
				++m_buff_Don_Daeug;
				m_bozoCard->SetHeroIndex(3);
				m_bozoCard->SetCardIndex(5);
				CreateAttackAiDaeugCheck(m_bozoCard);
				m_stackUseCard.push(m_bozoCard);
			
				AddDust(-1);
				AddRange(1);
				break;
			case 6:
				if (player == 1)
					m_Hero3_Card6_Normal = false;
				else
					m_Hero3_Card6_Normal_Player2 = false;
				break; 
			default:
				break;
			}
			break;
			// 토코요
		case 8:
			switch (normal)
			{
				// 바람의 무대
			case 5:
				if (player == 1)
				{
					if (GetRange() < 10 && GetPlayer1Shiled() > 0)
					{
						AddRange(1);
						AddPlayer1Shiled(-100);
					}
					if (GetRange() > 0 && GetPlayer1Shiled() < 5)
					{
						AddRange(1);
						AddPlayer1Shiled(-100);
					}
				}
				else
				{
					if (GetRange() > 0 && GetPlayer2Shiled() < 5)
					{
						AddRange(1);
						AddPlayer2Shiled(-100);
					}
					if (GetRange() > 0 && GetPlayer2Shiled() < 5)
					{
						AddRange(1);
						AddPlayer2Shiled(-100);
					}
				}
				break;
				// 맑음의 무대
			case 6:
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(3, 6, -1, 1, 0, 0, 0);
				m_bozoCard->SetHeroIndex(8);
				m_bozoCard->SetCardIndex(6);
				CreateAttackAiDaeugCheck(m_bozoCard);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{

	}
}

void CGameMapObj::UseBuildingBreakBYIndex(int player, CCard* card)
{
	int Hero = card->GetHeroIndex();
	int Cardindex = card->GetCardIndex();
	Card_Class CardClass = card->GetCardClass();
	UseBuildingBreakBYIndex(player, Hero, Cardindex, CardClass);
}

bool CGameMapObj::CreateAttack(int player, int min, int max, int sh, int li, int hero, int normal, int dondaeug, Card_Class cardclass,CAttackCard* card)
{

	//////////////////////////////////////////////////////////////////////////////////////////////

	int RangeMin = min;
	int RangeMax = max;
	int ShieldDamage = sh;
	int LifeDamage = li;
	int HeroIndex = hero;


	int buffShiled = 0;
	if (player == 1)
	{
		if (m_Hero3_Card6_Normal_Player2)
		{
			for (int i = 0; i < m_vecPlayer2_Building.size(); ++i)
			{
				if (m_vecPlayer2_Building[i]->GetCardIndex() == 6 && m_vecPlayer2_Building[i]->GetHeroIndex() == 3)
				{
					CCard* card;
					card = m_vecPlayer2_Building[i];
					CBuildingCard* tempbuidling = (CBuildingCard*)card;
					
					buffShiled = tempbuidling->GetNab();
				}
			}
		}
	}
	else
	{
		if (m_Hero3_Card6_Normal)
		{
			for (int i = 0; i < m_vecPlayer1_Building.size(); ++i)
			{
				if (m_vecPlayer1_Building[i]->GetCardIndex() == 6 && m_vecPlayer1_Building[i]->GetHeroIndex() == 3)
				{
					CCard* card;
					card = m_vecPlayer1_Building[i];
					CBuildingCard* tempbuidling = (CBuildingCard*)card;

					buffShiled = tempbuidling->GetNab();
				}
			}
		}
	}
	


	if (player == 1)
	{

		if (RangeMin <= m_Range && m_Range <= RangeMax)
		{

			if (sh == -1)
			{
				if (LifeDamage > 0)
					m_player2_teum = true;
				AddPlayer2Life(-LifeDamage);
				AddPlayer2Mana(LifeDamage);
				
				if (m_Player2_Life < 0)
					AddPlayer2Mana(m_Player2_Life);
					
			}
			else if (li == -1)
			{
				AddPlayer2Shiled(-ShieldDamage);
				AddDust(ShieldDamage);
			
				if (m_Player2_Shiled <= 0)
				{
					m_Dust += m_Player2_Shiled;
					m_Player2_Shiled = 0;
				}



			}
			/// <summary>
			///  여기서부터 AI 오라 or 라이프 선택
			/// </summary>
			/// <param name="card"></param>
			/// <returns></returns>
			///
			else if (m_Player2_Shiled+ buffShiled >= ShieldDamage)
			{	
				if ((LifeDamage == 1 && ShieldDamage >= 3) || LifeDamage == 0)
				{
					AddPlayer2Life(-LifeDamage);
					AddPlayer2Mana(LifeDamage);
				}
				else
				{
					AddPlayer2Shiled(-ShieldDamage);
					AddDust(ShieldDamage);
				}
				
			}
			else
			{
				if (m_Player2_Life < LifeDamage)
				{	
					if (LifeDamage > 0)
						m_player2_teum = true;
					AddPlayer2Life(-m_Player2_Life);
					AddPlayer2Mana(m_Player2_Life);

				}
				else
				{
					if (LifeDamage > 0)
						m_player2_teum = true;
					AddPlayer2Life(-LifeDamage);
					AddPlayer2Mana(LifeDamage);
					
				}
			}

			AttackEndEffect(player, hero, normal, cardclass);
			m_chogeok = 0;
		
			return true;
		}
		else
		{	
			PushAnimationCard2(0,6,Card_Class::Normal);
			m_chogeok = 0;
			return false;
			// 공격거리안됨
		}
	}
	else
	{

		if (RangeMin <= m_Range && m_Range <= RangeMax)
		{

			if (sh == -1)
			{
				if (LifeDamage > 0)
					m_player1_teum = true;
				AddPlayer1Life(-LifeDamage);
				AddPlayer1Mana(LifeDamage);
			}
			else if (li == -1)
			{
				AddPlayer1Shiled(-ShieldDamage);
				AddDust(ShieldDamage);
			

				if (m_Player1_Shiled <= 0)
				{
					AddDust(m_Player1_Shiled);
					m_Player1_Shiled = 0;
				}



			}
			/// <summary>
			///  여기서부터 AI 오라 or 라이프 선택
			/// </summary>
			/// <param name="card"></param>
			/// <returns></returns>
			else if (m_Player1_Shiled+buffShiled >= ShieldDamage)
			{
				m_bozoCard10 = card;
				m_player1_Attackselect = true;
				m_player1_AttackSelectShiledtemp = ShieldDamage;
				m_player1_AttackSelectLifetemp = LifeDamage;
				m_chogeok = 0;
				m_SelectTiming = false;
			
				return true;
			}
			else
			{
				if (m_Player1_Life < LifeDamage)
				{
					if (LifeDamage > 0)
						m_player1_teum = true;
					AddPlayer1Life(-m_Player1_Life);
					AddPlayer1Mana(m_Player1_Life);
					
				}
				else
				{
					if (LifeDamage > 0)
						m_player1_teum = true;
					AddPlayer1Life(-LifeDamage);
					AddPlayer1Mana(LifeDamage);
				
				}
			}

			AttackEndEffect(player, hero, normal, cardclass);
			m_chogeok = 0;
		
			m_SelectTiming = false;
			return true;
		}
		else
		{
			PushAnimationCard2(0, 6, Card_Class::Normal);
			m_chogeok = 0;
			m_SelectTiming = false;
			return false;
			// 공격거리안됨
		}
	}




}

void CGameMapObj::UseBuildingBYIndex(int player, int hero, int normal, Card_Class cardclass)
{
	
	if (cardclass == Card_Class::Normal)
	{

		switch (hero)
		{
			// 유리나
		case 1:
			switch (normal)
			{
			case 6:
				if (player == 1)
				{
					m_Hero1_Card6_Normal = 1;
					m_Player1MainEnd = true;
				}
				else
				{
					m_Hero1_Card6_Normal_Player2 = 1;
					m_Player2MainEnd = true;

				}
				// 전력!
			
				break;
			default:
				break;
			}
			break;
			// 사이네
		case 3:
			switch (normal)
			{
			case 4:
				if(player == 1)
					m_Hero3_Card4_Normal = 1;
				else
					m_Hero3_Card4_Normal_Player2 = 1;

				AddDALINRange(1);
				break;
				// 무음벽 전력 이거 오라공격맞을떄마다 어질어질하네...
			case 6:
				if (player == 1)
				{
					m_Hero3_Card6_Normal = true;
					m_Player1MainEnd = true;
				}	
				else
				{
					m_Hero3_Card6_Normal_Player2 = true;
					m_Player2MainEnd = true;
				}
				break;
			default:
				break;
			}
			break;
			// 토코요
		case 8:
			switch (normal)
			{
				// 바람의 무대
			case 5:
				if (player == 1)
				{
					if (GetRange() > 0 && GetPlayer1Shiled() < 5)
					{
						AddRange(-1);
						AddPlayer1Shiled(1);
					}
					if (GetRange() > 0 && GetPlayer1Shiled() < 5)
					{
						AddRange(-1);
						AddPlayer1Shiled(1);
					}
				}
				else
				{
					if (GetRange() > 0 && GetPlayer2Shiled() < 5)
					{
						AddRange(-1);
						AddPlayer2Shiled(1);
					}
					if (GetRange() > 0 && GetPlayer2Shiled() < 5)
					{
						AddRange(-1);
						AddPlayer2Shiled(1);
					}
				}
				break;
			case 6:
				
				// 종단
				if (player == 1)
				{
					SetPlayer1focus(2);
			
					m_Player1MainEnd = true;
				}
				else
				{
					SetPlayer2focus(2);
				
					m_Player2MainEnd = true;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{

	}
}

void CGameMapObj::UseBuildingBYIndex(int player, CCard* card)
{
	int Hero = card->GetHeroIndex();
	int Cardindex = card->GetCardIndex();
	Card_Class CardClass = card->GetCardClass();
	UseBuildingBYIndex(player, Hero, Cardindex, CardClass);
}

void CGameMapObj::Player2End()
{
	while(m_vecPlayer2_Hand.size() > 2)
	{
		m_vecPlayer2_Back.push_back(m_vecPlayer2_Hand[0]);
		//LogCreate(m_vecPlayer2_Hand[0],nullptr,2,2);
		m_vecPlayer2_Hand[0]->SettingGone();
		m_vecPlayer2_Hand.erase(m_vecPlayer2_Hand.begin());
	}
}

void CGameMapObj::AttackonTheStack(CAttackCard* attackcard)
{	
	// 애니메이션 없는 버젼
	m_stackUseCard.push(attackcard);

}

void CGameMapObj::UseBuildingUsingBYIndex(int hero, int normal, Card_Class cardclass)
{

}

void CGameMapObj::AiMainPhase()
{
	m_Ai->AiHandtoBack();
}

void CGameMapObj::AiHandEnable()
{
}

void CGameMapObj::Player1Mainend()
{
}

void CGameMapObj::Player2Mainend()
{
}

AttackInfo CGameMapObj::AttackCardDamageCalculate(int min, int max,int sh,int li,int hero, int player)
{

	int RangeMin = min;
	int RangeMax = max;
	int ShieldDamage = sh;
	int LifeDamage = li;
	int HeroIndex = hero;
	if (player == 1)
	{
		if (m_Hero1_Card6_Normal)
		{
			// 유리나 인덱스가 1 
			// 당신의 다른 여신에 의한 공격 +1/+1이 되고 초극을 얻는다.
			if (HeroIndex != 1)
			{
				m_chogeok = 1;

				if (ShieldDamage != -1)
					m_buff_Shiled_Attack++;
				if (LifeDamage != -1)
					m_buff_Life_Attack++;


			}
		}
		if (m_Hero1_Card4_Normal)
		{
			if (HeroIndex != 1)
			{
				m_buff_Don_Daeug = 1;
				m_buff_Range_Min++;
			
				m_Hero1_Card4_Normal = false;
			}
		}
	}
	else
	{
		if (m_Hero1_Card6_Normal_Player2)
		{
			// 유리나 인덱스가 1 
			// 당신의 다른 여신에 의한 공격 +1/+1이 되고 초극을 얻는다.
			if (HeroIndex != 1)
			{
				m_chogeok = 1;

				if (ShieldDamage != -1)
					m_buff_Shiled_Attack++;
				if (LifeDamage != -1)
					m_buff_Life_Attack++;


			}
		}
		if (m_Hero1_Card4_Normal_Player2)
		{
			if (HeroIndex != 1)
			{
				m_buff_Don_Daeug = 1;
				m_buff_Range_Min++;
				if (!m_player1_Attackselect)
					m_Hero1_Card4_Normal_Player2 = false;


			}
		}
	}

	RangeMin = min - m_buff_Range_Min;
	RangeMax = max;
	if (sh != -1)
	{	
		if (sh + m_buff_Shiled_Attack <= 0)
			ShieldDamage = 0;
		else
			ShieldDamage = sh + m_buff_Shiled_Attack;
	}
	else
		ShieldDamage = -1;

	if (li != -1)
	{
		if (li + m_buff_Life_Attack <= 0)
			LifeDamage = 0;
		else
			LifeDamage = li + m_buff_Life_Attack;
	}
	else
		LifeDamage = -1;

	



	AttackInfo at;
	
	at.Min = RangeMin;
	at.Max = RangeMax;
	at.sh = ShieldDamage;
	if (m_chogeok <= 0 && ShieldDamage >= 5)
		at.sh = 5;
	at.li = LifeDamage;
	buffreset();
	return at;
	
}

bool CGameMapObj::Player1Daueg(CCard* card)                  
{
	if (GetPlayer1MainEnd() == true)
		return false;
	int daeugcount = 0;


	for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
	{
		// 사이네 간파 
		// 팔상일때 대응처럼 사용가능
		if (m_vecPlayer1_Hand[i]->GetCardIndex() == 3 && m_vecPlayer1_Hand[i]->GetHeroIndex() == 3)
		{
			if (m_Player1_Shiled <= 1)
			{
				m_vecPlayer1_Hand[i]->SetSelectTime(true);
				m_vecPlayer1_Hand[i]->SetMove(false);
				++daeugcount;
				continue;
			}
		}


		if (m_vecPlayer1_Hand[i]->GetDaeung() > 0)
		{	
			CCard* tempcard = m_vecPlayer1_Hand[i];
			switch (m_vecPlayer1_Hand[i]->GetCardType())
			{
			case Card_Type::Attack:
				if (Player1UseAttackCard((CAttackCard*)tempcard))
				{
					m_vecPlayer1_Hand[i]->SetSelectTime(true);
					m_vecPlayer1_Hand[i]->SetMove(false);
					++daeugcount;
				
				}
				break;
			case Card_Type::Spell:
				if (Player1UseSpellCard((CSpellCard*)tempcard))
				{
					m_vecPlayer1_Hand[i]->SetSelectTime(true);
					m_vecPlayer1_Hand[i]->SetMove(false);
					++daeugcount;
					
				}
				break;
			case Card_Type::Building:
				if (Player1UseBuildingCard((CBuildingCard*)tempcard))
				{
					m_vecPlayer1_Hand[i]->SetSelectTime(true);
					m_vecPlayer1_Hand[i]->SetMove(false);
					++daeugcount;
				}
				break;
			default:
				break;
			}

		}
	}
	

	for (int i = 0; i < m_vecPlayer1_Hero.size(); ++i)
	{

		if (m_vecPlayer1_Hero[i]->GetCardIndex() == 3 && m_vecPlayer1_Hero[i]->GetHeroIndex() == 3)
		{
			CCard* tempcard = m_vecPlayer1_Hero[i];
			if (card->GetCardClass() == Card_Class::Hero && Player1UseAttackCard((CAttackCard*)tempcard))
			{
			
				m_vecPlayer1_Hero[i]->SetSelectTime(true);
				m_vecPlayer1_Hero[i]->SetMove(false);
				++daeugcount;
			}
			else
			{
				continue;
			}
		}






		if (m_vecPlayer1_Hero[i]->GetDaeung() > 0)
		{
			CCard* tempcard = m_vecPlayer1_Hero[i];
			switch (m_vecPlayer1_Hero[i]->GetCardType())
			{
			case Card_Type::Attack:
				if (Player1UseAttackCard((CAttackCard*)tempcard))
				{
					m_vecPlayer1_Hero[i]->SetSelectTime(true);
					m_vecPlayer1_Hero[i]->SetMove(false);
					++daeugcount;
				}
				break;
			case Card_Type::Spell:
				if (Player1UseSpellCard((CSpellCard*)tempcard))
				{
					m_vecPlayer1_Hero[i]->SetSelectTime(true);
					m_vecPlayer1_Hero[i]->SetMove(false);
					++daeugcount;
			
				}
				break;
			case Card_Type::Building:
				if (Player1UseBuildingCard((CBuildingCard*)tempcard))
				{
					m_vecPlayer1_Hero[i]->SetSelectTime(true);
					m_vecPlayer1_Hero[i]->SetMove(false);
					++daeugcount;
					
				}
				break;
			default:
				break;
			}

		}
	}






	
	
	return daeugcount > 0;
}

bool CGameMapObj::AiDaueg()
{
	return false;
}

void CGameMapObj::Player1OpenDauegButton(class CAttackCard* card)
{
	m_stackCreateAttackCard.push(card);

}

void CGameMapObj::Player1DauegExit(CCard* card)
{

	if (card != nullptr)
	{
		if (card->GetCardClass() == Card_Class::Normal)
		{
			auto iter = m_vecPlayer1_Hand.begin();
			auto iterend = m_vecPlayer1_Hand.end();
			for (; iter != iterend; ++iter)
			{
				if ((*iter) == card)
				{	
					if ((*iter)->GetCardType() == Card_Type::Building)
					{
						m_vecPlayer1_Building.push_back(*iter);
						(*iter)->SetRelativePos(620.f, 360.f, 0.f);
						(*iter)->SetStartHandPos(Vector3(620.f, 360.f, 0.f));
						(*iter)->SetMove(false);
					}
						
					else
						m_vecPlayer1_Use.push_back(*iter);

					card->SettingGone();
					m_vecPlayer1_Hand.erase(iter);
					break;
				}
			}
		}
		else
		{
			auto iter = m_vecPlayer1_Hero.begin();
			auto iterend = m_vecPlayer1_Hero.end();
			for (; iter != iterend; ++iter)
			{
				if ((*iter) == card)
				{
					if ((*iter)->GetCardType() == Card_Type::Building)
					{
						(*iter)->SetSelectTime(false);
						(*iter)->SetSelect(false);
						(*iter)->UnSellectTextureSetting();
						(*iter)->SetRelativePos(620.f, 360.f, 0.f);
						(*iter)->SetStartHandPos(Vector3(620.f, 360.f, 0.f));
						(*iter)->SetMove(false);
						m_vecPlayer1_Building.push_back(*iter);
					}
					else
						m_vecPlayer1_HeorUse.push_back(*iter);

					card->SettingGone();
					m_vecPlayer1_Hero.erase(iter);
					break;
				}
			}
		}
	}
	
	HandSortSetting();
}

void CGameMapObj::UseCard(CCard* card)
{
//	
	m_stackUseCard.push(card);


}

void CGameMapObj::SetDauegAnimation()
{
	m_AnimationCard->SetAnimIndex(2);
}
// 공격 후 효과 적는곳
void CGameMapObj::AttackEndEffect(int player, int hero, int normal,Card_Class cardclass)
{
	m_pScene->GetResource()->SoundPlay("Oraattacksound");
	// 사이네 팔방 휘두르기
	if (hero == 3 && normal == 0 && cardclass == Card_Class::Normal)
	{
		if (player == 1)
		{
			if (m_Player1_Shiled <= 1)
			{
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(4, 5, 2, 1, 0, 0, 0);
				m_bozoCard->SetHeroIndex(3);
				m_bozoCard->SetCardIndex(7);
				if (m_stackUseCard.size() > 0)
					m_stackUseCard.pop();
				CreateAttackAiDaeugCheck(m_bozoCard);
				m_stackUseCard.push(m_bozoCard);
			
			}
		}
		else
		{
			if (m_Player2_Shiled <= 1)
			{
				m_bozoCard->SetPlayer(player);
				m_bozoCard->SetCardType(Card_Type::Attack);
				m_bozoCard->AttackCardSetting(4, 5, 2, 1, 0, 0, 0);
				m_bozoCard->SetHeroIndex(3);
				m_bozoCard->SetCardIndex(7);
				if (m_stackUseCard.size() > 0)
					m_stackUseCard.pop();
				CreateAttackAiDaeugCheck(m_bozoCard);
				m_stackUseCard.push(m_bozoCard);
				
			}
		}
		
	}

	if (hero == 3 && normal == 2 && cardclass == Card_Class::Normal)
	{
		if (player == 1)
		{
			if (m_Player1_Shiled <= 1)
			{
				if (m_Dust > 0 && m_Range < 10)
				{
					AddDust(-1);
					AddRange(1);
				}
			}
		}
		else
		{
			if (m_Player2_Shiled <= 1)
			{
				if (m_Dust > 0 && m_Range < 10)
				{
					AddDust(-1);
					AddRange(1);
				}
			}
		}

	}
	// 토코요  빗어내리기
	if (hero == 8 && normal == 0 && cardclass == Card_Class::Normal)
	{
		if (player == 1)
		{
			if (GetPlayer1focus() == 2)
			{
				m_GameMapWidget->PushAnimation(Player1DeckNumber);
				m_vecPlayer1_Deck.push_back(m_vecPlayer1_Use.back());
				m_vecPlayer1_Use.pop_back();
			}
		}
		else
		{
			if (GetPlayer2focus() == 2)
			{
				m_GameMapWidget->PushAnimation(Player1DeckNumber);
				m_vecPlayer2_Deck.push_back(m_vecPlayer2_Use.back());
				m_vecPlayer2_Use.pop_back();
			}
		}

	}
	// 토코요  천년의새
	if (hero == 8 && normal == 1 && cardclass == Card_Class::Hero)
	{
		if (player == 1)
		{
			RefreshFree();
		}
		else
		{
			Refresh2Free();
			
		}

	}
	// 토코요 무궁의바람
	if (hero == 8 && normal == 2 && cardclass == Card_Class::Hero)
	{	
		int tempbool = 0;
		if (player == 1)
		{
			for (int i = 0; i < m_vecPlayer2_Hand.size(); ++i)
			{
				if (m_vecPlayer2_Hand[i]->GetCardType() != Card_Type::Attack)
				{
					m_vecPlayer2_Hand[i]->SettingGone();
					m_vecPlayer2_Hand[i]->SetSelect(false);
					LogCreate(m_vecPlayer2_Hand[i], nullptr, 2, 2);
					m_vecPlayer2_Use.push_back(m_vecPlayer2_Hand[i]);
					m_vecPlayer2_Hand.erase(m_vecPlayer2_Hand.begin() + i);
					
					++tempbool;
					break;
				}
			}
			if (tempbool == 0)
			{
				for (int i = 0; i < m_vecPlayer2_Hand.size(); ++i)
				{
					m_vecPlayer2_Hand[i]->CreateTex();
				}
			}
		}
		else
		{
			Player1HeroDeckUnSellectTime();
			tempbool = 0;
			for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
			{
				if (m_vecPlayer1_Hand[i]->GetCardType() != Card_Type::Attack)
				{
					++tempbool;
				}
			}
			if (tempbool == 1)
			{
				for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
				{
					if (m_vecPlayer1_Hand[i]->GetCardType() != Card_Type::Attack)
					{
						LogCreate(m_vecPlayer1_Hand[i], nullptr, 2, 1);
						m_vecPlayer1_Hand[i]->SettingGone();
						m_vecPlayer1_Hand[i]->SetSelect(false);
						m_vecPlayer1_Use.push_back(m_vecPlayer1_Hand[i]);
						m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
			
						break;
					}
				}
			}
			else if (tempbool >= 2)
			{
				for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
				{
					if (m_vecPlayer1_Hand[i]->GetCardType() != Card_Type::Attack)
					{
						m_vecPlayer1_Hand[i]->SetSelect(false);
						m_vecPlayer1_Hand[i]->SetSelectTime(true);
						
					}
				}
				m_GaeSiPhaseWidget->ClickCardBurn(1);
			}

		}

	}
	
}

// 재기 체크
void CGameMapObj::Turnendbuffreset(int player)
{
	buffreset();
	// 무음쇄빙 사이네3 비장패2
	if (player == 1)
	{	// 오라 1이하일떄
		if (m_Player1_Shiled <= 1)
		{
			for (int i = 0; i < m_vecPlayer1_HeorUse.size(); ++i)
			{	// 무음쇄빙
				if (m_vecPlayer1_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer1_HeorUse[i]->GetHeroIndex() == 3)
				{
					m_LogObj->CreateLog(m_vecPlayer1_HeorUse[i],nullptr,1,1);
					m_vecPlayer1_HeorUse[i]->SetUse(false);
					m_vecPlayer1_Hero.push_back(m_vecPlayer1_HeorUse[i]);
					m_vecPlayer1_HeorUse.erase(m_vecPlayer1_HeorUse.begin() + i);
				
					break;
				}
			}
		}
		if (m_Player1_focus == 2)
		{
			for (int i = 0; i < m_vecPlayer1_HeorUse.size(); ++i)
			{	// 무궁의바람
				if (m_vecPlayer1_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer1_HeorUse[i]->GetHeroIndex() == 8)
				{
					m_LogObj->CreateLog(m_vecPlayer1_HeorUse[i], nullptr, 1, 1);
					m_vecPlayer1_HeorUse[i]->SetUse(false);
					m_vecPlayer1_Hero.push_back(m_vecPlayer1_HeorUse[i]);
					m_vecPlayer1_HeorUse.erase(m_vecPlayer1_HeorUse.begin() + i);
					break;
				}
			}
		}
	}
	else
	{
		// 오라 1이하일떄
		if (m_Player2_Shiled <= 1)
		{
			for (int i = 0; i < m_vecPlayer2_HeorUse.size(); ++i)
			{	// 무음쇄빙
				if (m_vecPlayer2_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer2_HeorUse[i]->GetHeroIndex() == 3)
				{
					m_LogObj->CreateLog(m_vecPlayer2_HeorUse[i], nullptr, 1, 2);
					m_vecPlayer2_HeorUse[i]->SetUse(false);
					m_vecPlayer2_Hero.push_back(m_vecPlayer2_HeorUse[i]);
					m_vecPlayer2_HeorUse.erase(m_vecPlayer2_HeorUse.begin() + i);
					break;
				}
			}
		}
		// 집중력이 2일떄
		if (m_Player2_focus == 2)
		{
			for (int i = 0; i < m_vecPlayer2_HeorUse.size(); ++i)
			{	// 무궁의바람
				if (m_vecPlayer2_HeorUse[i]->GetCardIndex() == 2 && m_vecPlayer2_HeorUse[i]->GetHeroIndex() == 8)
				{
					m_LogObj->CreateLog(m_vecPlayer2_HeorUse[i], nullptr, 1, 1);
					m_vecPlayer2_HeorUse[i]->SetUse(false);
					m_vecPlayer2_Hero.push_back(m_vecPlayer2_HeorUse[i]);
					m_vecPlayer2_HeorUse.erase(m_vecPlayer2_HeorUse.begin() + i);
					break;
				}
			}
		}
	}




	m_Player1MainEnd = false;
	m_Player2MainEnd = false;
	++m_turn;
	// 한턴동안만 지속되는 버프 false로 바꿔주기
	m_Hero1_Card4_Normal = false;
	m_Hero1_Card4_Normal_Player2 = false;
}

void CGameMapObj::GaesiStart()
{
	if (m_Hero3_Card4_Normal)
	{
		AddDust(-1);
		AddRange(1);
	}
	if (m_Hero3_Card4_Normal_Player2)
	{
		AddDust(-1);
		AddRange(1);
	}
}

void CGameMapObj::PlayerHeor3Card6Check(int focus)
{
	m_Hero3_Card6_Normal_UITriger = focus;

}

void CGameMapObj::AiHero3Card6Check(int focus)
{

		if (m_Player2_Shiled == 2)
		{
			focus += 1;
			m_Player2_Shiled -= 1;
		}

		for (int i = 0; i < m_vecPlayer2_Building.size(); ++i)
		{
			if (m_vecPlayer2_Building[i]->GetCardIndex() == 6 && m_vecPlayer2_Building[i]->GetHeroIndex() == 3)
			{
				CCard* card;
				card = m_vecPlayer2_Building[i];
				CBuildingCard* tempbuidling = (CBuildingCard*)card;
				while (focus < 0)
				{
					if (tempbuidling->GetNabpoint() > 0)
						tempbuidling->AddNabPoint(-1);
					else
						m_Player2_Shiled -= 1;


					++focus;
				}
				Player2BuildingZeroCheck();
			}
		}
	

	
}

void CGameMapObj::Player1BuildingZeroCheck()
{
	for (int i = 0; i < m_vecPlayer1_Building.size(); ++i)
	{
		CCard* tempcard = m_vecPlayer1_Building[i];
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			((CBuildingCard*)tempcard)->SetUse(false);
			UseBuildingBreakBYIndex(1, tempcard);
			tempcard->SettingGone();
			if (tempcard->GetCardClass() == Card_Class::Hero)
			{
				m_vecPlayer1_HeorUse.push_back(tempcard);
			}
			else
			{
				m_vecPlayer1_Use.push_back(tempcard);
			}
			m_vecPlayer1_Building.erase(m_vecPlayer1_Building.begin() + i);
			--i;
		}
	}
}

void CGameMapObj::Player2BuildingZeroCheck()
{
	for (int i = 0; i < m_vecPlayer2_Building.size(); ++i)
	{
		CCard* tempcard = m_vecPlayer2_Building[i];
		if (((CBuildingCard*)tempcard)->GetNabpoint() == 0)
		{
			((CBuildingCard*)tempcard)->SetUse(false);
			UseBuildingBreakBYIndex(2, tempcard);
			tempcard->SettingGone();
			if (tempcard->GetCardClass() == Card_Class::Hero)
			{
				m_vecPlayer2_HeorUse.push_back(tempcard);
			}
			else
			{
				m_vecPlayer2_Use.push_back(tempcard);
			}
			tempcard->SetBack();
			m_vecPlayer2_Building.erase(m_vecPlayer2_Building.begin() + i);
			--i;
		}
	}
}

CBuildingCard* CGameMapObj::PlayerHero3Card6()
{
	CBuildingCard* tempbuilding2 = nullptr;
	if (m_Hero3_Card6_Normal)
	{
		for (int i = 0; i < m_vecPlayer1_Building.size(); ++i)
		{
			if (m_vecPlayer1_Building[i]->GetCardIndex() == 6 && m_vecPlayer1_Building[i]->GetHeroIndex() == 3)
			{
				CCard* card;
				card = m_vecPlayer1_Building[i];
				CBuildingCard* tempbuidling = (CBuildingCard*)card;

				return tempbuidling;
			}
		}
	}
	return nullptr;
}



void CGameMapObj::HandSortSetting2()
{
	size_t size2 = m_vecPlayer2_Hand.size();

	for (int i = 0; i < size2; ++i)
	{
		m_vecPlayer2_Hand[i]->SetRelativePos(709.4f - (72.1f * size2) + m_vecPlayer2_Hand[i]->GetRelativeScale().x * i + 10.f, 781.f, 0.f);
		m_vecPlayer2_Hand[i]->SetStartHandPos(m_vecPlayer2_Hand[i]->GetRelativePos());
		m_vecPlayer2_Hand[i]->SetMove(false);
		m_vecPlayer2_Hand[i]->SetUse(false);
		m_vecPlayer2_Hand[i]->SetSelectTime(false);
		m_vecPlayer2_Hand[i]->SetSelect(false);
		m_vecPlayer2_Hand[i]->UnSellectTextureSetting();
		m_vecPlayer2_Hand[i]->SetRender(true);
	}
}

void CGameMapObj::Player1CardManaCost(CCard* card)
{
	if (card->GetCardClass() == Card_Class::Normal)
		return;
	int manabuff = 0;
	if (card->GetCardIndex() == 1 && card->GetHeroIndex() == 3 && card->GetCardClass() == Card_Class::Hero)
	{
		manabuff = m_Player2_Shiled;
	}
	int mana = card->GetManaCosT()- manabuff;

	AddPlayer1Mana(-mana);
	AddDust(mana);
}

void CGameMapObj::AnimationHide()
{
	m_AnimationCard->SettingHide();
}

void CGameMapObj::CreateAttackAiDaeugCheck(CCard* card)
{	
	if (card->GetPlayer() == 1)
	{
		if (Player1UseAttackCard((CAttackCard*)card))
		{
			if (m_Ai->AiDauengCheck((CAttackCard*)card) && m_buff_Don_Daeug == 0&& ((CAttackCard*)card)->GetDaeugbool() == false)
			{

				m_stackUseCard.push(card);
				m_AnimationCard->SetAnimIndex(2);
				LogCreate(card, nullptr, 0, 1);
				LogCreate(m_Ai->AiUseDaueng() , card, 0, 2);
			
				m_Ai->Player1AttackCardSetting((CAttackCard*)card);
			}
			else
			{
				m_buff_Don_Daeug = 0;
				m_stackUseCard.push(card);
				PushAnimationCard(card, 0);
				LogCreate(card,nullptr,0, 1);
			}

		}
	}
	else
	{
		if (Player1Daueg(card) && ((CAttackCard*)card)->GetDaeugbool() == false)
		{
			Player1OpenDauegButton((CAttackCard*)card);

		}
		else
		{
			AttackonTheStack((CAttackCard*)card);
			PushAnimationCard(card,0);
			LogCreate(card, nullptr, 0,2);
		}
	}
	
}

void CGameMapObj::LogCreate(CCard* card, CCard* card2, int index, int player)
{
	m_LogObj->CreateLog(card,card2,index,player);
}

void CGameMapObj::SettingPlayer1Use()
{
	m_CardlistMtrl->AddTexture("MyUseGround", TEXT("MyUseGround.png"));
	m_Cardlist->SetRelativeScale(989.f * 1280.f / 1603.f, 736.f * 720.f / 905.f
		, 0.f);
	size_t vecsize = m_vecPlayer1_Use.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer1_Use[i]->SetRelativePos(151.f + ((i % 4) * 744.f / 4.f / 1.3f * 1.3f), 519.f - ((i / 4) * 1038.f / 4.f / 1.3f * 1.3f), 0.f);
		m_vecPlayer1_Use[i]->SetStartHandPos(m_vecPlayer1_Use[i]->GetRelativePos());
		m_vecPlayer1_Use[i]->SetMove(false);
		m_vecPlayer1_Use[i]->SetUse(false);
	}

}

void CGameMapObj::SettingPlayer1Back()
{
	m_CardlistMtrl->AddTexture("MyBackGround", TEXT("MyBackGround.png"));
	m_Cardlist->SetRelativeScale(989.f * 1280.f / 1603.f, 736.f * 720.f / 905.f
		, 0.f);
	size_t vecsize = m_vecPlayer1_Back.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer1_Back[i]->SetRelativePos(151.f + ((i % 4) * 744.f / 4.f / 1.3f * 1.3f), 519.f - ((i / 4) * 1038.f / 4.f / 1.3f * 1.3f), 0.f);
		m_vecPlayer1_Back[i]->SetStartHandPos(m_vecPlayer1_Back[i]->GetRelativePos());
		m_vecPlayer1_Back[i]->SetMove(false);
		m_vecPlayer1_Back[i]->SetUse(false);
		m_vecPlayer1_Back[i]->SetRenderDefault();
	
		
	}
}

void CGameMapObj::SettingAiUse()
{
	m_CardlistMtrl->AddTexture("AiUseGround", TEXT("AiUseGround.png"));
	m_Cardlist->SetRelativeScale(989.f * 1280.f / 1603.f, 736.f * 720.f / 905.f
		, 0.f);
	size_t vecsize = m_vecPlayer2_Use.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer2_Use[i]->SetRelativePos(151.f + ((i % 4) * 744.f / 4.f / 1.3f * 1.3f), 519.f - ((i / 4) * 1038.f / 4.f / 1.3f * 1.3f), 0.f);
		m_vecPlayer2_Use[i]->SetStartHandPos(m_vecPlayer2_Use[i]->GetRelativePos());
		m_vecPlayer2_Use[i]->SetMove(false);
		m_vecPlayer2_Use[i]->CreateTex();
		m_vecPlayer2_Use[i]->SetUse(false);
		m_vecPlayer2_Use[i]->SetSelectTime(false);
		m_vecPlayer2_Use[i]->UnSellectTextureSetting();
		m_vecPlayer2_Use[i]->SetSelect(false);
	}
}

void CGameMapObj::SettingAiBack()
{
	m_CardlistMtrl->AddTexture("AiBackGround", TEXT("AiBackGround.png"));
	m_Cardlist->SetRelativeScale(989.f * 1280.f / 1603.f, 736.f * 720.f / 905.f
		, 0.f);
	size_t vecsize = m_vecPlayer2_Back.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer2_Back[i]->SetRelativePos(151.f + ((i % 4) * 744.f / 4.f / 1.3f * 1.3f), 519.f - ((i / 4) * 1038.f / 4.f / 1.3f * 1.3f), 0.f);
		m_vecPlayer2_Back[i]->SetStartHandPos(m_vecPlayer2_Back[i]->GetRelativePos());
		m_vecPlayer2_Back[i]->SetMove(false);
		m_vecPlayer2_Back[i]->SetBack();
		m_vecPlayer2_Back[i]->SetUse(false);
		m_vecPlayer2_Back[i]->UnSellectTextureSetting();
		m_vecPlayer2_Back[i]->SetSelect(false);
		m_vecPlayer2_Back[i]->SetSelectTime(false);
	}
}

void CGameMapObj::SettingPlayer1UseBacksellecttime()
{
	size_t vecsize = m_vecPlayer1_Use.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer1_Use[i]->SetSelectTime(true);
		m_vecPlayer1_Use[i]->SetSelect(false);
	}

	size_t vecsize2 = m_vecPlayer1_Back.size();

	for (int i = 0; i < vecsize2; ++i)
	{
		m_vecPlayer1_Back[i]->SetSelectTime(true);
		m_vecPlayer1_Back[i]->SetSelect(false);
	}
}

void CGameMapObj::SettingPlayer1UseBackUnSellecttime()
{
	size_t vecsize = m_vecPlayer1_Use.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer1_Use[i]->UnSellectTextureSetting();
		m_vecPlayer1_Use[i]->SetSelectTime(false);
		m_vecPlayer1_Use[i]->SetSelect(false);
	}

	size_t vecsize2 = m_vecPlayer1_Back.size();

	for (int i = 0; i < vecsize2; ++i)
	{
		m_vecPlayer1_Back[i]->UnSellectTextureSetting();
		m_vecPlayer1_Back[i]->SetSelectTime(false);
		m_vecPlayer1_Back[i]->SetSelect(false);
	}
}

void CGameMapObj::SettingAllgone()
{
	m_Cardlist->SetRelativeScale(0.f,0.f, 0.f);
	size_t vecsize = m_vecPlayer1_Use.size();

	for (int i = 0; i < vecsize; ++i)
	{
		m_vecPlayer1_Use[i]->SetRelativePos(1800.f, 1800.f, 0.f);
		m_vecPlayer1_Use[i]->SetStartHandPos(m_vecPlayer1_Use[i]->GetRelativePos());
		m_vecPlayer1_Use[i]->SetLoopup(false);
	}
	size_t vecsize1 = m_vecPlayer1_Back.size();

	for (int i = 0; i < vecsize1; ++i)
	{
		m_vecPlayer1_Back[i]->SetRelativePos(1800.f, 1800.f, 0.f);
		m_vecPlayer1_Back[i]->SetStartHandPos(m_vecPlayer1_Back[i]->GetRelativePos());
		m_vecPlayer1_Back[i]->SetLoopup(false);
	}

	size_t vecsize2 = m_vecPlayer2_Use.size();

	for (int i = 0; i < vecsize2; ++i)
	{
		m_vecPlayer2_Use[i]->SetRelativePos(1800.f, 1800.f, 0.f);
		m_vecPlayer2_Use[i]->SetStartHandPos(m_vecPlayer2_Use[i]->GetRelativePos());
		m_vecPlayer2_Use[i]->SetBack();
		m_vecPlayer2_Use[i]->SetLoopup(false);
	}
	size_t vecsize3 = m_vecPlayer2_Back.size();

	for (int i = 0; i < vecsize3; ++i)
	{
		m_vecPlayer2_Back[i]->SetRelativePos(1800.f, 1800.f, 0.f);
		m_vecPlayer2_Back[i]->SetStartHandPos(m_vecPlayer2_Back[i]->GetRelativePos());
		m_vecPlayer2_Back[i]->SetBack();
		m_vecPlayer2_Back[i]->SetLoopup(false);
	}
}

int CGameMapObj::SumPlayer2HeroManaCost()
{
	int tempint = 0;
	size_t vecsize2 = m_vecPlayer2_Hero.size();

	for (int i = 0; i < vecsize2; ++i)
	{
		tempint += m_vecPlayer2_Hero[i]->GetManaCosT();
	}
	return tempint;
}

bool CGameMapObj::Hero8Card4(CCard* card,CCard* card1)
{
	if (card == nullptr)
		return false;
	for (int i = 0; i <  m_vecPlayer1_Use.size(); ++i)
	{
		if (m_vecPlayer1_Use[i] == card)
		{
			m_vecPlayer1_Use[i]->SettingGone();
			m_vecPlayer1_Use[i]->UnSellectTextureSetting();
			m_vecPlayer1_Use[i]->SetSelectTime(false);
			m_vecPlayer1_Use[i]->SetSelect(false);
			m_vecPlayer1_Deck.insert(m_vecPlayer1_Deck.begin(), m_vecPlayer1_Use[i]);
			m_vecPlayer1_Use.erase(m_vecPlayer1_Use.begin() + i);
			break;
		}
	}
	for (int i = 0; i < m_vecPlayer1_Back.size(); ++i)
	{
		if (m_vecPlayer1_Back[i] == card)
		{
			m_vecPlayer1_Back[i]->SettingGone();
			m_vecPlayer1_Back[i]->UnSellectTextureSetting();
			m_vecPlayer1_Back[i]->SetSelectTime(false);
			m_vecPlayer1_Back[i]->SetSelect(false);
			m_vecPlayer1_Deck.insert(m_vecPlayer1_Deck.begin(), m_vecPlayer1_Back[i]);
			m_vecPlayer1_Back.erase(m_vecPlayer1_Back.begin() + i);
			break;
		}
	}

	if (card1 == nullptr)
		return false;
	for (int i = 0; i < m_vecPlayer1_Use.size(); ++i)
	{
		if (m_vecPlayer1_Use[i] == card1)
		{
			m_vecPlayer1_Use[i]->SettingGone();
			m_vecPlayer1_Use[i]->UnSellectTextureSetting();
			m_vecPlayer1_Use[i]->SetSelectTime(false);
			m_vecPlayer1_Use[i]->SetSelect(false);
			m_vecPlayer1_Deck.insert(m_vecPlayer1_Deck.begin(), m_vecPlayer1_Use[i]);
			m_vecPlayer1_Use.erase(m_vecPlayer1_Use.begin() + i);
			break;
		}
	}
	for (int i = 0; i < m_vecPlayer1_Back.size(); ++i)
	{
		if (m_vecPlayer1_Back[i] == card1)
		{
			m_vecPlayer1_Back[i]->SettingGone();
			m_vecPlayer1_Back[i]->UnSellectTextureSetting();
			m_vecPlayer1_Back[i]->SetSelectTime(false);
			m_vecPlayer1_Back[i]->SetSelect(false);
			m_vecPlayer1_Deck.insert(m_vecPlayer1_Deck.begin(), m_vecPlayer1_Back[i]);
			m_vecPlayer1_Back.erase(m_vecPlayer1_Back.begin() + i);
			break;
		}
	}

	return true;
}

void CGameMapObj::RefreshFree()
{
	RefreshSound();
	size_t BackSize = m_vecPlayer1_Back.size();
	size_t UseSize = m_vecPlayer1_Use.size();
	if (BackSize == 0 && UseSize == 0)
	{
		srand(GetTickCount());

		int DeckSize = m_vecPlayer1_Deck.size();
		int* Arr = new int[DeckSize];
		for (int i = 0; i < DeckSize; ++i)
		{
			Arr[i] = i;
		}
		for (int i = 0; i < 50; i++)
		{
			int S1 = rand() % DeckSize;
			int S2 = rand() % DeckSize;

			CCard* temp = m_vecPlayer1_Deck[S1];
			m_vecPlayer1_Deck[S1] = m_vecPlayer1_Deck[S2];
			m_vecPlayer1_Deck[S2] = temp;
		}
		delete Arr;
		return;
	}


	for (int i = 0; i < BackSize; ++i)
	{

		m_vecPlayer1_Deck.push_back(m_vecPlayer1_Back[i]);
		m_vecPlayer1_Deck.back()->SettingGone();
		//m_vecPlayer1_Deck.back()->SetUse(false);
	}
	for (int i = 0; i < UseSize; ++i)
	{

		m_vecPlayer1_Deck.push_back(m_vecPlayer1_Use[i]);
		m_vecPlayer1_Deck.back()->SettingGone();
		m_vecPlayer1_Deck.back()->SetUse(false);
	}
	m_vecPlayer1_Back.clear();
	m_vecPlayer1_Use.clear();


	srand(GetTickCount());

	int DeckSize = m_vecPlayer1_Deck.size();
	int* Arr = new int[DeckSize];
	for (int i = 0; i < DeckSize; ++i)
	{
		Arr[i] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		int S1 = rand() % DeckSize;
		int S2 = rand() % DeckSize;

		CCard* temp = m_vecPlayer1_Deck[S1];
		m_vecPlayer1_Deck[S1] = m_vecPlayer1_Deck[S2];
		m_vecPlayer1_Deck[S2] = temp;
	}
	delete Arr;

	
}

void CGameMapObj::Refresh2Free()
{
	RefreshSound();
	size_t BackSize = m_vecPlayer2_Back.size();
	size_t UseSize = m_vecPlayer2_Use.size();
	if (BackSize == 0 && UseSize == 0)
	{
		srand(GetTickCount());

		int DeckSize = m_vecPlayer2_Deck.size();
		int* Arr = new int[DeckSize];
		for (int i = 0; i < DeckSize; ++i)
		{
			Arr[i] = i;
		}
		for (int i = 0; i < 50; i++)
		{
			int S1 = rand() % DeckSize;
			int S2 = rand() % DeckSize;

			CCard* temp = m_vecPlayer2_Deck[S1];
			m_vecPlayer2_Deck[S1] = m_vecPlayer2_Deck[S2];
			m_vecPlayer2_Deck[S2] = temp;
		}
		delete Arr;
		return;
	}


	for (int i = 0; i < BackSize; ++i)
	{

		m_vecPlayer2_Deck.push_back(m_vecPlayer2_Back[i]);
		m_vecPlayer2_Deck.back()->SettingGone();
		//m_vecPlayer1_Deck.back()->SetUse(false);
	}
	for (int i = 0; i < UseSize; ++i)
	{

		m_vecPlayer2_Deck.push_back(m_vecPlayer2_Use[i]);
		m_vecPlayer2_Deck.back()->SettingGone();
		m_vecPlayer2_Deck.back()->SetUse(false);
	}
	m_vecPlayer2_Back.clear();
	m_vecPlayer2_Use.clear();


	srand(GetTickCount());

	int DeckSize = m_vecPlayer2_Deck.size();
	int* Arr = new int[DeckSize];
	for (int i = 0; i < DeckSize; ++i)
	{
		Arr[i] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		int S1 = rand() % DeckSize;
		int S2 = rand() % DeckSize;

		CCard* temp = m_vecPlayer2_Deck[S1];
		m_vecPlayer2_Deck[S1] = m_vecPlayer2_Deck[S2];
		m_vecPlayer2_Deck[S2] = temp;
	}
	delete Arr;

}

void CGameMapObj::Player1HandtoUse(CCard* card)
{
	if (card == nullptr)
		return;
	for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
	{
		if (m_vecPlayer1_Hand[i] == card)
		{
			m_vecPlayer1_Hand[i]->SettingGone();
			m_vecPlayer1_Hand[i]->SetSelect(false);
			m_vecPlayer1_Hand[i]->SetSelectTime(false);
			m_vecPlayer1_Hand[i]->UnSellectTextureSetting();
			m_vecPlayer1_Hand[i]->SetLoopup(false);
			m_vecPlayer1_Use.push_back(m_vecPlayer1_Hand[i]);
			m_vecPlayer1_Hand.erase(m_vecPlayer1_Hand.begin() + i);
			break;
		}
	}
}

void CGameMapObj::Player1HandUnSellect()
{
	for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
	{
		m_vecPlayer1_Hand[i]->SetSelect(false);
		m_vecPlayer1_Hand[i]->SetSelectTime(false);
		m_vecPlayer1_Hand[i]->UnSellectTextureSetting();
		m_vecPlayer1_Hand[i]->SetLoopup(false);
	}

}

void CGameMapObj::Player1HeroDeckUnSellectTime()
{
	for (int i = 0; i < m_vecPlayer1_Hero.size(); ++i)
	{
		m_vecPlayer1_Hero[i]->SetSelect(false);
		m_vecPlayer1_Hero[i]->SetSelectTime(false);
		m_vecPlayer1_Hero[i]->UnSellectTextureSetting();
	}

}

int CGameMapObj::Player1HandNotAttack()
{	
	int  temp = 0;

	for (int i = 0; i < m_vecPlayer1_Hand.size(); ++i)
	{
		if (m_vecPlayer1_Hand[i]->GetCardType() != Card_Type::Attack)
		{
			++temp;
		}
	}

	return temp;
}

void CGameMapObj::ManaSound()
{
	m_pScene->GetResource()->SoundPlay("Mana");
}

void CGameMapObj::OraSound()
{
	m_pScene->GetResource()->SoundPlay("Ora");
}

void CGameMapObj::ForwardSound()
{
	m_pScene->GetResource()->SoundPlay("FrontWard");
}

void CGameMapObj::BackWardSound()
{
	m_pScene->GetResource()->SoundPlay("BackWard");
}

void CGameMapObj::ItalSound()
{
	m_pScene->GetResource()->SoundPlay("BackWard");
}

void CGameMapObj::TurnEndSound()
{
	m_pScene->GetResource()->SoundPlay("TurnEnd");
}

void CGameMapObj::DaeungSound()
{
	m_pScene->GetResource()->SoundPlay("daeungsound");
}

void CGameMapObj::HideSound()
{
	m_pScene->GetResource()->SoundPlay("hide");
}

void CGameMapObj::DrawSound()
{
	m_pScene->GetResource()->SoundPlay("draw");
}

void CGameMapObj::RefreshSound()
{
	m_pScene->GetResource()->SoundPlay("refresh");
}

void CGameMapObj::MissSound()
{
	m_pScene->GetResource()->SoundPlay("miss");
}

void CGameMapObj::CardUseCloseWidget()
{
	m_CardUseWidget->CloseWidget();
}

bool CGameMapObj::Player1FocusCheck()
{
	if (m_DALIN_Range == m_Range && m_Dust == 0 && m_Player1_Shiled == 0)
		return false;
	return true;
}

bool CGameMapObj::Player2FocusCheck()
{

	if (m_DALIN_Range == m_Range && m_Dust == 0 && m_Player1_Shiled == 0)
		return false;
	return true;
}

void CGameMapObj::RangeUp()
{
	for (int i = 0; i < m_vecRange.size(); ++i)
	{
		m_vecRange[i]->RangeUp();
	}
}

void CGameMapObj::RangeDown()
{
	for (int i = 0; i < m_vecRange.size(); ++i)
	{
		m_vecRange[i]->RangeDown();
	}
}

void CGameMapObj::WhicSound()
{
	m_pScene->GetResource()->SoundPlay("whic");
}

void CGameMapObj::ESCButton(float Delata)
{
	m_BackWidget->Show(Delata);

}

void CGameMapObj::CardClickSound()
{
	m_pScene->GetResource()->SoundPlay("cardclick");
}


