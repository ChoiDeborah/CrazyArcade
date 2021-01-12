#include "stdafx.h"
#include "Bomb.h"
#include "BitmapMgr.h"
#include "GameMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Item.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ExtraBomb.h"
#include "SoundMgr.h"


CBomb::CBomb()
	: m_dwDestroyTime(0)
	, m_pFrameKey(L"")
	, m_bIsBoom(false)
	, m_eNextState(IDLE)
	, m_eCurState(IDLE)
	, m_iLength(1)
	, m_bBoomRender(false)
	, m_eDir(DIRECTION::DIR_END)
{

}




CBomb::~CBomb()
{
}

void CBomb::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = pos.x;
	m_tInfo.fY = pos.y;

	m_iWidth = 44.f;
	m_iHeight = 41.f;

	m_fSpeed = 10.f;
		// Center
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Bomb1.bmp", L"Bomb1");
	// Flow
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Center.bmp", L"Flow_Center");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Down.bmp", L"Flow_Down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Left.bmp", L"Flow_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Right.bmp", L"Flow_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Up.bmp", L"Flow_Up");
	//Edge
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Edge_Down.bmp", L"Flow_Edge_Down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Edge_Left.bmp", L"Flow_Edge_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Edge_Right.bmp", L"Flow_Edge_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Flow_Edge_Up.bmp", L"Flow_Edge_Up");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Idle/Bomb_Idle_0.bmp", L"Bomb_Idle_0");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Idle/Bomb_Idle_1.bmp", L"Bomb_Idle_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Bomb/Idle/Bomb_Idle_2.bmp", L"Bomb_Idle_2");

	// 길이에 따라서 출력
	m_pFrameKey = L"Bomb_Idle_0";
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_dwBoomTime = GetTickCount();
	bArrDir[DIRECTION::DIR_END] = { 0 };
	CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex)->m_bMonsterPass = false;
}

int CBomb::Update()
{
	if (m_eCurState == CBomb::DESTROY || m_bIsDead)
		return OBJ_DEAD;

	//UpdateIndex();
	//if (m_tIndex.x < 0 || m_tIndex.y < 0)
	//	return OBJ_DEAD;
	//if (m_tIndex.x >= TILEX || m_tIndex.y >= TILEY)
	//	return OBJ_DEAD;
	//
	/*CTile* pTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex);*/
	//if (pTile->Get_Option() == 1) 
	//	Set_State_Boom();

	CObj::UpdateIndex();
	UpdateState();

	FrameMove();
	SceneChange();
	return OBJ_NOEVENT;
}

void CBomb::LateUpdate()
{
	{
		if (m_eCurState == IDLE) {
			switch (m_eDir)
			{
			case DIRECTION::LEFT:
				if (m_tInfo.fX > 40.f) 
				{
					m_tInfo.fX -= m_fSpeed;
				}
				break;
			case DIRECTION::RIGHT:
				if(m_tInfo.fX < 600.f) 
					m_tInfo.fX += m_fSpeed;
				break;
			case DIRECTION::UP:
				if (m_tInfo.fY > 60.f)
					m_tInfo.fY -= m_fSpeed;
				break;
			case DIRECTION::DOWN:
				if(m_tInfo.fY < 450.f)
					m_tInfo.fY += m_fSpeed;
				break;

			default:
				break;
			}
		}
		if (m_dwBoomTime + 2000 < GetTickCount())
		{
			m_eNextState = BOOM;
		}
		if (!m_bIsBoom && m_eCurState == BOOM)
		{
			m_bIsBoom = true;
			m_dwDestroyTime = GetTickCount();
		}


		//if (!m_bIsBoom  && CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex)->m_bIsBoom)
		//{
		//	m_bIsBoom = true;
		//	m_eNextState = BOOM;
		//	m_dwDestroyTime = GetTickCount();
		//}
		CTile* pTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex);

		if (pTile)
		{
			if (!m_bIsBoom  && pTile->m_bIsBoom)
			{
				m_bIsBoom = true;
				m_eNextState = BOOM;
				m_dwDestroyTime = GetTickCount();
			}
		}
		if (m_bIsBoom &&m_dwDestroyTime + 300 < GetTickCount())
		{
			m_eNextState = DESTROY;
			// 사라 질 때 거짓으로 바꿔준다 
			Set_Bomb_State(false, false);
		}
	}
}
void CBomb::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	switch (m_eCurState)
	{
	case CBomb::IDLE:
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 14.f, m_tRect.top - 11.f, //출력될 위치의 xy 좌표 
			m_iWidth, m_iHeight, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			0, // 시작 위치 
			m_iWidth, m_iHeight,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
		break;
	case CBomb::BOOM:
		Render_Boom(hDC);
		break;
	case CBomb::DESTROY:
		break;
	case CBomb::STATE_END:
		break;
	default:
		break;
	}

	if (CGameMgr::Get_Instance()->m_bCollision)
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


}


