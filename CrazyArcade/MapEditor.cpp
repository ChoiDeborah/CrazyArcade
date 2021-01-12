#include "stdafx.h"
#include "MapEditor.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "Mouse.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMapEditor::CMapEditor()
{
	
}


CMapEditor::~CMapEditor()
{
	Release();
}


void CMapEditor::Initialize()
{
	CObjMgr::Get_Instance()->AddObject(OBJID::MOUSE, CAbstractFactory<CMouse>::Create());
	// 배경
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Editor_BackGround.bmp", L"EditorBackGround");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Stage_1.bmp", L"Stage_1");

	// 버튼 추가
	// 왼쪽 버튼
	// 누르기 전
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Left_1.bmp", L"Button_Left_1");
	// 누른 후
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Left_2.bmp", L"Button_Left_2");
	// 오른쪽 버튼
	// 누르기 전
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Right_1.bmp", L"Button_Right_1");
	//누른 후
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Button_Right_2.bmp", L"Button_Right_2");


	// 버튼 생성
	CObj* pObj = CAbstractFactory<CMyButton>::Create(657.f, 149.f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Button_Left_1");
	dynamic_cast<CMyButton*>(pObj)->Set_Button_Size(33.f, 33.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::EDITORBUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(781.f, 149.f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Button_Right_1");
	dynamic_cast<CMyButton*>(pObj)->Set_Button_Size(33.f, 33.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::EDITORBUTTON, pObj);

	CTileMgr::Get_Instance()->Initialize();
}

void CMapEditor::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyUP('B'))
	{
		CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_MENU);
	}
}

void CMapEditor::LateUpdate()
{
	CTileMgr::Get_Instance()->LateUpdate();
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMapEditor::Render(HDC hDC)
{
	// 마우스 커서 출력 
	// 배경 화면 출력
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"EditorBackGround");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Stage_1");
	BitBlt(hDC, OFFSET_X, OFFSET_Y, MAPSIZEX, MAPSIZEY, hMemDC, 0, 0, SRCCOPY);

	// 버튼 오브젝트 돌려
	Render_Line(hDC);

	// 밥먹고 라인그려라 
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	
}

void CMapEditor::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	// 버튼 삭제 해
	CObjMgr::Get_Instance()->DeleteID(OBJID::EDITORBUTTON);
	CObjMgr::Get_Instance()->DeleteID(OBJID::MOUSE);

}

void CMapEditor::Render_Line(HDC hDC)
{
	// 세로
	float x = OFFSET_X;
	float y = OFFSET_Y;

	for (int i = 0; i < TILEX; ++i) 
	{
		x = i * TILESIZEX + OFFSET_X;
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x, y + MAPSIZEY);
	}

	for (int i = 0; i < TILEY; ++i){
		x = OFFSET_X;
		y = i * TILESIZEY + OFFSET_Y;
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x + MAPSIZEX, y);
	}
}

