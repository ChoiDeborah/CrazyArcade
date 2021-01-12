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
			// ������ ������ ��ȯ
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
	
	// ��ǳ�� ������ �浹 ó��
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);
	// ������ ��ǳ�� �浹ó��
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS), OBJID::BOMB, OBJID::BOSS);

	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::BOSS, OBJID::EXTRA_BOMB);
	// ��ǳ�� �÷��̾�
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

		GdiTransparentBlt(hDC, // ���� ������� DC
			200, 200, //��µ� ��ġ�� xy ��ǥ 
			284, 92, // ����� ��Ʈ���� ���μ��� ������. 
			hMemDC,
			0,
			0, // ���� ��ġ 
			284, 92,// ����� ��Ʈ���� ��ü ���μ��� ����. 
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

		GdiTransparentBlt(hDC, // ���� ������� DC
			250, 200, //��µ� ��ġ�� xy ��ǥ 
			194, 94, // ����� ��Ʈ���� ���μ��� ������. 
			hMemDC,
			0,
			0, // ���� ��ġ 
			194, 94,// ����� ��Ʈ���� ��ü ���μ��� ����. 
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

		GdiTransparentBlt(hDC, // ���� ������� DC
			250, 200, //��µ� ��ġ�� xy ��ǥ 
			234, 36, // ����� ��Ʈ���� ���μ��� ������. 
			hMemDC,
			0,
			0, // ���� ��ġ 
			234, 36,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255, 255, 255)
		);
	}
}

void CStage3::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// �������� ����� ���� ����
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BOSS);
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::TILE);
	CGameMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->StopAll();

}
