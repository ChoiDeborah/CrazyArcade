#include "stdafx.h"
#include "Logo.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	this->Release();
}

void CLogo::Initialize()
{
 	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Logo.bmp", L"Logo");
	CSoundMgr::Get_Instance()->PlayBGM(L"Main.wav");
}

void CLogo::Update()
{
	// 추후 뭔가 키를 누르면 씬이 바뀌도록 만들것이다. 
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_MENU);
	}
}

void CLogo::LateUpdate()
{
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
 }

void CLogo::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
}
