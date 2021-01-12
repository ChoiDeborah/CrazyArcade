#include "stdafx.h"
#include "EditorLineMgr.h"
#include "EditorLine.h"
CEditorLineMgr* CEditorLineMgr::m_pInstance = nullptr;

CEditorLineMgr::CEditorLineMgr()
{
}


CEditorLineMgr::~CEditorLineMgr()
{
	Release();
}

void CEditorLineMgr::Initialize()
{
}

void CEditorLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(hDC);
}

void CEditorLineMgr::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	int iScrollX = CEditorScrollMgr::Get_ScrollX();
	pt.x -= iScrollX;

	if (CEditorKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		CEditorScrollMgr::Set_ScrollX(-5.f);
	if (CEditorKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		CEditorScrollMgr::Set_ScrollX(5.f);

	if (CEditorKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		LINEINFO tStartInfo =
		{
			LINEPOS(float(pt.x), float(pt.y)),
			LINEPOS(float(pt.x), float(pt.y))
		};
		m_listLine.emplace_back(new CEditorLine(tStartInfo));
	}
	if (CEditorKeyMgr::Get_Instance()->KeyUP(VK_LBUTTON))
	{
		m_listLine.back()->Set_LineInfo(LINEPOS(float(pt.x), float(pt.y)));
	}
	if (CEditorKeyMgr::Get_Instance()->KeyUP('S'))
		SaveData();
}

void CEditorLineMgr::Release()
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

void CEditorLineMgr::SaveData()
{
	HANDLE hFile = CreateFile(__T("../Data/Line.dat"),
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"세이브 파일", __T("세이브"), MB_OK);
	}
	DWORD dwByte = 0;
	for (auto& pLine : m_listLine)
	{
		WriteFile(hFile, &pLine->Get_LineInfo(), sizeof(LINEINFO), &dwByte, nullptr);

	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"세이브 성공!!", L"save", MB_OK);
}
