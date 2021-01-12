#include "stdafx.h"
#include "MyMenu.h"
#include "BitmapMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "SoundMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Lobby.wav");

	// 마우스 추가
	CObjMgr::Get_Instance()->AddObject(OBJID::MOUSE, CAbstractFactory<CMouse>::Create());

	// 메뉴창 바탕화면 추가
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Menu_1.bmp", L"Menu");

	// 버튼 추가
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Start_1.bmp", L"Start1");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Editor_1.bmp", L"Edit1");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Start_2.bmp", L"Start2");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Editor_2.bmp", L"Edit2");

	CObj* pObj = CAbstractFactory<CMyButton>::Create(400.f, 231.5f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Start1");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	//dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Exit");
	//CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 278.5f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Edit1");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);

}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CObjMgr::Get_Instance()->DeleteID(OBJID::MENUBUTTON);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MOUSE);
}
