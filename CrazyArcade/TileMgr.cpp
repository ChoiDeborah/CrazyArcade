#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "KeyMgr.h"
#include "BitmapMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "GameMgr.h"
#include "CollisionMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr()
	:m_iOption(0)
{
	ZeroMemory(&pt, sizeof(POINT));
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float x = 20.f + ( j * TILESIZEX) + (TILESIZEX * 0.5f);
			float y = 40.f + ( i * TILESIZEY) + (TILESIZEY * 0.5f);
			// option 0������ Ÿ�� ����.
			CObj* pObj = CAbstractFactory<CTile>::Create(x, y);
			m_vecTile.emplace_back(pObj);
			CObjMgr::Get_Instance()->AddObject(OBJID::TILE, pObj);
		}
	}
}

void CTileMgr::Update()
{
	// Ŀ�� ��ǥ �޾ƿ���
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// ���⼭ ���� �ε��� ���� ���� Ÿ�� �ɼ��̳� �Ӽ��� �ٲ� �ֱ�
	// Ű�Ŵ��� �ΰ��� ���� �־ �ȵǴ°� ������...
	// ���콺 ���ϸ� �ϴ°ɷ� ����.
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		// ���콺 �������� ��ǥ ���̸�	
		if (pt.x >= 20.f && pt.x <= 620.f && pt.y >= 40.f && pt.y <= 560.f)
		{
			CTileMgr::Get_Instance()->PickTile(pt, 0, m_iOption);
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		Save_Tile();
	}
}

void CTileMgr::LateUpdate()
{
	// ���⼭ ������ �����Ϳ��� ����
	//CCollisionMgr::CollisionRectEx_Tile(m_vecTile);

}

void CTileMgr::Render(HDC hDC)
{

	Show_Tile(hDC);
	Show_Mouse_Positon(hDC);

	// Ÿ�� �׸���
	for (auto& pTile : m_vecTile)
	{
		pTile->Render(hDC);
	}

}

void CTileMgr::Release()
{
	for (auto& pTile : m_vecTile)
	{
		if (pTile)
		{
			delete pTile;
			pTile = nullptr;
		}
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::Show_Tile(HDC hDC)
{
	switch (m_iOption)
	{
	case 1:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 40.f;
		m_pFrameKey = L"Camp_Tile_1";
		break;
	case 2:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 49.f;
		m_pFrameKey = L"Camp_Tile_2";
		break;
	case 3:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 49.f;
		m_pFrameKey = L"Camp_Tile_3";
		break;
	case 4:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 58.f;
		m_pFrameKey = L"Camp_Tile_4";
		break;
	case 5:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 49.f;
		m_pFrameKey = L"Camp_Tile_5";
		break;
	case 6:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 49.f;
		m_pFrameKey = L"Camp_Tile_6";
		break;
	case 7:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 49.f;
		m_pFrameKey = L"Camp_Tile_7";
		break;
	case 8:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 58.f;
		m_pFrameKey = L"Camp_Tile_8";
		break;
	case 9:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 46.f;
		m_pFrameKey = L"Camp_Tile_9";
		break;
	case 10:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 46.f;
		m_pFrameKey = L"Camp_Tile_10";
		break;
	case 11:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 59.f;
		m_pFrameKey = L"Camp_Tile_11";
		break;
	case 12:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 59.f;
		m_pFrameKey = L"Camp_Tile_12";
		break;
	case 13:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 59.f;
		m_pFrameKey = L"Camp_Tile_13";
		break;
	case 14:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 59.f;
		m_pFrameKey = L"Camp_Tile_14";
		break;
	case 15:
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 44.f;
		m_pFrameKey = L"Camp_Tile_15";
		break;
	default:
		break;

	}
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // ���� ������� DC
		700.f, 130.f, //��µ� ��ġ�� xy ��ǥ 
		m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
		hMemDC,
		0, 0,
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(255, 255, 255)
	);
	//BitBlt(hDC, 700.f, 130.f, TILESIZEX, TILESIZEY, hMemDC, m_iDrawID * TILESIZEX, 0, SRCCOPY);
}

void CTileMgr::Show_Mouse_Positon(HDC hDC) const
{
	/*TCHAR buff[1024] = L"";
	swprintf_s(buff, L" Mouse Pos X :%d Pos Y %d", pt.x, pt.y);
	TextOut(hDC, 600, 10, buff, lstrlen(buff));*/
}

void CTileMgr::PickTile(const POINT & pt, const int iDrawID, const int iOption)
{
	INDEX Index = CGameMgr::Get_Instance()->Get_Index_From_Position(pt);

	int iIndex = Index.x + (Index.y * TILEX);
	//cout << "x : " << Index.x << " , y : " << Index.y << "Index : " << iIndex << endl;
	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/BackUp.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	//assert(!(INVALID_HANDLE_VALUE == hFile));

	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"dd", L"Ÿ�� ���̺� ����!", MB_OK);
}

void CTileMgr::Load_Tile(TCHAR* pFilePath )
{
	
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	//assert(!(INVALID_HANDLE_VALUE == hFile));

	INFO tInfo = {};
	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	while (true)
	{

		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
		m_vecTile.emplace_back(pTile);
		CObjMgr::Get_Instance()->AddObject(OBJID::TILE, pTile);

	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"dd", L"Ÿ�� Load ����!", MB_OK);
}

CTile * CTileMgr::Get_Tile_Info(INDEX _index)
{
	int iIndex = _index.x + (_index.y * TILEX);
	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return nullptr;

	return dynamic_cast<CTile*>(m_vecTile[iIndex]);
}
