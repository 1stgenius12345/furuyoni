
#include "Share.fx"

/*
int : ����
float : �Ǽ�
float2 ~ 4 : 2, 3, 4���� ����(floatŸ��)
int2 ~ 4 : 2, 3, 4���� ����(intŸ��)
matrix : 4x4 ���
float3x3 : 3x3 ��� floatŸ��
*/


struct VS_INPUT_COLOR
{
	// : �ڿ� Semantic �� �ۼ��Ѵ�.
	// POSITION �������Ϳ� �ִ� ���� �����ڴٴ� �ǹ��̴�.
	// �ڿ��� �������� ��ȣ�� ���� �� �ִ�. POSITION1 �̷������� �ۼ��� �����ϴ�.
	// �Ⱥٿ��� ��쿡�� 0���� �ڵ����� ������ �ȴ�.
	float3  Pos : POSITION;
	float4  Color : COLOR;
};

struct VS_OUTPUT_COLOR
{
	// SV �� ������ System Value �̴�.
	// �� �������� Shader �ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ����ϴ�.
	// ���� �������� ��ȯ�� ������ SV_POSITION �������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	// ȭ����������� ��ȯ�� �Ͼ�� �ȴ�.
	float4  Pos : SV_POSITION;
	float4  Color : COLOR;
	float2	UV	: TEXCOORD;
};

float2 ComputeAnimation2DUV(float2 UV)
{
	if (g_Animation2DEnable == 0)
		return UV;

	if (g_Animation2DType == Animation2DFrame ||
		g_Animation2DType == Animation2DArray)
		return UV;

	float2	ResultUV;

	if (UV.x <= 0.f)
		ResultUV.x = g_vAnimation2DStartUV.x;

	else
		ResultUV.x = g_vAnimation2DEndUV.x;

	if (UV.y <= 0.f)
		ResultUV.y = g_vAnimation2DStartUV.y;

	else
		ResultUV.y = g_vAnimation2DEndUV.y;

	return ResultUV;
}

VS_OUTPUT_COLOR Standard2DColorVS(VS_INPUT_COLOR input)
{
	VS_OUTPUT_COLOR output = (VS_OUTPUT_COLOR)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;

	// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	output.Color = input.Color;

	return output;
}


PS_OUTPUT_SINGLE Standard2DColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4	Color = input.Color * g_vMtrlBaseColor + g_vMtrlEmissiveColor;

	output.Color = Color;

	return output;
}

struct VS_INPUT_UV
{
	// : �ڿ� Semantic �� �ۼ��Ѵ�.
	// POSITION �������Ϳ� �ִ� ���� �����ڴٴ� �ǹ��̴�.
	// �ڿ��� �������� ��ȣ�� ���� �� �ִ�. POSITION1 �̷������� �ۼ��� �����ϴ�.
	// �Ⱥٿ��� ��쿡�� 0���� �ڵ����� ������ �ȴ�.
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

struct VS_OUTPUT_UV
{
	// SV �� ������ System Value �̴�.
	// �� �������� Shader �ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ����ϴ�.
	// ���� �������� ��ȯ�� ������ SV_POSITION �������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	// ȭ����������� ��ȯ�� �Ͼ�� �ȴ�.
	float4  Pos : SV_POSITION;
	float2  UV : TEXCOORD;
	float4	ProjPos : POSITION;
};

VS_OUTPUT_UV Standard2DTextureVS(VS_INPUT_UV input)
{
	VS_OUTPUT_UV output = (VS_OUTPUT_UV)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;

	// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	output.Pos = output.ProjPos;
	output.UV = ComputeAnimation2DUV(input.UV);

	return output;
}


PS_OUTPUT_SINGLE Standard2DTexturePS(VS_OUTPUT_UV input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);
	
	float4 color1 = g_DistortionFilterTex.Sample(g_AnisotropicSmp, input.UV);


	float4	result = (float4)0.f;

	result.rgb = BaseColor.rgb * (g_vMtrlBaseColor.rgb) * (color1.rgb/0.5f) + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb ;

	result.a = BaseColor.a * g_MtrlOpacity / (color1.a);

	result = PaperBurn2D(result, input.UV);

	result = Distortion(result, input.UV, input.ProjPos);

	output.Color = result;

	return output;
}



