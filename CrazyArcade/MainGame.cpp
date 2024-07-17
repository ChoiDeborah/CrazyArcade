#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Mouse.h"
#include "ObjMgr.h"

#include "CollisionMgr.h"
#include "BitmapMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "GameMgr.h"
#include "SoundMgr.h"


CMainGame::CMainGame()
	:m_FPS(L"")
	, m_iFPS(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand((unsigned)time(NULL));
	m_dwTime = GetTickCount();
	m_hDC = GetDC(g_hWnd);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Menu_1.bmp", L"Back");
	//CSoundMgr::Get_Instance();
	//// 작업할 도화지. 
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/BackGround.bmp", L"BackBuffer");
	CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_LOGO);
}

void CMainGame::Update()
{
	CObjMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
}

void CMainGame::Render()
{
	HDC hBackBufferDC = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBackDC = CBitmapMgr::Get_Instance()->FindImage(L"Back");

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	
 	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	// 여기에서 씬매니저 -> 씬 -> ObjMgr를 돌리면 각 객체가 다 돌아가겠네 

	CSceneMgr::Get_Instance()->Render(hBackBufferDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	 
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CBitmapMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CGameMgr::Destroy_Instance();
	// CObjMgr 메모리 릭 생기므로 마지막에 지워준다.
	CObjMgr::Destory_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
}