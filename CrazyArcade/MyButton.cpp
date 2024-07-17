#include "stdafx.h"
#include "MyButton.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"


CMyButton::CMyButton()
	:m_pFrameKey(L"")
	, m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 218.f;
	m_tInfo.fCY = 47.f;
}

int CMyButton::Update()
{
	return 0;
}

void CMyButton::LateUpdate()
{
	CObj::UpdateRect();

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->KeyUP(VK_LBUTTON))
		{
			if (!lstrcmp(m_pFrameKey, L"Start1")) 
			{
				//CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE);
				CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE2);
				//CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE3);
				//CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_STAGE);
			}
			else if (!lstrcmp(m_pFrameKey, L"Edit1"))
			 	CSceneMgr::Get_Instance()->SceneChange(SceneID::SCENE_EDIT);
			else if (!lstrcmp(m_pFrameKey, L"Button_Left_1")) 
			{
				CTileMgr::Get_Instance()->Set_TileOption(-1);
				// 타일 번호 감소
			}
			else if (!lstrcmp(m_pFrameKey, L"Button_Right_1")) 
			{
				// 타일 번호 증가
				CTileMgr::Get_Instance()->Set_TileOption(+1);
			}
			else
				DestroyWindow(g_hWnd);

			return;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = nullptr;

	if (m_iDrawID == 0) {
		if (!lstrcmp(m_pFrameKey, L"Start1"))
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Start1");
		else if (!lstrcmp(m_pFrameKey, L"Edit1"))
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Edit1");
		else if (!lstrcmp(m_pFrameKey, L"Button_Left_1")) {
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Button_Left_1");
		}
		else if (!lstrcmp(m_pFrameKey, L"Button_Right_1")) {
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Button_Right_1");
		}
	}
	else if (m_iDrawID == 1)
	{
		if (!lstrcmp(m_pFrameKey, L"Start1"))
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Start2");
		else if (!lstrcmp(m_pFrameKey, L"Edit1"))
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Edit2");
		else if (!lstrcmp(m_pFrameKey, L"Button_Left_1")) 
		{
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Button_Left_2");
		}
		else if (!lstrcmp(m_pFrameKey, L"Button_Right_1")) 
		{
			hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Button_Right_2");
		}

	}

	GdiTransparentBlt(hDC, m_tRect.left, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY, hMemDC, m_tInfo.fCX*0, 0, m_tInfo.fCX, m_tInfo.fCY, RGB(255, 255, 255));
}

void CMyButton::Release()
{
}

void CMyButton::Set_Button_Size(float _fCX, float _fCY)
{
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
}
