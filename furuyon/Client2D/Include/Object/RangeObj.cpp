
#include "RangeObj.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Device.h"
CRangeObj::CRangeObj()
{
	m_front = false;
	m_back = false;
}

CRangeObj::CRangeObj(const CRangeObj& obj) :
	CGameObject(obj)
{

}

CRangeObj::~CRangeObj()
{
}

void CRangeObj::Start()
{
	CGameObject::Start();
}

bool CRangeObj::Init()
{
	CGameObject::Init();
	

	m_Sprite = CreateSceneComponent<CSpriteComponent>("CRangeObj");
	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativeScale(208.f,71.f,0.f);
	m_Sprite->SetRelativePos(640.f, 230.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_BACKMAP);


	m_SpriteMtrl = m_Sprite->GetMaterial(0);
	m_SpriteMtrl->AddTexture("Range", TEXT("Range.png"));
	m_SpriteMtrl->SetEmissiveColor(1.5f, 1.5f, 1.5f, 1.5f);
	m_SpriteMtrl->SetShader("Standard2DRangeShader");

	return true;
}

void CRangeObj::Update(float DeltaTime)
{
	Resolution	RS = CDevice::GetInst()->GetResolution();

	Vector2	Center;
	Center.x = RS.Width / 2.f;
	Center.y = RS.Height / 2.f;
	if (m_front)
	{
		Vector3 EndPoint = Vector3(0.f, SettingPos(m_index), 0.f);
		EndPoint = EndPoint - GetRelativePos();

		if (EndPoint.y <= 0)
		{
			m_Sprite->AddRelativePos(0.f, EndPoint.y * DeltaTime * 15.f - DeltaTime * 10.f, 0.f);
		}
		else
		{
			Settingindex(m_index);
			m_front = false;

		}
	
		float Ratio = 416.f / 142.f;
		Vector3 EndPoint2 = Vector3(416.f / (12.f - (float)m_index), 142.f / (12.f - (float)m_index), 0.f);
		EndPoint2 = EndPoint2 - GetRelativeScale();
		if (EndPoint2.y >= 0)
		{
			m_Sprite->AddRelativeScale(Ratio *(EndPoint2.y * DeltaTime * 10.f + DeltaTime * 3.f), EndPoint2.y * DeltaTime * 10.f + DeltaTime * 3.f, 0.f);
		}
		


	}

	

	if (m_back)
	{
		Vector3 EndPoint = Vector3(0.f, SettingPos(m_index), 0.f);
		EndPoint = EndPoint - GetRelativePos();

		if (EndPoint.y >= 0)
		{
			m_Sprite->AddRelativePos(0.f, EndPoint.y * DeltaTime * 15.f + DeltaTime * 10.f, 0.f);
		}
		else
		{
			Settingindex(m_index);
			m_back = false;

		}



		float Ratio = 416.f / 142.f;
		Vector3 EndPoint2 = Vector3(416.f / (12.f - (float)m_index), 142.f / (12.f - (float)m_index), 0.f);
		EndPoint2 = EndPoint2 - GetRelativeScale();
		if (EndPoint2.y <= 0)
		{
			m_Sprite->AddRelativeScale(Ratio * (EndPoint2.y * DeltaTime * 10.f - DeltaTime * 3.f), EndPoint2.y * DeltaTime * 10.f - DeltaTime * 3.f, 0.f);
		}
	
	}


}

void CRangeObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CRangeObj::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CRangeObj::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CRangeObj* CRangeObj::Clone()
{
	return new CRangeObj(*this);
}

void CRangeObj::Animation2DNotify(const std::string& Name)
{
}

void CRangeObj::Settingindex(int i)
{
	m_index = i;
	m_Sprite->SetRelativeScale(416.f / (12.f -(float)m_index), 142.f/(12.f - (float)m_index), 0.f);

	m_Sprite->SetRelativePos(640.f, SettingPos(m_index),0.f);

}

void CRangeObj::RangeUp()
{
	
	m_index -= 1;

	m_back = true;
	

}

void CRangeObj::RangeDown()
{



	m_index += 1;

	m_front = true;
	
}

float CRangeObj::SettingPos(int index)
{
	if (index >= 11)
	{
		return 100.f;
	}
	switch (index)
	{
	case 1:
		return 586.f;
		break;
	case 2:
		return 565.f;
		break;
	case 3:
		return 543.f;
		break;
	case 4:
		return 521.f;
		break;
	case 5:
		return 498.f;
		break;
	case 6:
		return 475.f;
		break;
	case 7:
		return 450.f;
		break;
	case 8:
		return 422.f;
		break;
	case 9:
		return 390.f;
		break;
	case 10:
		return 325.f;
		break;
	case 11:
		return 200.f;
		break;
	default:
		break;
	}
}
