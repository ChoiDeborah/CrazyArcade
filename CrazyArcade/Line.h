#pragma once
class CLine
{
public:
	CLine();
	CLine(LINEINFO& rLineInfo);
	~CLine();
public:
	LINEINFO& Get_LineInfo() { return m_tInfo; }
public:
	void Render(HDC hDC);

private:
	LINEINFO m_tInfo;
};

