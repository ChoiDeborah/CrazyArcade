#include "stdafx.h"
#include "Stage2.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "BitmapMgr.h"
#include "TileMgr.h"
#include "GameMgr.h"
#include "CollisionMgr.h"
#include "Item.h"
#include "SoundMgr.h"
#include "SceneMgr.h"


CStage2::CStage2() :m_bGameEnd(true), m_bGameStart(true), m_bWin(false), m_bLose(false), m_bResult(false)
{

}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage1.wav");
	CSoundMgr::Get_Instance()->PlayBGM(L"gamestart.wav", CSoundMgr::UI);
	CGameMgr::Get_Instance()->Initialize();
	// 타일 로드 전 타일 오브젝트 리스트 비워주기

	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Stage2.dat");
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(8, 6));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(14, 12));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(12, 10));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(0, 12));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(2, 10));

	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(0, 0));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(2, 2));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(12, 2));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(14, 0));
	
	//물풍선 추가
	CObj* pObj = CAbstractFactory<CItem>::Create(0, 11);
	dynamic_cast<CItem*>(pObj)->Set_Type((int)ITEM::BOMB);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(0, 0);
	dynamic_cast<CItem*>(pObj)->Set_Type((int)ITEM::BOMB);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(14, 1);
	dynamic_cast<CItem*>(pObj)->Set_Type((int)ITEM::BOMB);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(13, 11);
	dynamic_cast<CItem*>(pObj)->Set_Type((int)ITEM::BOMB);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	// 물약

	pObj = CAbstractFactory<CItem>::Create(0, 1);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::BOMBLEN);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(13, 0);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::BOMBLEN);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(14, 11);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::BOMBLEN);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(1, 12);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::BOMBLEN);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	// 발

	pObj = CAbstractFactory<CItem>::Create(0, 12);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(0, 0);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(14, 0);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);
	pObj = CAbstractFactory<CItem>::Create(14, 12);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	
	m_dwGameStartTime = GetTickCount();
	CGameMgr::Get_Instance()->m_bGameLose = false;
}

void CStage2::Update()
{
	if (m_dwGameStartTime + 2000 < GetTickCount())
	{
		m_bGameEnd = false;
		m_bGameStart = false;
	}

	
	CGameMgr::Get_Instance()->Update();
	if (!m_bGameEnd)
		CObjMgr::Get_Instance()->Update();

	if (CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER).empty())
	{
		m_bGameEnd = true;
		m_bWin = true;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE3);
		}

	}
}

void CStage2::LateUpdate()
{
	CGameMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
	CCollisionMgr::CollisionRectEX(CTileMgr::Get_Instance()->Get_TileVector(), CObjMgr::Get_Instance()->Get_Player());

	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::ITEM), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::ITEM, OBJID::PLAYER);
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);
	CCollisionMgr::CollisionRectMonstrBomb(CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB));

	// 물풍선 아이템 충돌 처리
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);

	CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), OBJID::TILE, OBJID::BOMB);
	// 물풍선 플레이어
	CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::BOMB, OBJID::PLAYER);
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), OBJID::BOMB, OBJID::TILE);

}

void CStage2::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Background");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Stage_1");
	BitBlt(hDC, OFFSET_X, OFFSET_Y, MAPSIZEX, MAPSIZEY, hMemDC, 0, 0, SRCCOPY);


	CGameMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	if (m_bGameStart)
	{
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"GameStart");

		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			200, 200, //출력될 위치의 xy 좌표 
			284, 92, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			0, // 시작 위치 
			284, 92,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}

	if (m_bLose)
	{
		//m_bLose = false
		if (!m_bResult)
		{
			m_bResult = true;
			CSoundMgr::Get_Instance()->PlayBGM(L"GameOver.wav", CSoundMgr::UI);
		}
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"GameOver");

		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			250, 200, //출력될 위치의 xy 좌표 
			194, 94, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			0, // 시작 위치 
			194, 94,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}

	if (m_bWin)
	{
		//m_bWin = false;
		if (!m_bResult)
		{
			m_bResult = true;
			CSoundMgr::Get_Instance()->PlayBGM(L"GameClear.wav", CSoundMgr::UI);
		}
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Clear");

		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			250, 200, //출력될 위치의 xy 좌표 
			234, 36, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			0, // 시작 위치 
			234, 36,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}

}

void CStage2::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// 스테이지 종료시 몬스터 삭제
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::TILE);
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CGameMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->StopAll();

}
