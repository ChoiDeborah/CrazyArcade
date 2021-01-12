#include "stdafx.h"
#include "BitmapMgr.h"
#include "MyBitmap.h"

CBitmapMgr* CBitmapMgr::m_pInstance = nullptr;


CBitmapMgr::CBitmapMgr()
{
}


CBitmapMgr::~CBitmapMgr()
{
	Release();
}

HDC CBitmapMgr::FindImage(const TCHAR * pImgKey)
{
	auto& iter = find_if(m_mapImage.begin(), m_mapImage.end(), CMyStrCmp(pImgKey));
	if (m_mapImage.end() == iter)
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBitmapMgr::InsertBmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{

	auto& iter = m_mapImage.find(pImgKey);
	if (m_mapImage.end() == iter)
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->LoadBmp(pFilePath);
		m_mapImage.emplace(pImgKey, pBmp);
	}
}

void CBitmapMgr::Release()
{
	for (auto& rPair : m_mapImage)
	{
		if (rPair.second)
		{
			delete rPair.second;
			rPair.second = nullptr;
		}
	}
	m_mapImage.clear();
}
