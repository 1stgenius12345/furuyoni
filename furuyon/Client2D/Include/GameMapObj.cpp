#include "GameMapObj.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CGameMapObj::CGameMapObj()
{
}

CGameMapObj::CGameMapObj(const CGameMapObj& obj) :
	CGameObject(obj)
{

}

CGameMapObj::~CGameMapObj()
{
}

void CGameMapObj::Start()
{
	CGameObject::Start();
}

bool CGameMapObj::Init()
{
	CGameObject::Init();

	m_TileMap = CreateSceneComponent<CTileMapComponent>("TileMap");

	SetRootComponent(m_TileMap);

	m_TileMap->Load(TEXT("MainMap.map"));

	/*m_TileMap->CreateTile<CTile>(Tile_Shape::Rhombus, 100, 100, Vector2(160.f, 80.f));

	m_TileMap->SetMaterial(0, "MainMap");
	m_TileMap->SetFrameMax(5, 76);
	m_TileMap->SetTileDefaultFrame(3, 2);*/

	//m_TileMap->SetRelativePos(100.f, 500.f, 0.f);

	/*m_TileMap->CreateTile<CTile>(Tile_Shape::Rect, 100, 100, Vector2(64.f, 64.f));

	m_TileMap->SetMaterial(0, "MainMapRect");
	m_TileMap->SetFrameMax(1, 5);
	m_TileMap->SetTileDefaultFrame(0, 0);*/

	return true;
}

void CGameMapObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

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
