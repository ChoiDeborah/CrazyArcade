#include "stdafx.h"
#include "Editor.h"


CEditor::CEditor()
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize()
{
	m_hDC = GetDC(g_hWnd);
}

void CEditor::Update()
{
}

void CEditor::Render()
{
}

void CEditor::Release()
{
}
