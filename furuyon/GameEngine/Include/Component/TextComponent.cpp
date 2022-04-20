
#include "TextComponent.h"
#include "../Device.h"
#include "../Resource/ResourceManager.h"
//#include "WidgetWindow.h"

CTextComponent::CTextComponent() :
	m_Font(nullptr),
	m_Layout(nullptr),
	m_ColorBrush(nullptr),
	m_2DTarget(nullptr),
	m_Text(nullptr),
	m_FontName(nullptr),
	m_MaxCount(0),
	m_FontSize(12.f),
	m_Alpha(true),
	m_Opacity(1.f),
	m_Color(1.f, 1.f, 1.f, 1.f),
	m_ShadowEnable(false),
	m_ShadowColorBrush(nullptr),
	m_ShadowAlpha(true),
	m_ShadowOpacity(1.f),
	m_ShadowColor(0.f, 0.f, 0.f, 1.f),
	m_ShadowOffset(3.f, 3.f),
	m_AlignH(TEXT_ALIGN_H2::Left),
	m_AlignV(TEXT_ALIGN_V2::Top)
{
	m_2DTarget = CDevice::GetInst()->Get2DTarget();

	const TCHAR* FontName = CResourceManager::GetInst()->GetFontFaceName("Default");

	m_FontName = new TCHAR[128];
	memset(m_FontName, 0, sizeof(TCHAR) * 128);
	lstrcpy(m_FontName, FontName);

	m_FontKey = "Default";

	m_MaxCount = 256;

	m_Text = new TCHAR[m_MaxCount];
	memset(m_Text, 0, sizeof(TCHAR) * 256);
	lstrcpy(m_Text, TEXT("Text"));

	m_Font = CResourceManager::GetInst()->FindFont(m_FontKey);
	m_Layout = CResourceManager::GetInst()->CreateTextLayout(m_Text,
		m_FontKey, 100.f, 100.f);
	CResourceManager::GetInst()->CreateFontColor(m_Color);
	m_ColorBrush = CResourceManager::GetInst()->FindFontColor(m_Color);

	CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
	m_ShadowColorBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);

	SetRelativePos(100.f, 100.f, 0.f);

}

CTextComponent::CTextComponent(const CTextComponent& widget)
{
	m_Font = widget.m_Font;
	m_Layout = widget.m_Layout;
	m_ColorBrush = widget.m_ColorBrush;
	m_2DTarget = widget.m_2DTarget;

	m_MaxCount = widget.m_MaxCount;

	m_Text = new TCHAR[m_MaxCount];

	memset(m_Text, 0, sizeof(TCHAR) * m_MaxCount);
	lstrcpy(m_Text, widget.m_Text);

	m_FontKey = widget.m_FontKey;

	int	Length = lstrlen(widget.m_FontName);
	m_FontName = new TCHAR[Length + 1];

	memset(m_FontName, 0, sizeof(TCHAR) * (Length + 1));
	lstrcpy(m_FontName, widget.m_FontName);

	m_FontSize = widget.m_FontSize;
	m_Alpha = widget.m_Alpha;
	m_Opacity = widget.m_Opacity;
	m_Color = widget.m_Color;


	m_ShadowEnable = widget.m_ShadowEnable;
	m_ShadowColorBrush = widget.m_ShadowColorBrush;
	m_ShadowAlpha = widget.m_ShadowAlpha;
	m_ShadowOpacity = widget.m_ShadowOpacity;
	m_ShadowColor = widget.m_ShadowColor;
	m_ShadowOffset = widget.m_ShadowOffset;
	m_AlignH = widget.m_AlignH;
	m_AlignV = widget.m_AlignV;
}

CTextComponent::~CTextComponent()
{
	SAFE_RELEASE(m_Layout);
	SAFE_DELETE_ARRAY(m_Text);
	SAFE_DELETE_ARRAY(m_FontName);
}

void CTextComponent::SetMaxTextCount(int MaxCount)
{
	if (m_MaxCount >= MaxCount)
		return;

	TCHAR* Text = new TCHAR[MaxCount];

	memset(Text, 0, sizeof(TCHAR) * MaxCount);

	lstrcpy(Text, m_Text);

	m_MaxCount = MaxCount;

	SAFE_DELETE_ARRAY(m_Text);

	m_Text = Text;
}

