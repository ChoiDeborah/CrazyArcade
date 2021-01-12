#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	LoadData();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(hDC);
}

void CLineMgr::Release()
{
	for (auto& pLine : m_listLine)
	{
		if (pLine)
		{
			delete pLine;
			pLine = nullptr;
		}
	}
	m_listLine.clear();
}

bool CLineMgr::LineCollision(float fInX, float * pOutY)
{
	if (m_listLine.empty())
		return false;

	CLine* pTarget = nullptr;
	for (auto& pLine : m_listLine)
	{
		if (fInX >= pLine->Get_LineInfo().tLeftPoint.fx &&
			fInX <= pLine->Get_LineInfo().tRightPoint.fx)
		{
			pTarget = pLine;
		}
	}
	if (nullptr == pTarget)
		return false;

	// Outy = ((y2 - y1) / (x2 - x1)) * (InX - x1) + y1;

	float x1 = pTarget->Get_LineInfo().tLeftPoint.fx;
	float x2 = pTarget->Get_LineInfo().tRightPoint.fx;
	float y1 = pTarget->Get_LineInfo().tLeftPoint.fy;
	float y2 = pTarget->Get_LineInfo().tRightPoint.fy;

	*pOutY = ((y2 - y1) / (x2 - x1)) * (fInX - x1) + y1;
	return true;
}

void CLineMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hWnd, L"���� ���� ����", L"���� ���� ����", MB_OK);
		return;
	}
	LINEINFO tInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}
		m_listLine.emplace_back(new CLine(tInfo));
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"���� �б� ����", L"���� �б� ����", MB_OK);
}
