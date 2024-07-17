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
	// Ÿ�� �ε� �� Ÿ�� ������Ʈ ����Ʈ ����ֱ�

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
	
	//��ǳ�� �߰�
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

	// ����

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

	// ��

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

	// ��ǳ�� ������ �浹 ó��
	CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);

	CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), OBJID::TILE, OBJID::BOMB);
	// ��ǳ�� �÷��̾�
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

	if (m_bLose)
	{
		//m_bLose = false
		if (!m_bResult)
		{
			m_bResult = true;
			CSoundMgr::Get_Instance()->PlayBGM(L"GameOver.wav", CSoundMgr::UI);
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
			CSoundMgr::Get_Instance()->PlayBGM(L"GameClear.wav", CSoundMgr::UI);
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

void CStage2::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// �������� ����� ���� ����
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::TILE);
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CGameMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->StopAll();

}
