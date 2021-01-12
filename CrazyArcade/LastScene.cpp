#include "stdafx.h"
#include "LastScene.h"
#include "BitmapMgr.h"

CLastScene::CLastScene()
{
}


CLastScene::~CLastScene()
{
	Release();
}

void CLastScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/End.bmp", L"End");


}

void CLastScene::Update()
{
}

void CLastScene::LateUpdate()
{
}

void CLastScene::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"End");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CLastScene::Release()
{
}
