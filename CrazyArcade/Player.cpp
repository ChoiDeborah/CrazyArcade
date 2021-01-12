#include "stdafx.h"
#include "Player.h"
#include "Bomb.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BitmapMgr.h"
#include "Bomb.h"
#include "KeyMgr.h"
#include "GameMgr.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	:m_pFrameKey(L"")
	, m_eNextState(DOWN)
	, m_eCurState(DOWN)
	, m_bIsBubble(false)
	, m_iLengthOfBomb(1)
	, m_iNumOfBomb(1)
	, m_bNeedle(false)
	, m_bKick(false)
	, m_pTargetTile(nullptr)
	, m_Developter(false)
	, m_bIsDrop(false)
{

}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 25.f;
	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = pos.x;
	m_tInfo.fY = pos.y;
	m_fSpeed = 3.f;
	m_fAngle = 45.f;

	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_idle.bmp", L"Player_Idle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_down2.bmp", L"Player_Down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_up.bmp", L"Player_Up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_right.bmp", L"Player_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_left.bmp", L"Player_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_bubble.bmp", L"bazzi_bubble");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_dead.bmp", L"bazzi_dead");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Player/bazzi_undead.bmp", L"bazzi_undead");

	m_eCurState = IDLE;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = 0;
	m_dwBubbleTime = GetTickCount();
}

int CPlayer::Update()
{
	if (m_bIsDead && !m_Developter)
	{
		m_bIsDead = false;
		m_eNextState = DEAD;
		CGameMgr::Get_Instance()->m_bGameLose = true;
	}
	SceneChange();

	if(m_eCurState != CPlayer::UNDEAD 
		&& m_eCurState != CPlayer::DEAD)
		KeyCheck();
	CObj::UpdateIndex();

	
	FrameMove();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	MAPINFO* pMapInfo = CGameMgr::Get_Instance()->Get_MapInfo(m_tIndex);

	if (m_bNeedle &&CKeyMgr::Get_Instance()->KeyUP(VK_CONTROL))
	{
		Use_Niddle();
	}
	if (CKeyMgr::Get_Instance()->KeyUP('I'))
	{
		//m_eNextState = CPlayer::IDLE;
		Use_Niddle();
	}

	if (CKeyMgr::Get_Instance()->KeyUP('D'))
	{
		m_Developter = true;
	}

	if (pMapInfo) 
	{
		if (pMapInfo->bIsBoom) {
			if(m_eCurState != CPlayer::DEAD)
			
				m_eNextState = BUBBLE;
		}
	}

	if (m_bIsBubble && m_dwBubbleTime + 2000 < GetTickCount()) 
	{
	
		m_bIsBubble = false;
		m_eNextState = DEAD;
	}

	if (m_eCurState == CPlayer::UNDEAD && m_dwNiddleTime + 300 < GetTickCount())
	{
		m_eNextState = IDLE;
	}
}

void CPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	
	TCHAR buff[1024] = L"";
	swprintf_s(buff, L" Player Pos X :%d Pos Y %d", m_tIndex.x, m_tIndex.y);
	TextOut(hDC, 600, 10, buff, lstrlen(buff));
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_eCurState == UP || m_eCurState == DOWN || m_eCurState == IDLE) 
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left-20.f, m_tRect.top-35.f, //출력될 위치의 xy 좌표 
			70.f, 70.f, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			70 * m_tFrame.iFrameScene,
			70 * m_tFrame.iFrameStart, // 시작 위치 
			70,70,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
	}
	else if (m_eCurState == RIGHT || m_eCurState == LEFT || m_eCurState == BUBBLE || m_eCurState == DEAD || m_eCurState == UNDEAD)
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 20.0f, m_tRect.top - 35.f, //출력될 위치의 xy 좌표 
			70.f, 70.f, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			70* m_tFrame.iFrameStart,
			70 * m_tFrame.iFrameScene, // 시작 위치 
			70, 70,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
	}

	if (m_bNeedle)
	{
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Item (3)");

		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			680.f, 490.f, //출력될 위치의 xy 좌표 
			38.f, 38.f, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0, 0,
			38.f, 38.f,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
	if (CGameMgr::Get_Instance()->m_bCollision) 
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CPlayer::Release()
{
}

void CPlayer::KeyCheck()
{
	
	if (m_eCurState == BUBBLE)
		m_fSpeed = 0.3f;
	else m_fSpeed = 3.0f;

	if (GetAsyncKeyState(VK_UP))
	{

		if (m_tInfo.fY > OFFSET_Y) 
		{
			m_tInfo.fY -= m_fSpeed;
		}
		if (m_eCurState != BUBBLE)
		{
			m_pFrameKey = L"Player_Up";
			m_eNextState = UP;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		
		if (m_tRect.bottom < 560.f)
			m_tInfo.fY += m_fSpeed;
		if (m_eCurState != BUBBLE)
		{
			m_pFrameKey = L"Player_Down";
			m_eNextState = DOWN;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_tRect.left > OFFSET_X)
			m_tInfo.fX -= m_fSpeed;
		if (m_eCurState != BUBBLE)
		{
			m_pFrameKey = L"Player_Left";
			m_eNextState = LEFT;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_tRect.right < 620.f)
			m_tInfo.fX += m_fSpeed;
		if (m_eCurState != BUBBLE)
		{
			m_pFrameKey = L"Player_Right";
			m_eNextState = RIGHT;
		}
	}
	else {
		if (m_eCurState != CPlayer::BUBBLE && m_eNextState!= CPlayer::BUBBLE&&
			m_eCurState != CPlayer::DEAD && 
			m_eCurState != CPlayer::UNDEAD)
		{
			if (m_eCurState != BUBBLE) {
				m_eNextState = IDLE;
				m_pFrameKey = L"Player_Idle";
			}
		}
		
	}

	if (m_bIsDrop &&m_dwBubbleTime + 100 < GetTickCount())
	{
		m_bIsDrop = false;
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		//MAPINFO* pMapInfo = CGameMgr::Get_Instance()->Get_MapInfo(m_tIndex);
		//if (nullptr != pMapInfo) 
		//{!pMapInfo->bIsExist
		if (!m_bIsDrop &&m_eCurState != CPlayer::DEAD && m_eCurState != CPlayer::BUBBLE)
		{
			if (m_iLengthOfBomb >= CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOMB).size())
			{
				m_bIsDrop = true;
				m_dwCreateBoomTime = GetTickCount();
				CSoundMgr::Get_Instance()->PlaySoundW(L"bomb1.wav", CSoundMgr::PLAYER);
				// 맵 정보에 플레이어 인덱스로 존재하고 터지지 않는다.
				CGameMgr::Get_Instance()->Set_MapInfo(m_tIndex, true, false);
				// 캐릭터 위치 기준 가장 가까운 타일 위치 반환
				POINT BombPos = CGameMgr::Get_Instance()->Get_Tile_Positon_From_Position(m_tInfo.fX, m_tInfo.fY);
				CObj* pBomb = CAbstractFactory<CBomb>::Create(m_tIndex.x, m_tIndex.y);
				dynamic_cast<CBomb*>(pBomb)->Set_Length(m_iLengthOfBomb);
				CObjMgr::Get_Instance()->AddObject(OBJID::BOMB, pBomb);
			}

		}//}
	}
}

void CPlayer::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CPlayer::IDLE:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::DOWN:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::UP:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::LEFT:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::RIGHT:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::BUBBLE:
			CSoundMgr::Get_Instance()->PlaySoundW(L"bomb3.wav", CSoundMgr::PLAYER);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"bazzi_bubble";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_dwBubbleTime = GetTickCount();
			m_bIsBubble = true;
			break;
		case CPlayer::DEAD:
			CSoundMgr::Get_Instance()->PlaySoundW(L"dead.wav", CSoundMgr::PLAYER);
			m_tFrame.dwFrameSpeed = 100;
			m_pFrameKey = L"bazzi_dead";
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::UNDEAD:
			CSoundMgr::Get_Instance()->PlaySoundW(L"niddle.wav", CSoundMgr::PLAYER);
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"bazzi_undead";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}


void CPlayer::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed <GetTickCount())
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			++m_tFrame.iFrameStart;	
			break;
		case CPlayer::DOWN:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::RIGHT:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::LEFT:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::UP:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::BUBBLE:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::DEAD:
			++m_tFrame.iFrameStart;
			break;
		case CPlayer::UNDEAD:
			++m_tFrame.iFrameStart;
			break;
		default:
			break;
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		// 끝 스프라이트 유지 
		if(m_eCurState == BUBBLE || m_eCurState == DEAD)
			m_tFrame.iFrameStart = 3;
		else if (m_eCurState == UNDEAD)
			m_tFrame.iFrameStart = 2;
		else
			m_tFrame.iFrameStart = 0;
		

	}
}

void CPlayer::Take_Item(int _iItemType)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"item.wav", CSoundMgr::PLAYER);
	switch (_iItemType)
	{
	case 0:
		break;
	case 1:
		++m_iNumOfBomb;
		break;
	case 2:
		++m_iLengthOfBomb;
		break;
	case 3:
		m_fSpeed += 0.5f;
		break;
	case 4:
		m_bNeedle = true;
		break;
	case 5:
		m_bKick = true;
		break;
	default:
		break;
	}
}

void CPlayer::Use_Niddle()
{
	m_bNeedle = false;
	m_bIsBubble = false;
	m_eNextState = UNDEAD;
	m_dwNiddleTime = GetTickCount();
}

void CPlayer::Set_State_Bubble()
{
	if (m_eCurState != CPlayer::DEAD)
		m_eNextState = BUBBLE;

}

CTile * CPlayer::Get_Pushing_Tile()
{

	if (nullptr == m_pTargetTile)
		return nullptr;
	else
		return m_pTargetTile;

}

