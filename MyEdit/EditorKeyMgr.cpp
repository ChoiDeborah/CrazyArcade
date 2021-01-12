#include "stdafx.h"
#include "EditorKeyMgr.h"


CEditorKeyMgr* CEditorKeyMgr::m_pInstance = nullptr;

CEditorKeyMgr::CEditorKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


CEditorKeyMgr::~CEditorKeyMgr()
{
}

bool CEditorKeyMgr::KeyPressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;

	return false;
}

bool CEditorKeyMgr::KeyDown(int iKey)
{
	if (!m_bKeyState[iKey] && (GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}
	return false;
}

bool CEditorKeyMgr::KeyUP(int iKey)
{
	if (m_bKeyState[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}
	return false;
}

void CEditorKeyMgr::KeyUpdate()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}
}