#include "stdafx.h"
#include "Tile.h"
#include "BitmapMgr.h"
#include "GameMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CTile::CTile()
	:m_iDrawID(0),
	m_iOption(0),
	m_iHeight(0),
	m_bIsBoom(false)
	, m_bMonsterPass(true)
{
	m_eOBJID = OBJID::TILE;
	m_bFlat = false;
	ZeroMemory(&m_tPrevIndex, sizeof(INDEX));
}


CTile::~CTile()
{
}

void CTile::Initialize()
{
	// 타일 추가
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_1.bmp", L"Camp_Tile_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_2.bmp", L"Camp_Tile_2");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_3.bmp", L"Camp_Tile_3");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_4.bmp", L"Camp_Tile_4");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_5.bmp", L"Camp_Tile_5");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_6.bmp", L"Camp_Tile_6");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_7.bmp", L"Camp_Tile_7");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_8.bmp", L"Camp_Tile_8");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_9.bmp", L"Camp_Tile_9");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_10.bmp", L"Camp_Tile_10");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_11.bmp", L"Camp_Tile_11");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_12.bmp", L"Camp_Tile_12");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_13.bmp", L"Camp_Tile_13");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_14.bmp", L"Camp_Tile_14");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Camp/Camp_Tile_15.bmp", L"Camp_Tile_15");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Option00.bmp", L"Option00");

	m_tInfo.fCX = (float)TILESIZEX;
	m_tInfo.fCY = (float)TILESIZEY;

	m_bIsPass = false;
	m_bIsBroken = false;
	m_bIsPush = false;	
}

int CTile::Update()
{
	/*POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = (float)pos.x;
	m_tInfo.fY = (float)pos.y;*/
	return OBJ_NOEVENT;
}

void CTile::LateUpdate()
{
	CObj::UpdateIndex();

	Check_Move_Tile();
}

void CTile::Check_Move_Tile()
{
	if (m_tPrevIndex != m_tIndex) 
	{
		CTile * pCurTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex);
		CTile* pPrevTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tPrevIndex);
		pCurTile->Set_Option(m_iOption);
		pPrevTile->Set_Option(0);
		//pPrevTile->reset_option(0);
		m_tPrevIndex = m_tIndex;
		/*CTile * pCurTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex);
		CTile* pPrevTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tPrevIndex);
		int tempCurOption = pCurTile->Get_Option();
		pCurTile->m_bIsPass(false);
		pPrevTile->m_bisP;
		*////m_tPrevIndex = m_tIndex;
	}
}


void CTile::Render(HDC hDC)
{
	UpdateRect();
	
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left, m_tRect.top - (m_iHeight- m_tInfo.fCY) , //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_iHeight, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		0, 0,
		m_tInfo.fCX, m_iHeight,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);

	if (!m_bIsPass && m_iOption != 0 && CGameMgr::Get_Instance()->m_bCollision)
	{
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Option00");
			
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tInfo.fX - 20.f, m_tInfo.fY - 20.f,  //출력될 위치의 xy 좌표 
			TILESIZEX, TILESIZEY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0, 0,
			TILESIZEX, TILESIZEY,// 출력할 비트맵의 전체 가로세로 길이.
			RGB(255, 255, 255)
		);
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('C')) 
	{
		TCHAR buff[1024] = L"";
		swprintf_s(buff, L" %d", m_iOption);
		TextOut(hDC, m_tInfo.fX, m_tInfo.fY, buff, lstrlen(buff));
	}
	
}

void CTile::Release()
{
}

void CTile::Set_Option(int _iOption)
{
	//CObj::UpdateIndex();
	m_iOption = _iOption;
	m_tPrevIndex = m_tIndex;

	switch (m_iOption)
	{
	case 0:
		m_bIsPass = true;
		m_bIsBroken = false;
		m_bIsPush = false;
		
		m_pFrameKey = L"";
		m_iHeight = 40.f;

		break;
	case 1:
		m_bIsPass = true;
		m_bIsBoom = true;
		m_bIsBroken = false;
		m_bIsPush = false;
		m_bFlat = true;
	
		m_iHeight = 40.f;
		m_pFrameKey = L"Camp_Tile_1";
		break;
	case 2:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;
	
		m_iHeight = 49.f;
		m_pFrameKey = L"Camp_Tile_2";
		break;
	case 3:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 49.f;
		m_pFrameKey = L"Camp_Tile_3";
		break;
	case 4:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;
	
		m_iHeight = 58.f;
		m_pFrameKey = L"Camp_Tile_4";
		break;
	case 5:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = true;

		m_iHeight = 49.f;
		m_pFrameKey = L"Camp_Tile_5";
		break;
	case 6:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = true;
	
		m_iHeight = 49.f;
		m_pFrameKey = L"Camp_Tile_6";
		break;
	case 7:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = true;

		m_iHeight = 49.f;
		m_pFrameKey = L"Camp_Tile_7";
		break;
	case 8:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 58.f;
		m_pFrameKey = L"Camp_Tile_8";
		break;
	case 9:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = true;

		m_iHeight = 46.f;
		m_pFrameKey = L"Camp_Tile_9";
		break;
	case 10:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = true;

		m_iHeight = 46.f;
		m_pFrameKey = L"Camp_Tile_10";
		break;
	case 11:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 59.f;
		m_pFrameKey = L"Camp_Tile_11";
		break;
	case 12:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 59.f;
		m_pFrameKey = L"Camp_Tile_12";
		break;
	case 13:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 59.f;
		m_pFrameKey = L"Camp_Tile_13";
		break;
	case 14:
		m_bIsPass = false;
		m_bIsBroken = false;
		m_bIsPush = false;

		m_iHeight = 59.f;
		m_pFrameKey = L"Camp_Tile_14";
		break;
	case 15:
		m_bIsPass = false;
		m_bIsBroken = true;
		m_bIsPush = false;

		m_iHeight = 44.f;
		m_pFrameKey = L"Camp_Tile_15";
		break;
	default:
		break;
	}
	// 타일 번호에 따라 프레임 키 정해주기.
	

	if (!m_bIsPass)
		CGameMgr::Get_Instance()->Set_MapInfo(m_tIndex, true, false);
	

}

void CTile::Create_Item()
{
	CObj* pObj = CAbstractFactory<CItem>::Create();
	dynamic_cast<CItem*>(pObj)->Set_Index(m_tIndex);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
}

void CTile::Update_Option()
{
	CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex)->Set_Option(m_iOption);
}


void CTile::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY - 20.f);
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (int(m_tInfo.fCY) >> 1));
	
}

void CTile::Set_Tile_Size(float _fCX, float _fCY)
{
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
}

Point CTile::GET_Tile_Pos()
{
	Point temp = { m_tInfo.fX, m_tInfo.fY };
	return temp;
}