void CTextComponent::SetText(const TCHAR* Text)
{
	int	Count = lstrlen(Text);

	if (m_MaxCount < Count)
	{
		m_MaxCount = Count + 1;
		SAFE_DELETE_ARRAY(m_Text);
		m_Text = new TCHAR[m_MaxCount];
	}

	memset(m_Text, 0, sizeof(TCHAR) * m_MaxCount);
	lstrcpy(m_Text, Text);

	CreateTextLayout();
}

void CTextComponent::AddText(const TCHAR* Text)
{
	int	Count = lstrlen(Text);
	int	CurCount = lstrlen(m_Text);

	if (m_MaxCount < Count + CurCount)
	{
		m_MaxCount = (Count + CurCount) * 2;

		TCHAR* NewText = new TCHAR[m_MaxCount];
		memset(NewText, 0, sizeof(TCHAR) * m_MaxCount);

		lstrcpy(NewText, m_Text);

		SAFE_DELETE_ARRAY(m_Text);
		m_Text = NewText;
	}

	lstrcat(m_Text, Text);

	CreateTextLayout();
}

void CTextComponent::SetFont(const std::string& Name)
{
	m_Font = CResourceManager::GetInst()->FindFont(Name);

	CreateTextLayout();
}

void CTextComponent::SetFontSize(float FontSize)
{
	m_FontSize = FontSize;

	CreateTextLayout();
}

void CTextComponent::SetAlignH(TEXT_ALIGN_H2 Align)
{
	m_AlignH = Align;

	CreateTextLayout();
}

void CTextComponent::SetAlignV(TEXT_ALIGN_V2 Align)
{
	m_AlignV = Align;

	CreateTextLayout();
}

void CTextComponent::SetColor(float r, float g, float b)
{
	m_Color.x = r;
	m_Color.y = g;
	m_Color.z = b;

	CResourceManager::GetInst()->CreateFontColor(m_Color);
	m_ColorBrush = CResourceManager::GetInst()->FindFontColor(m_Color);
}

void CTextComponent::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_Color.x = r / 255.f;
	m_Color.y = g / 255.f;
	m_Color.z = b / 255.f;

	CResourceManager::GetInst()->CreateFontColor(m_Color);
	m_ColorBrush = CResourceManager::GetInst()->FindFontColor(m_Color);
}

void CTextComponent::SetColor(const Vector3& Color)
{
	m_Color.x = Color.x;
	m_Color.y = Color.y;
	m_Color.z = Color.z;

	CResourceManager::GetInst()->CreateFontColor(m_Color);
	m_ColorBrush = CResourceManager::GetInst()->FindFontColor(m_Color);
}

void CTextComponent::SetColor(unsigned int Color)
{
	m_Color.z = (Color & 0x000000ff) / 255.f;
	m_Color.y = ((Color >> 8) & 0x000000ff) / 255.f;
	m_Color.x = ((Color >> 16) & 0x000000ff) / 255.f;

	CResourceManager::GetInst()->CreateFontColor(m_Color);
	m_ColorBrush = CResourceManager::GetInst()->FindFontColor(m_Color);
}

void CTextComponent::SetAlphaEnable(bool AlphaEnable)
{
	m_Alpha = AlphaEnable;
}

void CTextComponent::SetOpacity(float Opacity)
{
	m_Opacity = Opacity;
}

void CTextComponent::SetShadowEnable(bool ShadowEnable)
{
	m_ShadowEnable = ShadowEnable;
}

void CTextComponent::SetShadowOffset(const Vector2& ShadowOffset)
{
	m_ShadowOffset = ShadowOffset;
}

void CTextComponent::SetShadowColor(float r, float g, float b)
{
	m_ShadowColor.x = r;
	m_ShadowColor.y = g;
	m_ShadowColor.z = b;

	CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
	m_ShadowColorBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
}

void CTextComponent::SetShadowColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_ShadowColor.x = r / 255.f;
	m_ShadowColor.y = g / 255.f;
	m_ShadowColor.z = b / 255.f;

	CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
	m_ShadowColorBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
}

void CTextComponent::SetShadowColor(const Vector3& Color)
{
	m_ShadowColor.x = Color.x;
	m_ShadowColor.y = Color.y;
	m_ShadowColor.z = Color.z;

	CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
	m_ShadowColorBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
}

