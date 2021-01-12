#include "stdafx.h"
#include "EditorLine.h"


CEditorLine::CEditorLine()
{
}

CEditorLine::CEditorLine(LINEINFO & rLineInfo)
	:m_tInfo(rLineInfo)
{
}


CEditorLine::~CEditorLine()
{
}

void CEditorLine::Render(HDC hDC)
{
	int iScrollX = CEditorScrollMgr::Get_ScrollX();
	MoveToEx(hDC, static_cast<int>(m_tInfo.tLeftPoint.fx) + iScrollX, static_cast<int>(m_tInfo.tLeftPoint.fy), nullptr);
	LineTo(hDC, static_cast<int>(m_tInfo.tRightPoint.fx) + iScrollX, static_cast<int>(m_tInfo.tRightPoint.fy));
}