#include "BuildingHUDWidget.h"
#include "../Object/BuildingCard.h"
CBuildingHUDWidget::CBuildingHUDWidget():
	m_OwnerCard(nullptr)
{
}

CBuildingHUDWidget::CBuildingHUDWidget(const CBuildingHUDWidget& widget)
{
}

CBuildingHUDWidget::~CBuildingHUDWidget()
{
}

bool CBuildingHUDWidget::Init()
{
	CWidgetWindow::Init();

	m_BuildingNumber = CreateWidget<CNumberWidget>("m_BuildingNumber");
	m_BuildingNumber->SetPos(-674.f / 8.f / 1.3f, -838.f / 8.f / 1.3f);
	m_BuildingNumber->SetNumberSize(150.f / 200.0f, 134.f / 200.0f);
	m_BuildingNumber->SetTexture("NormalCardIn", TEXT("Number_150134.png"));
	m_BuildingNumber->SetNumber(0);
	m_BuildingNumber->SetFrameCount(10, 4);
	m_BuildingNumber->SetZOrder(3);

	return true;
}

void CBuildingHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_OwnerCard != nullptr)
	{
		m_BuildingNumber->SetNumber(m_OwnerCard->GetNabpoint());
	}
}

void CBuildingHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBuildingHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CBuildingHUDWidget* CBuildingHUDWidget::Clone()
{
	return new CBuildingHUDWidget(*this);
}

void CBuildingHUDWidget::UseNabRenderUpdate()
{
	m_BuildingNumber->SetNumberSize(150.f / 2.2f, 134.f / 2.2f);
}

void CBuildingHUDWidget::UnUseNabRenderUpdate()
{
	m_BuildingNumber->SetNumberSize(150.f / 200.0f, 134.f / 200.0f);
	
}
