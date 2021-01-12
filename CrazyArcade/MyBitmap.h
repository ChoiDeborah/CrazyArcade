#pragma once
class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
public:
	HDC Get_MemDC() { return m_hMemDC; }
	void LoadBmp(const TCHAR* pPath);
	void Release();
private:
	HDC m_hMemDC; // ��Ʈ�� �̹����� �̸� �׷����� �޸� DC

	HBITMAP m_hBitmap; // ��Ʈ�� ������ ���� ���� GDI ������Ʈ 
	HBITMAP m_hOldBitmap;
};