void CBomb::Render_Boom(HDC _hDC)
{
	// 물줄기 길이 만큼 사방향으로 BOOM
	// 중앙 
	//Boom(_hDC, INDEX(m_tIndex.x, m_tIndex.y));
	CTile* pTile = CTileMgr::Get_Instance()->Get_Tile_Info(m_tIndex);
	if (pTile)
	{
		pTile ->m_bMonsterPass = true;
	}
	CObj* pObj = CAbstractFactory<CExtraBomb>::Create(m_tIndex.x, m_tIndex.y);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	// 터지고 있는 상황 업데이트
	CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x, m_tIndex.y), false, true);
	// 사방향
	// 왼쪽
	for (int i = 1; i <= m_iLength; ++i)
	{
		// Edge일 때
		if (i == m_iLength)
		{
			Create_ExtraBoom(INDEX(m_tIndex.x - i, m_tIndex.y), BOMBTYPE::EDGE_LEFT, bArrDir[DIRECTION::LEFT]);
			Create_ExtraBoom(INDEX(m_tIndex.x + i, m_tIndex.y), BOMBTYPE::EDGE_RIGHT, bArrDir[DIRECTION::RIGHT]);
			Create_ExtraBoom(INDEX(m_tIndex.x, m_tIndex.y - i), BOMBTYPE::EDGE_UP, bArrDir[DIRECTION::UP]);
			Create_ExtraBoom(INDEX(m_tIndex.x, m_tIndex.y + i), BOMBTYPE::EDGE_DOWN, bArrDir[DIRECTION::DOWN]);
		}
		else
		{
			Create_ExtraBoom(INDEX(m_tIndex.x - i, m_tIndex.y), BOMBTYPE::LEFT, bArrDir[DIRECTION::LEFT]);
			Create_ExtraBoom(INDEX(m_tIndex.x + i, m_tIndex.y), BOMBTYPE::RIGHT, bArrDir[DIRECTION::RIGHT]);
			Create_ExtraBoom(INDEX(m_tIndex.x, m_tIndex.y - i), BOMBTYPE::UP, bArrDir[DIRECTION::UP]);
			Create_ExtraBoom(INDEX(m_tIndex.x, m_tIndex.y + i), BOMBTYPE::DOWN, bArrDir[DIRECTION::DOWN]);
		}
	}
}

bool CBomb::Dir_Tile_Check(INDEX _index, bool& _bDir)
{
	CTile* pTile = CTileMgr::Get_Instance()->Get_Tile_Info(_index);
	if (pTile && !_bDir)
	{
		// 지나갈 수 있으면
		if (pTile->Get_IsPass())
		{
			CGameMgr::Get_Instance()->Set_MapInfo(_index, false, true);
			return true;
		}
		// 부서지면
		else if (pTile->Get_IsBroken())
		{
			pTile->Set_Option(0);
			pTile->Create_Item();
			_bDir = true;
		}
		else
			_bDir = true;
	}

	return false;
}

