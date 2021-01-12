#pragma once
class CMyBitmap;
class CBitmapMgr
{
private:
	CBitmapMgr();
	~CBitmapMgr();
public:
	static CBitmapMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBitmapMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	HDC FindImage(const TCHAR* pImgKey);
public:
	void InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void Release();
private:
	static CBitmapMgr* m_pInstance;
	map<const TCHAR*, CMyBitmap*> m_mapImage;
};