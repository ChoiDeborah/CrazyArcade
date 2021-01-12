#include "stdafx.h"
#include "Scene.h"
#include "BitmapMgr.h"

CScene::CScene()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/BackGround.bmp", L"Background");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Stage_1.bmp", L"Stage_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/GameStart.bmp", L"GameStart");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/GameOver.bmp", L"GameOver");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Clear.bmp", L"Clear");

}


CScene::~CScene()
{
}
