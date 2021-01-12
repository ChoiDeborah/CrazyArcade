#include "stdafx.h"
#include "Obj.h"
#include "GameMgr.h"

CObj::CObj() 
	:m_bIsDead(false)
	, m_fAngle(0.f)
	, m_bIsInit(false)
	, m_eGroupID(GroupID::GAMEOBJECT)
	, m_bFlat(false)
	, m_eOBJID(OBJID::END)
	, m_bTop(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tIndex, sizeof(INDEX));
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (int(m_tInfo.fCY) >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (int(m_tInfo.fCY) >> 1));
}

void CObj::UpdateIndex()
{
	// 인덱스 업데이트 하기
	m_tIndex = CGameMgr::Get_Instance()->Get_Index_From_Position(m_tInfo.fX, m_tInfo.fY);
}

void CObj::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed <GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

void CObj::Set_Rect_X(float _offset)
{
	m_tRect.left += _offset;
	m_tRect.right += _offset;
}

void CObj::Set_Rect_Y(float _offset)
{
	m_tRect.bottom += _offset;
	m_tRect.top += _offset;
}

Point CObj::Get_Position()
{
	return Point(m_tInfo.fX, m_tInfo.fY);
}
