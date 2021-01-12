#pragma once
class CEditorLine
{
public:
	CEditorLine();
	CEditorLine(LINEINFO& rLineInfo);
	~CEditorLine();
public:
	void Set_LineInfo(LINEPOS& rRPoint) { m_tInfo.tRightPoint = rRPoint; }
public:
	LINEINFO& Get_LineInfo() { return m_tInfo; }
public:
	void Render(HDC hDC);

private:
	LINEINFO m_tInfo;
};