struct VS_INPUT2_UV
{
	// : �ڿ� Semantic �� �ۼ��Ѵ�.
	// POSITION �������Ϳ� �ִ� ���� �����ڴٴ� �ǹ��̴�.
	// �ڿ��� �������� ��ȣ�� ���� �� �ִ�. POSITION1 �̷������� �ۼ��� �����ϴ�.
	// �Ⱥٿ��� ��쿡�� 0���� �ڵ����� ������ �ȴ�.
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

struct VS_OUTPUT2_UV
{
	// SV �� ������ System Value �̴�.
	// �� �������� Shader �ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ����ϴ�.
	// ���� �������� ��ȯ�� ������ SV_POSITION �������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	// ȭ����������� ��ȯ�� �Ͼ�� �ȴ�.
	float4  Pos : SV_POSITION;
	float2  UV : TEXCOORD;
	float4	ProjPos : POSITION;
	float   clip : SV_ClipDistance0;
	float   clip1 : SV_ClipDistance1;
};

VS_OUTPUT2_UV Standard2DTitleVS(VS_INPUT2_UV input)
{
	VS_OUTPUT2_UV output = (VS_OUTPUT2_UV)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;
	
	float4  clip = float4(0.f, 1.f, 0.f, input.Pos.y/2.f-0.1f);
	float4  clip1 = float4(0.f, -1.f, 0.f, input.Pos.y);
	//	float4  clip1 = float4(0.f, -0.2f, 0.f, 0.f);
		//float4  clip1 = float4()
		// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	//output.
	output.Pos = output.ProjPos;
	output.UV = ComputeAnimation2DUV(input.UV);
	output.clip = dot(mul(float4(Pos, 1.f), g_matWVP), clip);
	output.clip1 = dot(mul(float4(Pos, 1.f), g_matWVP), clip1);
	return output;
}


PS_OUTPUT_SINGLE Standard2DTitlePS(VS_OUTPUT2_UV input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	result = (float4)0.f;

	//result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb *0.5f + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.a = BaseColor.a * g_MtrlOpacity;


	output.Color = result;

	return output;
}


struct VS_INPUT3_UV
{
	// : �ڿ� Semantic �� �ۼ��Ѵ�.
	// POSITION �������Ϳ� �ִ� ���� �����ڴٴ� �ǹ��̴�.
	// �ڿ��� �������� ��ȣ�� ���� �� �ִ�. POSITION1 �̷������� �ۼ��� �����ϴ�.
	// �Ⱥٿ��� ��쿡�� 0���� �ڵ����� ������ �ȴ�.
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

struct VS_OUTPUT3_UV
{
	// SV �� ������ System Value �̴�.
	// �� �������� Shader �ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ����ϴ�.
	// ���� �������� ��ȯ�� ������ SV_POSITION �������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	// ȭ����������� ��ȯ�� �Ͼ�� �ȴ�.
	float4  Pos : SV_POSITION;
	float2  UV : TEXCOORD;
	float4	ProjPos : POSITION;
	float   clip : SV_ClipDistance0;
	float   clip1 : SV_ClipDistance1;
};

VS_OUTPUT3_UV Standard2DLogVS(VS_INPUT3_UV input)
{
	VS_OUTPUT3_UV output = (VS_OUTPUT3_UV)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;

	float4  clip = float4(0.f, 1.f, 0.f, 0.8f);
	float4  clip1 = float4(0.f, -1.f, 0.f, 0.8f);
	//	float4  clip1 = float4(0.f, -0.2f, 0.f, 0.f);
		//float4  clip1 = float4()
		// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	//output.
	output.Pos = output.ProjPos;
	output.UV = ComputeAnimation2DUV(input.UV);
	output.clip = dot(mul(float4(Pos, 1.f), g_matWVP), clip);
	output.clip1 = dot(mul(float4(Pos, 1.f), g_matWVP), clip1);
	return output;
}


PS_OUTPUT_SINGLE Standard2DLogPS(VS_OUTPUT3_UV input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	result = (float4)0.f;

	//result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb *0.5f + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.a = BaseColor.a * g_MtrlOpacity;


	output.Color = result;

	return output;
}





struct VS_INPUT4_UV
{
	// : �ڿ� Semantic �� �ۼ��Ѵ�.
	// POSITION �������Ϳ� �ִ� ���� �����ڴٴ� �ǹ��̴�.
	// �ڿ��� �������� ��ȣ�� ���� �� �ִ�. POSITION1 �̷������� �ۼ��� �����ϴ�.
	// �Ⱥٿ��� ��쿡�� 0���� �ڵ����� ������ �ȴ�.
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

struct VS_OUTPUT4_UV
{
	// SV �� ������ System Value �̴�.
	// �� �������� Shader �ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ����ϴ�.
	// ���� �������� ��ȯ�� ������ SV_POSITION �������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	// ȭ����������� ��ȯ�� �Ͼ�� �ȴ�.
	float4  Pos : SV_POSITION;
	float2  UV : TEXCOORD;
	float4	ProjPos : POSITION;
	float   clip : SV_ClipDistance0;
	float   clip1 : SV_ClipDistance1;
};

VS_OUTPUT3_UV Standard2DRangeVS(VS_INPUT4_UV input)
{
	VS_OUTPUT4_UV output = (VS_OUTPUT4_UV)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;

	float4  clip = float4(0.f, 1.f, 0.f, 0.35f);
	float4  clip1 = float4(0.f, -1.f, 0.f, 0.80f);
	//	float4  clip1 = float4(0.f, -0.2f, 0.f, 0.f);
		//float4  clip1 = float4()
		// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	//output.
	output.Pos = output.ProjPos;
	output.UV = ComputeAnimation2DUV(input.UV);
	output.clip = dot(mul(float4(Pos, 1.f), g_matWVP), clip);
	output.clip1 = dot(mul(float4(Pos, 1.f), g_matWVP), clip1);
	return output;
}


PS_OUTPUT_SINGLE Standard2DRangePS(VS_OUTPUT4_UV input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	result = (float4)0.f;

	//result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb *0.5f + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.a = BaseColor.a * g_MtrlOpacity;


	output.Color = result;

	return output;
}
