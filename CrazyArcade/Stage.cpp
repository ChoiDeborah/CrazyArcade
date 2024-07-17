#include "stdafx.h"
#include "Stage.h"

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

CStage::CStage():m_bGameEnd(true), m_bGameStart(true), m_bWin(false), m_bLose(false), m_bResult(false)
{

}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage1.wav");
	CSoundMgr::Get_Instance()->PlayBGM(L"gamestart.wav", CSoundMgr::UI);



	CGameMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(10, 6));

	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(4, 4));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(10, 4));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(10, 8));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(4, 8));

	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(14, 12));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(14, 0));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(0, 0));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CMonster>::Create(0, 12));

	CObjMgr::Get_Instance()->AddObject(OBJID::MOUSE, CAbstractFactory<CMouse>::Create());




	CObj* pItem = CAbstractFactory<CItem>::Create();
	dynamic_cast<CItem*>(pItem)->Set_Type(5);
	dynamic_cast<CItem*>(pItem)->Set_Index(INDEX(10, 5));
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	
	pItem = CAbstractFactory<CItem>::Create();
	dynamic_cast<CItem*>(pItem)->Set_Type(5);
	dynamic_cast<CItem*>(pItem)->Set_Index(INDEX(5, 4));
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	pItem = CAbstractFactory<CItem>::Create();
	dynamic_cast<CItem*>(pItem)->Set_Type(5);
	dynamic_cast<CItem*>(pItem)->Set_Index(INDEX(4, 7));
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	pItem = CAbstractFactory<CItem>::Create();
	dynamic_cast<CItem*>(pItem)->Set_Type(5);
	dynamic_cast<CItem*>(pItem)->Set_Index(INDEX(9, 8));
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);


	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Stage1.dat");

	m_dwGameStartTime = GetTickCount();
}

void CStage::Update()
{
	if (m_dwGameStartTime + 2000 < GetTickCount())
	{
		m_bGameEnd = false;
		m_bGameStart = false;
	}

	CGameMgr::Get_Instance()->Update();
	if(!m_bGameEnd)
		CObjMgr::Get_Instance()->Update();

	if (CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER).empty())
	{
		m_bGameEnd = true;
		m_bWin = true;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{



			CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE2);
		}

	}
	
	//CTileMgr::Get_Instance()->Update();
}

void CStage::LateUpdate()
{
	if (!m_bGameEnd) 
	{
		CGameMgr::Get_Instance()->LateUpdate();
		CTileMgr::Get_Instance()->LateUpdate();
		CObjMgr::Get_Instance()->LateUpdate();
		CCollisionMgr::CollisionRectEX(CTileMgr::Get_Instance()->Get_TileVector(), CObjMgr::Get_Instance()->Get_Player());
		CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::ITEM), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::ITEM, OBJID::PLAYER);
		CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), OBJID::PLAYER, OBJID::MONSTER);
		//CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::MONSTER, OBJID::EXTRA_BOMB);
		CCollisionMgr::CollisionRectMonstrBomb(CObjMgr::Get_Instance()->Get_Objlist(OBJID::MONSTER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB));
		CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::ITEM), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::ITEM, OBJID::EXTRA_BOMB);
		//CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::PLAYER, OBJID::EXTRA_BOMB);
		//CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::EXTRA_BOMB), OBJID::BOMB, OBJID::EXTRA_BOMB);
		//CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), OBJID::BOMB, OBJID::BOMB);
		CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), OBJID::TILE, OBJID::BOMB);
		// ��ǳ�� �÷��̾�
		CCollisionMgr::CollisionRectEX(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::PLAYER), OBJID::BOMB, OBJID::PLAYER);
		CCollisionMgr::CollisionRect(CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB), CObjMgr::Get_Instance()->Get_Objlist(OBJID::TILE), OBJID::BOMB, OBJID::TILE);


	}

}
void CStage::Render(HDC hDC)
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

	if (CGameMgr::Get_Instance()->m_bGameLose)
	{
		//m_bLose = false;
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

void CStage::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// �������� ����� ���� ����
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::TILE);
	CObjMgr::Get_Instance()->DeleteID(OBJID::BOMB);
	CObjMgr::Get_Instance()->DeleteID(OBJID::EXTRA_BOMB);
	CGameMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
	CSoundMgr::Get_Instance()->StopAll();

}
