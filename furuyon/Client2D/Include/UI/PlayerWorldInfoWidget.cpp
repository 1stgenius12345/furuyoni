
#include "PlayerWorldInfoWidget.h"
#include "Input.h"


CPlayerWorldInfoWidget::CPlayerWorldInfoWidget()
{

}

CPlayerWorldInfoWidget::CPlayerWorldInfoWidget(const CPlayerWorldInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CPlayerWorldInfoWidget::~CPlayerWorldInfoWidget()
{
}

bool CPlayerWorldInfoWidget::Init()
{	//m_ProfileImage->SetShader("UIImageShader");
	CWidgetWindow::Init();

	m_ProfileImage = CreateWidget<CImage>("Image");
	m_ProfileImage->SetTexture("PlayerTex", TEXT("참_일러.png"));
	m_ProfileImage->SetPos(m_Size.x * -172.f, m_Size.x * -69.f);
	m_ProfileImage->SetSize(m_Size.x*320.f, m_Size.y*365.6f);
	m_ProfileImage->SetZOrder(10);
	

	m_NameText = CreateWidget<CText>("Name");
	m_NameText->SetText(TEXT("참"));
	m_NameText->SetPos(m_Size.x* -143.f, m_Size.y* -44.f);
	m_NameText->SetSize(m_Size.x * 300.f, m_Size.y * 50.f);
	m_NameText->SetFontSize(m_Size.x * 30.f);
	m_NameText->SetShadowEnable(false);
	m_NameText->SetShadowColor(1.f, 1.f, 0.f);
	m_NameText->SetShadowAlphaEnable(true);
	m_NameText->SetShadowOpacity(0.5f);
	m_NameText->SetAlignH(TEXT_ALIGN_H::Center);
	m_NameText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_NameText->SetZOrder(4);

	//m_HPBar = CreateWidget<CProgressBar>("HPBar");

	//m_HPBar->SetPos(50.f, 0.f);
	//m_HPBar->SetSize(100.f, 20.f);
	////m_HPBar->SetTint(1.f, 1.f, 1.f, 0.6f);
	//m_HPBar->SetTexture("HPBar", TEXT("HPBar.png"));

	m_AttackShield_NumberWidget = CreateWidget<CNumberWidget>("NumberShield");

	m_AttackShield_NumberWidget->SetPos(m_Size.x * -174, m_Size.y * -262);
	m_AttackShield_NumberWidget->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);
	m_AttackShield_NumberWidget->SetTexture("NumberShield", TEXT("Number.png"));
	m_AttackShield_NumberWidget->SetNumber(3);
	m_AttackShield_NumberWidget->SetFrameCount(10, 2);
	m_AttackShield_NumberWidget->SetZOrder(8);



	m_AttackLife_NumberWidget = CreateWidget<CNumberWidget>("NumberLife");
	m_AttackLife_NumberWidget->SetPos(m_Size.x * 114, m_Size.y * -262);
	m_AttackLife_NumberWidget->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);
	m_AttackLife_NumberWidget->SetTexture("NumberLife", TEXT("Number.png"));
	m_AttackLife_NumberWidget->SetNumber(1);
	m_AttackLife_NumberWidget->SetFrameCount(10, 2);
	m_AttackLife_NumberWidget->SetZOrder(4);


	

	m_RangeMin = CreateWidget<CNumberWidget>("RangeMin");
	m_RangeMin->SetPos(m_Size.x * -86.f, m_Size.y * 225.f);
	m_RangeMin->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);
	m_RangeMin->SetTexture("NumberLife", TEXT("Number.png"));
	m_RangeMin->SetNumber(3);
	m_RangeMin->SetFrameCount(10, 2);
	m_RangeMin->SetZOrder(6);

	m_RangeMax = CreateWidget<CNumberWidget>("RangeMax");
	m_RangeMax->SetPos(m_Size.x * 29.f, m_Size.y * 225.f);
	m_RangeMax->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);
	m_RangeMax->SetTexture("NumberLife", TEXT("Number.png"));
	m_RangeMax->SetNumber(4);
	m_RangeMax->SetFrameCount(10, 2);
	m_RangeMax->SetZOrder(6);

	m_RangeTilde = CreateWidget<CText>("Tilde");

	m_RangeTilde->SetText(TEXT("~"));
	m_RangeTilde->SetPos(m_Size.x * -100.f, m_Size.y * 235.f);
	m_RangeTilde->SetSize(m_Size.x * 200.f, m_Size.y * 50.f);
	m_RangeTilde->SetFontSize(m_Size.x * 30.f);
	m_RangeTilde->SetShadowEnable(false);
	m_RangeTilde->SetShadowColor(1.f, 1.f, 0.f);
	m_RangeTilde->SetShadowAlphaEnable(true);
	m_RangeTilde->SetShadowOpacity(0.5f);
	m_RangeTilde->SetAlignH(TEXT_ALIGN_H::Center);
	m_RangeTilde->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_RangeTilde->SetZOrder(7);
	// 위치 체크용

	//m_Check_PosX = CreateWidget<CNumberWidget>("CheckPosX");
	//m_Check_PosX->SetPos(-300.f, 0.f);
	//m_Check_PosX->SetNumberSize(50.f, 50.f);
	//m_Check_PosX->SetTexture("Number", TEXT("Number.png"));
	//m_Check_PosX->SetNumber(m_RangeTilde->GetPos().x);
	//m_Check_PosX->SetFrameCount(10, 2);
	//m_Check_PosX->SetZOrder(2);



	//m_Check_PosY = CreateWidget<CNumberWidget>("CheckPosY");
	//m_Check_PosY->SetPos(-300.f, -50.f);
	//m_Check_PosY->SetNumberSize(50.f, 50.f);
	//m_Check_PosY->SetTexture("Number", TEXT("Number.png"));
	//m_Check_PosY->SetNumber(m_RangeTilde->GetPos().y);
	//m_Check_PosY->SetFrameCount(10, 2);
	//m_Check_PosY->SetZOrder(2);

	CInput::GetInst()->AddKeyCallback<CPlayerWorldInfoWidget>("MoveUp", KT_Push, this, &CPlayerWorldInfoWidget::MoveUp);
	CInput::GetInst()->AddKeyCallback<CPlayerWorldInfoWidget>("MoveDown", KT_Push, this, &CPlayerWorldInfoWidget::MoveDown);
	CInput::GetInst()->AddKeyCallback<CPlayerWorldInfoWidget>("MoveLeft", KT_Push, this, &CPlayerWorldInfoWidget::MoveLeft);
	CInput::GetInst()->AddKeyCallback<CPlayerWorldInfoWidget>("MoveRight", KT_Push, this, &CPlayerWorldInfoWidget::MoveRight);

	return true;
}

