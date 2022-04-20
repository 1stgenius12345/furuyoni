
#include "Viewport.h"

CViewport::CViewport()	:
	m_Camera(nullptr),
	m_bRender(true)
{
}

CViewport::~CViewport()
{

}

void CViewport::Start()
{
	if (!m_bRender)
		return;
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CViewport::Init()
{
	m_Camera = new CCamera;

	m_Camera->SetName("UICamera");
	m_Camera->m_pScene = m_Scene;

	m_Camera->Init();
	m_Camera->SetCameraType(Camera_Type::CamUI);

	m_Camera->Release();

	return true;
}

void CViewport::Update(float DeltaTime)
{
	if (!m_bRender)
		return;
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(DeltaTime);
	}
}

void CViewport::PostUpdate(float DeltaTime)
{
	if (!m_bRender)
		return;
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(DeltaTime);
	}
}

void CViewport::Render()
{

	if (!m_bRender)
		return;
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}
