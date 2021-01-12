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
	HDC m_hMemDC; // 비트맵 이미지를 미리 그려넣을 메모리 DC

	HBITMAP m_hBitmap; // 비트맵 정보를 갖고 있을 GDI 오브젝트 
	HBITMAP m_hOldBitmap;
};