void CBomb::Create_ExtraBoom(INDEX _index, BOMBTYPE::TYPE _eType, bool &bDir)
{
	if (0 > _index.x || TILEX - 1 < _index.x)
		return;
	if (0 > _index.y || TILEY - 1 < _index.y)
		return;

	if (Dir_Tile_Check(_index, bDir))
	{
		CObj* pObj = CAbstractFactory<CExtraBomb>::Create(_index.x, _index.y);
		dynamic_cast<CExtraBomb*>(pObj)->Set_Type(_eType);
		CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	}
}

bool CBomb::Check_Distance(CObj * pPlayer)
{
	float fDistance = 0.f;

	Point posPlayer = pPlayer->Get_Position();


	fDistance = sqrtf((posPlayer.x - m_tInfo.fX) * (posPlayer.x - m_tInfo.fX)
		+ (posPlayer.y - m_tInfo.fY)*(posPlayer.y - m_tInfo.fY));

	if (fDistance >= 10.f)
		true;

	return false;
}

void CBomb::Set_State_Boom()
{
	if (!m_bIsBoom) {
		m_bIsBoom = true;
		m_eNextState = BOOM;
		m_dwDestroyTime = GetTickCount();
	}
}

//void CBomb::Set_State_Boom()
//{
//	if (!m_bIsBoom && m_Cur)
//	{
//		m_eNextState = BOOM;
//		m_dwDestroyTime = GetTickCount();
//	}
//}


void CBomb::Boom(HDC _hDC, INDEX index)
{
	if (0 > index.x || TILEX - 1 < index.x)
		return;
	if (0 > index.y || TILEY - 1 < index.y)
		return;

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	POINT BombPos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(index);
	// 포지션 받아서
	RECT RectBomb = CGameMgr::Get_Instance()->Get_Rect_From_Position(BombPos, 40.f, 40.f);

	GdiTransparentBlt(_hDC, // 실제 복사받을 DC
		RectBomb.left, RectBomb.top, //출력될 위치의 xy 좌표 
		40, 40, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		56 * m_tFrame.iFrameStart,
		70 * m_tFrame.iFrameScene, // 시작 위치 
		40, 40,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);
}

void CBomb::UpdateState()
{
	MAPINFO * pMapInfo = CGameMgr::Get_Instance()->Get_MapInfo(m_tIndex);
	if (pMapInfo != nullptr)
	{
		if (pMapInfo->bIsBoom == true && m_eCurState == IDLE)
			m_eNextState = BOOM;
	}
}



void CBomb::Set_Bomb_State(bool _bIsExist, bool _bIsBoom)
{
	CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x, m_tIndex.y), _bIsExist, _bIsBoom);

	// 사방향

	for (int i = 0; i <= m_iLength; ++i)
	{
		CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x - i, m_tIndex.y), _bIsExist, _bIsBoom);
		CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x + i, m_tIndex.y), _bIsExist, _bIsBoom);
		CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x, m_tIndex.y + i), _bIsExist, _bIsBoom);
		CGameMgr::Get_Instance()->Set_MapInfo(INDEX(m_tIndex.x, m_tIndex.y - i), _bIsExist, _bIsBoom);
	}
}


void CBomb::Release()
{

}

void CBomb::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CBomb::IDLE:
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			break;
		case CBomb::STATE::BOOM:
			CSoundMgr::Get_Instance()->PlaySoundW(L"bomb2.wav", CSoundMgr::BOMB);
			m_pFrameKey = L"Bomb1";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 1;
			m_iWidth = 40.f;
			m_iHeight = 40.f;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CBomb::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		switch (m_eCurState)
		{
		case CBomb::IDLE:
			if (m_tFrame.iFrameStart == 0)
				m_pFrameKey = L"Bomb_Idle_0";
			if (m_tFrame.iFrameStart == 1)
				m_pFrameKey = L"Bomb_Idle_1";
			if (m_tFrame.iFrameStart == 2)
				m_pFrameKey = L"Bomb_Idle_2";
			break;
		case CBomb::STATE::BOOM:
			break;
		case CBomb::DESTROY:
			break;
		case CBomb::STATE_END:
			break;
		default:
			break;
		}

		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
}