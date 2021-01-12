#pragma once
class CEditorScrollMgr
{
public:
	CEditorScrollMgr();
	~CEditorScrollMgr();
public:
	static int Get_ScrollX() { return m_iScrollX; }
	static void Set_ScrollX(int x) { m_iScrollX += x; }
private:
	static int m_iScrollX;
};

