#include "stdafx.h"
#include "GameMgr.h"
#include "KeyMgr.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"

IMPLEMENT_SINGLETON(CGameMgr)

CGameMgr::CGameMgr():m_bCollision(false)
{
}


CGameMgr::~CGameMgr()
{
	Release();
}

void CGameMgr::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Option01.bmp", L"Option01");

	m_bGameLose = false;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			MAPINFO * pMapInfo = new MAPINFO;
			pMapInfo->index = INDEX(j,i);
			m_vecMapInfo.emplace_back(pMapInfo);
		}
	}

	iNumOfBomb = 0;
	iLengthOfBomb = 0;
	m_bReload = false;
}

void CGameMgr::Update()
{
	if (CKeyMgr::Get_Instance()->KeyPressing('C'))
	{
		m_bCollision = true;
	}
	else m_bCollision = false;

	if (CKeyMgr::Get_Instance()->KeyUP('S'))
	{
		SceneID::ID eSceneID = CSceneMgr::Get_Instance()->Get_SceneID();

		switch (eSceneID)
		{
		case SceneID::SCENE_LOGO:
			break;
		case SceneID::SCENE_MENU:
			break;
		case SceneID::SCENE_EDIT:
			break;
		case SceneID::SCENE_STAGE:
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE2);
			break;
		case SceneID::SCENE_STAGE2:
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE3);
			break;
		case SceneID::SCENE_STAGE3:
			break;
		case SceneID::SCENE_END:
			break;
		default:
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyUP('R'))
	{
		SceneID::ID eSceneID = CSceneMgr::Get_Instance()->Get_SceneID();
		
		switch (eSceneID)
		{
		case SceneID::SCENE_LOGO:
			break;
		case SceneID::SCENE_MENU:
			break;
		case SceneID::SCENE_EDIT:
			break;
		case SceneID::SCENE_STAGE:
			m_bReload = true;
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE);
			m_bReload = false;
			break;
		case SceneID::SCENE_STAGE2:
			m_bReload = true;
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE2);
			m_bReload = false;
			break;
		case SceneID::SCENE_STAGE3:
			m_bReload = true;
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE3);
			m_bReload = false;
			break;
		case SceneID::SCENE_END:
			break;
		default:
			break;
		}
	}


}

void CGameMgr::LateUpdate()
{
}

void CGameMgr::Render(HDC hDC)
{

	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
	
			int iIndex = i + (j * TILEX);

			if (0 > iIndex || m_vecMapInfo.size() <= (size_t)iIndex)
				return;

			if (m_vecMapInfo[iIndex]->bIsBoom)
			{
 				/*cout <<"Boom Index : "<< i << ", " << j << endl;
				HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Option01");
				POINT pos = Get_Posiotn_From_Index(m_vecMapInfo[iIndex]->index);
				BitBlt(hDC, pos.x-20.f, pos.y-20.f, 40.f, 40.f, hMemDC, 0, 0, SRCCOPY);
			*/
			}
		}
	}
}

void CGameMgr::Release()
{
	for (auto& pMapInfo : m_vecMapInfo)
	{
		if (pMapInfo)
		{
			delete pMapInfo;
			pMapInfo = nullptr;
		}
	}
	m_vecMapInfo.clear();
	m_vecMapInfo.shrink_to_fit();
}

// ÁÂÇ¥ ÁÖ¸é °¡Àå °¡±î¿î Å¸ÀÏ ÁßÁ¡ ¹ÝÈ¯
POINT CGameMgr::Get_Tile_Positon_From_Position(POINT _pos)
{
	POINT TilePos;
	INDEX index;
	
	index.x = (_pos.x - OFFSET_X) / TILESIZEX;
	index.y = (_pos.y - OFFSET_Y) / TILESIZEY;

	TilePos.x = OFFSET_X + index.x * TILESIZEX + TILESIZEX/2;
	TilePos.y = OFFSET_Y + index.y * TILESIZEY + TILESIZEY/2;

	return TilePos;
}
// ÀÎµ¦½º ÁÖ¸é ÁÂÇ¥ ÁÖ´Â ¾Ö
POINT CGameMgr::Get_Posiotn_From_Index(INDEX _index)
{
	POINT pos;

	pos.x = (_index.x * TILESIZEX) + OFFSET_X + TILESIZEX/2;
	pos.y = (_index.y * TILESIZEY) + OFFSET_Y + TILESIZEY/2;

	return pos;
}

RECT CGameMgr::Get_Rect_From_Position(POINT _pos, float _fCX, float _fCY)
{
	RECT rect;
	rect.left = LONG(_pos.x - (_fCX * 0.5f));
	rect.top = LONG(_pos.y - (int(_fCY) >> 1));
	rect.right = LONG(_pos.y + (_fCX * 0.5f));
	rect.bottom = LONG(_pos.y + (int(_fCY) >> 1));

	

	return rect;
}

RECT CGameMgr::GET_Rect_From_Index(INDEX _index, float _fCX, float _fCY)
{
	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(_index);
	RECT rect = CGameMgr::Get_Instance()->Get_Rect_From_Position(pos, _fCX, _fCY);
	return rect;
}

MAPINFO * CGameMgr::Get_MapInfo(INDEX _index)
{
	int iIndex = _index.x + (_index.y* TILEX);

	if (0 > iIndex || m_vecMapInfo.size() <= (size_t)iIndex)
		return nullptr;

	return m_vecMapInfo[iIndex];
}

void CGameMgr::Set_MapInfo(INDEX _index, bool _bIsExist, bool _bIsBoom)
{
	int iIndex = _index.x + (_index.y* TILEX);

	if (0 > iIndex || m_vecMapInfo.size() <= (size_t)iIndex)
		return;

	m_vecMapInfo[iIndex]->bIsExist = _bIsExist;
	m_vecMapInfo[iIndex]->bIsBoom = _bIsBoom;
}



POINT CGameMgr::Get_Tile_Positon_From_Position(float _posX, float _posY)
{
	POINT TilePos;
	INDEX index;

	index.x = (_posX - OFFSET_X) / TILESIZEX;
	index.y = (_posY - OFFSET_Y) / TILESIZEY;

	TilePos.x = OFFSET_X + index.x * TILESIZEX + TILESIZEX / 2;
	TilePos.y = OFFSET_Y + index.y * TILESIZEY + TILESIZEY / 2;

	return TilePos;
}

// ÁÂÇ¥ ÁÖ¸é ÀÎµ¦½º ÁÜ
INDEX CGameMgr::Get_Index_From_Position(POINT _pos)
{
	INDEX index;
	index.x = (_pos.x - OFFSET_X) / TILESIZEX;
	index.y = (_pos.y - OFFSET_Y) / TILESIZEY;
	return index;
}

INDEX CGameMgr::Get_Index_From_Position(float _posX, float _posY)
{
	INDEX index;
	index.x = (_posX - OFFSET_X) / TILESIZEX;
	index.y = (_posY - OFFSET_Y) / TILESIZEY;
	return index;
}