void CPlayerWorldInfoWidget::Update(float DeltaTime)
{
	//m_Check_PosX->SetNumber(m_ProfileImage->GetPos().x + 2000);
	//m_Check_PosY->SetNumber(m_ProfileImage->GetPos().y + 2000);
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerWorldInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerWorldInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CPlayerWorldInfoWidget* CPlayerWorldInfoWidget::Clone()
{
	return new CPlayerWorldInfoWidget(*this);
}

void CPlayerWorldInfoWidget::ClickCallback()
{
//	MessageBox(0, TEXT("Click"), TEXT("Click"), MB_OK);
}

void CPlayerWorldInfoWidget::MoveUp(float DeltaTime)
{
	m_CardImage->AddPos(Vector2(0, DeltaTime * 10));
}

void CPlayerWorldInfoWidget::MoveDown(float DeltaTime)
{
	m_CardImage->AddPos(Vector2(0,-DeltaTime * 10));
}

void CPlayerWorldInfoWidget::MoveLeft(float DeltaTime)
{
	m_CardImage->AddPos(Vector2(-DeltaTime * 10, 0));
}

void CPlayerWorldInfoWidget::MoveRight(float DeltaTime)
{
	m_CardImage->AddPos(Vector2(DeltaTime * 10, 0));
}

void CPlayerWorldInfoWidget::UpdatePosANDScale()
{


	m_CardImage->SetPos(m_Size.x * -187.5f, m_Size.x * -281.25f);
	m_CardImage->SetSize(m_Size.x * 375.f, m_Size.y * 563.f);

	m_ProfileImage->SetPos(m_Size.x * -172.f, m_Size.x * -69.f);
	m_ProfileImage->SetSize(m_Size.x * 320.f, m_Size.y * 365.6f);




	m_NameText->SetPos(m_Size.x * -143.f, m_Size.y * -44.f);
	m_NameText->SetSize(m_Size.x * 300.f, m_Size.y * 50.f);
	m_NameText->SetFontSize(m_Size.x * 30.f);



	m_AttackShield_NumberWidget->SetPos(m_Size.x * -174, m_Size.y * -262);
	m_AttackShield_NumberWidget->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);



	m_AttackLife_NumberWidget->SetPos(m_Size.x * 114, m_Size.y * -262);
	m_AttackLife_NumberWidget->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);





	m_RangeMin->SetPos(m_Size.x * -86.f, m_Size.y * 225.f);
	m_RangeMin->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);

	m_RangeMax->SetPos(m_Size.x * 29.f, m_Size.y * 225.f);
	m_RangeMax->SetNumberSize(m_Size.x * 50.f, m_Size.y * 50.f);


	m_RangeTilde->SetPos(m_Size.x * -100.f, m_Size.y * 235.f);
	m_RangeTilde->SetSize(m_Size.x * 200.f, m_Size.y * 50.f);
	m_RangeTilde->SetFontSize(m_Size.x * 30.f);



}
