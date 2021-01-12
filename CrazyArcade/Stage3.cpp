#include "stdafx.h"
#include "Stage3.h"

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
#include "Boss.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Item.h"
CStage3::CStage3():m_bGameEnd(true), m_bGameStart(true), m_bWin(false), m_bLose(false), m_bResult(false)
{
}


CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage3.wav");
	CSoundMgr::Get_Instance()->PlaySoundW(L"gamestart.wav", CSoundMgr::UI);
	CGameMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(10, 6));
	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Stage3.dat");

	CObjMgr::Get_Instance()->AddObject(OBJID::BOSS, CAbstractFactory<CBoss>::Create(7, 6));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(12, 7));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(12, 5));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(2, 5));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(2, 7));
	CGameMgr::Get_Instance()->m_bGameLose = false;


	CObj* pObj = CAbstractFactory<CItem>::Create(9, 5);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	pObj = CAbstractFactory<CItem>::Create(9, 7);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	pObj = CAbstractFactory<CItem>::Create(5, 5);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	pObj = CAbstractFactory<CItem>::Create(5, 7);
	dynamic_cast<CItem*>(pObj)->Set_Type(ITEM::SHOE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pObj);

	m_dwGameStartTime = GetTickCount();
}

void CStage3::Update()
{
	if (m_dwGameStartTime + 2000 < GetTickCount())
	{
		m_bGameEnd = false;
		m_bGameStart = false;
	}

	CGameMgr::Get_Instance()->Update();

	if (!m_bGameEnd)
		CObjMgr::Get_Instance()->Update();


	if (CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS).empty())
	{
		m_bGameEnd = true;
		m_bWin = true;
		CSoundMgr::Get_Instance()->StopAll();
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{
			// 마지막 신으로 전환
			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_END);
		}

	}



}

void CStage3::LateUpdate()
{
	CGameMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
	CCollisionMgr::CollisionRectEX(CTileMgr::Get_Instance()->Get_TileVector(), CObjMgr::Get_Instance()->Get_Player());
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::ITEM), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::ITEM, OBJID::PLAYER);
	
	//CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::MONSTER, OBJID::EXTRA_BOMB);
	CCollisionMgr::CollisionRectMonstrBomb(CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB));
	
	// 물풍선 아이템 충돌 처리
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);
	// 보스랑 물풍선 충돌처리
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS), OBJID::BOMB, OBJID::BOSS);

	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::BOSS, OBJID::EXTRA_BOMB);
	// 물풍선 플레이어
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::BOMB, OBJID::PLAYER);

	CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), OBJID::TILE, OBJID::BOMB);
	
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), OBJID::BOMB, OBJID::TILE);
	

	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::BOSS, OBJID::PLAYER);

}

void CStage3::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Background");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Stage_1");
	BitBlt(hDC, OFFSET_X, OFFSET_Y, MAPSIZEX, MAPSIZEY, hMemDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	CGameMgr::Get_Instance()->Render(hDC);
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

	if (CGameMgr::Get_Instance()->m_bGameLose)
	{
		//m_bLose = false;
		if (!m_bResult)
		{
			m_bResult = true;
			CSoundMgr::Get_Instance()->PlaySoundW(L"GameOver.wav", CSoundMgr::UI);
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
			CSoundMgr::Get_Instance()->PlaySoundW(L"GameClear.wav", CSoundMgr::UI);
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

void CStage3::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// 스테이지 종료시 몬스터 삭제
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BOSS);
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::TILE);
	CGameMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->StopAll();

}
