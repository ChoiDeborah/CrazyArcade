#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static int Get_ScrollX() { return m_iScrollX; }
	static void Set_ScrollX(int x) { m_iScrollX += x; }
private:
	static int m_iScrollX;
};

