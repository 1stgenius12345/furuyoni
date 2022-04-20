
#include "Standard2DCard.h"

CStandard2DCard::CStandard2DCard()
{
}

CStandard2DCard::~CStandard2DCard()
{
}

bool CStandard2DCard::Init()
{
	if (!LoadVertexShader(m_Name, "Standard2DTextureVS", TEXT("Card2D.fx"), SHADER_PATH))
		return false;

	if (!LoadPixelShader(m_Name, "Standard2DTexturePS", TEXT("Card2D.fx"), SHADER_PATH))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
		return false;

	return true;
}
