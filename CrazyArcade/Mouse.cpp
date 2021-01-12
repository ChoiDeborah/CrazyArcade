#include "stdafx.h"
#include "Mouse.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"

CMouse::CMouse()
{
	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 42.f;

	m_eGroupID = GroupID::UI;
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Mouse_1.bmp", L"Mouse_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Mouse_2.bmp", L"Mouse_2");

	m_tInfo = { 0.f, 0.f, 20.f, 20.f };
	ShowCursor(FALSE);

}

int CMouse::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = float(pt.x);
	m_tInfo.fY = float(pt.y);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON)) 
	{
		m_bIsPressed = true;
		m_pFrameKey = L"Mouse_2";
	}
	else
	{
		m_bIsPressed = false;
		m_pFrameKey = L"Mouse_1";
	}
	return 0;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left, m_tRect.top,
		m_tInfo.fCX*2, m_tInfo.fCY*2,
		hMemDC,
		0, 0,
		m_tInfo.fCX*2, m_tInfo.fCY*2,
		RGB(255, 255, 255));
}

void CMouse::Release()
{
}