void CTextComponent::SetShadowColor(unsigned int Color)
{
	m_ShadowColor.z = (Color & 0x000000ff) / 255.f;
	m_ShadowColor.y = ((Color >> 8) & 0x000000ff) / 255.f;
	m_ShadowColor.x = ((Color >> 16) & 0x000000ff) / 255.f;

	CResourceManager::GetInst()->CreateFontColor(Color);
	m_ShadowColorBrush = CResourceManager::GetInst()->FindFontColor(Color);
}

void CTextComponent::SetShadowAlphaEnable(bool AlphaEnable)
{
	m_ShadowAlpha = AlphaEnable;
}

void CTextComponent::SetShadowOpacity(float Opacity)
{
	m_ShadowOpacity = Opacity;
}

void CTextComponent::CreateTextLayout()
{
	if (!m_Font)
		return;

	SAFE_RELEASE(m_Layout);

	m_Layout = CResourceManager::GetInst()->CreateTextLayout(m_Text, m_Font,
		GetRelativeScale().x, GetRelativeScale().y);

	DWRITE_TEXT_RANGE	Range = {};
	Range.startPosition = 0;
	Range.length = lstrlen(m_Text);

	m_Layout->SetFontSize(m_FontSize, Range);

	switch (m_AlignH)
	{
	case TEXT_ALIGN_H2::Left:
		m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		break;
	case TEXT_ALIGN_H2::Center:
		m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case TEXT_ALIGN_H2::Right:
		m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		break;
	}


	switch (m_AlignV)
	{
	case TEXT_ALIGN_V2::Top:
		m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	case TEXT_ALIGN_V2::Middle:
		m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	case TEXT_ALIGN_V2::Bottom:
		m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;
	}
}

void CTextComponent::Start()
{
	m_2DTarget = CDevice::GetInst()->Get2DTargetWorld();
}

bool CTextComponent::Init()
{
	CPrimitiveComponent::Init();

	CreateTextLayout();

	return true;
}

void CTextComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
	m_2DTarget->BeginDraw();

	Resolution	RS = CDevice::GetInst()->GetResolution();

	D2D1_POINT_2F	Point;

	Point.x = GetRelativePos().x;
	Point.y = RS.Height - GetRelativePos().y - GetRelativeScale().y;

	if (m_ShadowEnable)
	{
		D2D1_POINT_2F	ShadowPoint = Point;
		ShadowPoint.x += m_ShadowOffset.x;
		ShadowPoint.y += m_ShadowOffset.y;

		if (m_ShadowAlpha)
			m_ShadowColorBrush->SetOpacity(m_ShadowOpacity);

		else
			m_ShadowColorBrush->SetOpacity(1.f);

		m_2DTarget->DrawTextLayout(ShadowPoint, m_Layout, m_ShadowColorBrush,
			D2D1_DRAW_TEXT_OPTIONS_NONE);
	}


	if (m_Alpha)
		m_ColorBrush->SetOpacity(m_Opacity);

	else
		m_ColorBrush->SetOpacity(1.f);

	m_2DTarget->DrawTextLayout(Point, m_Layout, m_ColorBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE);

	m_2DTarget->EndDraw();
	
}

void CTextComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CTextComponent::Collision(float DeltaTime)
{
}

void CTextComponent::Render(float DeltaTime)
{
	/*m_2DTarget->BeginDraw();

	Resolution	RS = CDevice::GetInst()->GetResolution();

	D2D1_POINT_2F	Point;

	Point.x = GetRelativePos().x;
	Point.y = RS.Height - GetRelativePos().y - GetRelativeScale().y;

	if (m_ShadowEnable)
	{
		D2D1_POINT_2F	ShadowPoint = Point;
		ShadowPoint.x += m_ShadowOffset.x;
		ShadowPoint.y += m_ShadowOffset.y;

		if (m_ShadowAlpha)
			m_ShadowColorBrush->SetOpacity(m_ShadowOpacity);

		else
			m_ShadowColorBrush->SetOpacity(1.f);

		m_2DTarget->DrawTextLayout(ShadowPoint, m_Layout, m_ShadowColorBrush,
			D2D1_DRAW_TEXT_OPTIONS_NONE);
	}


	if (m_Alpha)
		m_ColorBrush->SetOpacity(m_Opacity);

	else
		m_ColorBrush->SetOpacity(1.f);

	m_2DTarget->DrawTextLayout(Point, m_Layout, m_ColorBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE);

	m_2DTarget->EndDraw();*/
}

CTextComponent* CTextComponent::Clone()
{
	return new CTextComponent(*this);
}
