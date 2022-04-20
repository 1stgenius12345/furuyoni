#include "BuildingCard.h"

CBuildingCard::CBuildingCard():
	m_NabWidget(nullptr),
	m_teum(false)
{
	m_CardType = Card_Type::Building;
}

CBuildingCard::CBuildingCard(const CBuildingCard& obj) :
	CCard(obj)
{
	m_NabWidget = obj.m_NabWidget;
	m_teum = obj.m_teum;

}

CBuildingCard::~CBuildingCard()
{
}

void CBuildingCard::Start()
{
	CCard::Start();
}

bool CBuildingCard::Init()
{
	CCard::Init();

	//기본맵 위젯 관리
	m_NabWidgetComponent = CreateSceneComponent<CWidgetComponent>("m_NabWidgetComponent");
	m_NabWidgetComponent->SetRender2DType(Render_Type_2D::RT2D_Default);
	m_NabWidget = m_NabWidgetComponent->CreateWidget<CBuildingHUDWidget>("m_GameMapWidget");
	m_NabWidget->SetBuildingCard(this);
	//m_NabWidget->SetGameMapObj(this);
	m_Sprite->AddChild(m_NabWidgetComponent);

	return true;
}

void CBuildingCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (m_Use)
	{
		m_NabWidget->UseNabRenderUpdate();
	}
	else
	{
		m_NabWidget->UnUseNabRenderUpdate();
	}
}

void CBuildingCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CBuildingCard::Collision(float DeltaTime)
{
	CCard::Collision(DeltaTime);
}

void CBuildingCard::Render(float DeltaTime)
{
	CCard::Render(DeltaTime);
}

CBuildingCard* CBuildingCard::Clone()
{
	return new CBuildingCard(*this);
}

void CBuildingCard::Animation2DNotify(const std::string& Name)
{
}


void CBuildingCard::CreateCardSetting()
{
	// 통상패 세팅
	if (Card_Class::Normal == m_CardClass)
	{
		switch (m_HeroIndex)
		{
		// 유리나
		case 1:
			switch (m_CardIndex)
			{
			// 6번카드 압도
			case 5:
				BuildingCardSetting(2, 0, 0);
				m_teum = true;
				break;
			// 7번카드 기염만장
			case 6:
				BuildingCardSetting(4,0,1);
				break;
			default:
				break;
			}
			break;
		// 부여
		case 3:
			switch (m_CardIndex)
			{
			// 권역
			case 4:
				BuildingCardSetting(2, 0, 0);
				break;
			// 충음정
			case 5:
				BuildingCardSetting(1,1,0);
				break;
			//무음벽
			case 6:
				BuildingCardSetting(5, 0, 1);
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (m_CardIndex)
			{
				// 바람의 무대
			case 5:
				BuildingCardSetting(2, 0, 0);
				break;
				//무음벽
			case 6:
				BuildingCardSetting(2, 0, 0);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	//  비장패 세팅
	else
	{
		switch (m_HeroIndex)
		{
		case 1:
			switch (m_CardIndex)
			{
			
			default:
				break;
			}
			break;
		default:
			break;
		}
	}


}


void CBuildingCard::BuildingCardSetting(int nab, int dae, int jeo)
{
	m_Nab = nab;
	m_Daeung = dae;
	m_Tenreok = jeo;
}

void CBuildingCard::BuildingCardSetting(int nab, int dae, int jeo, int mana)
{
	m_Nab = nab;
	m_Daeung = dae;
	m_Tenreok = jeo;
	m_ManaCost = mana;
}

