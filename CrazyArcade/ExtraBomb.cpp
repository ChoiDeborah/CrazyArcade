#include "stdafx.h"
#include "ExtraBomb.h"
#include "GameMgr.h"
#include "BitmapMgr.h"


CExtraBomb::CExtraBomb():
	m_pFrameKey(L""), 
	m_eDir(DIRECTION::DIR_END),
	m_eType(BOMBTYPE::FLOW_END),
	m_bBossBomb(false)
{

}


CExtraBomb::~CExtraBomb()
{

}

void CExtraBomb::Initialize()
{
	//m_tInfo.fCX = 20.f;
	//m_tInfo.fCY = 20.f;
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = pos.x;
	m_tInfo.fY = pos.y;
	m_dwDestroyTime = GetTickCount();

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Center.bmp", L"Flow_Center");


	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
}

int CExtraBomb::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (!m_bBossBomb) {
		if (m_dwDestroyTime + 200 < GetTickCount())
			m_bIsDead = true;
	}
	else
	{
		if (m_dwDestroyTime + 600 < GetTickCount())
			m_bIsDead = true;
	}
	CObj::FrameMove();


	return OBJ_NOEVENT;
}

void CExtraBomb::LateUpdate()
{
}

void CExtraBomb::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	
	if (m_bBossBomb) {
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 10.f, m_tRect.top - 10.f, //출력될 위치의 xy 좌표 
			40, 40, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			56 * m_tFrame.iFrameStart,
			0, // 시작 위치 
			40, 40,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}

	else
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
			40,40, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			56 * m_tFrame.iFrameStart,
			40, 40,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}


	if (CGameMgr::Get_Instance()->m_bCollision)
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CExtraBomb::Release()
{
}

void CExtraBomb::Set_Type(BOMBTYPE::TYPE eType)
{
	m_eType = eType; 

	switch (m_eType)
	{
	case BOMBTYPE::CENTER:
		m_pFrameKey = L"Flow_Center";

		m_tFrame.dwFrameSpeed = 500;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::RIGHT:
		m_pFrameKey = L"Flow_Right";
		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::LEFT:
		m_pFrameKey = L"Flow_Left";
		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::UP:
		m_pFrameKey = L"Flow_Up";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::DOWN:
		m_pFrameKey = L"Flow_Down";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::EDGE_RIGHT:
		m_pFrameKey = L"Flow_Edge_Right";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::EDGE_LEFT:
		m_pFrameKey = L"Flow_Edge_Left";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::EDGE_UP:
		m_pFrameKey = L"Flow_Edge_Up";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::EDGE_DOWN:
		m_pFrameKey = L"Flow_Edge_Down";

		m_tFrame.dwFrameSpeed = 50;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;
		m_tFrame.iFrameScene = 0;
		break;
	case BOMBTYPE::FLOW_END:
		break;
	default:
		break;
	}
}
