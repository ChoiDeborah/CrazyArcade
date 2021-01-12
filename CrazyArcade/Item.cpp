#include "stdafx.h"
#include "Item.h"
#include "BitmapMgr.h"
#include "GameMgr.h"

CItem::CItem():m_bExist(false), m_iTypeOfItem(0), m_pFrameKey(L"")
{
	m_tInfo.fCX = 38.0f;
	m_tInfo.fCY = 38.0f;

	m_bExist = rand() % 2;

	//if (m_bExist)
	//{
		m_iTypeOfItem = rand() % 4 + 1;
	/*}
	else m_iTypeOfItem = 0;*/
}


CItem::~CItem()
{
	

}

void CItem::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Item/Item (0).bmp", L"Item (0)");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Item/Item (1).bmp", L"Item (1)");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Item/Item (2).bmp", L"Item (2)");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Item/Item (3).bmp", L"Item (3)");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Item/Shoe.bmp", L"Shoe");

	switch (m_iTypeOfItem)
	{
	case 0:
		//m_pFrameKey = L"Item (0)";
		break;
	case 1:
 		m_pFrameKey = L"Item (0)";
		break;
	case 2:
		m_pFrameKey = L"Item (1)";
		break;
	case 3: 
		m_pFrameKey = L"Item (2)";
		break;
	case 4:
		m_pFrameKey = L"Item (3)";
		break;
	case 5:
		m_pFrameKey = L"Item (0)";
		break;
	default:
		break;
	}
}

int CItem::Update()
{
	if (m_bIsDead) 
		return OBJ_DEAD;
	

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
	

}

void CItem::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	POINT ItemPos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = ItemPos.x;
	m_tInfo.fY = ItemPos.y;
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		0,
		0, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);

	if (CGameMgr::Get_Instance()->m_bCollision)
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CItem::Release()
{
	
}

void CItem::Set_Index(INDEX _index)
{
	m_tIndex = _index;

	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(_index);

	m_tInfo.fX = pos.x;
	m_tInfo.fY = pos.y;
}

void CItem::Set_Type(int _iType)
{
	m_iTypeOfItem = _iType;
	switch (m_iTypeOfItem)
	{
	case 0:
		//m_pFrameKey = L"Item (0)";
		break;
	case 1:
		m_pFrameKey = L"Item (0)";
		break;
	case 2:
		m_pFrameKey = L"Item (1)";
		break;
	case 3:
		m_pFrameKey = L"Item (2)";
		break;
	case 4:
		m_pFrameKey = L"Item (3)";
		break;
	case 5:
		m_pFrameKey = L"Shoe";
	default:
		break;
	}
}
