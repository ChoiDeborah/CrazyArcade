#include "stdafx.h"
#include "Monster.h"
#include "BitmapMgr.h"
#include "GameMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "SoundMgr.h"
CMonster::CMonster():
	m_eDir(DIRECTION::RIGHT), 
	m_bIsFinalHit(false),
	m_bStartCollision(true)
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 1.5f;
	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = (float)pos.x;
	m_tInfo.fY = (float)pos.y;
	m_fHeight = 84.f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon1_Front.bmp", L"Mon1_Front");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon1_back.bmp", L"Mon1_back");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon1_Left.bmp", L"Mon1_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon1_Right.bmp", L"Mon1_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon1_Dead.bmp", L"Mon1_Dead");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon2_Up.bmp", L"Mon2_Up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon2_Down.bmp", L"Mon2_Down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon2_Left.bmp", L"Mon2_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Mon2_Right.bmp", L"Mon2_Right");

	TargetPos = { m_tInfo.fX, m_tInfo.fY };
	m_dwCollisionDelayTime = GetTickCount();
}

int CMonster::Update()
{
	if (m_bIsDead)
	{
		return OBJ_DEAD;
 	}

 	if (!m_bStartCollision && m_dwCollisionDelayTime + 1000 < GetTickCount())
	{
 		m_bStartCollision = true;
	}

	if (m_bIsFinalHit && m_dwDeadTime + 300 < GetTickCount()) {
		m_bIsDead = true;
	}

	// 작아진 상태에서 일정 시간 이상되면 다시 커짐
	if (m_bSmaller && m_dwRefreshTime + 5000 < GetTickCount())
		m_bSmaller = false;

	SceneChange();
	if(m_eCurState != CMonster::DEAD)
		Check_Dir();
	CObj::FrameMove();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate()
{

}


void CMonster::Render(HDC hDC)
{
	CObj::UpdateRect();

	/*TCHAR buff[1024] = L"";
	swprintf_s(buff, L" Monster Pos X :%d Pos Y %d", m_tIndex.x, m_tIndex.y);
	TextOut(hDC, 20, 10, buff, lstrlen(buff));
*/

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (!m_bSmaller || m_eCurState == DEAD) {
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 15.0f, m_tRect.top - 50.f, //출력될 위치의 xy 좌표 
			64, 84, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			64 * m_tFrame.iFrameStart,
			0, // 시작 위치 
			64, 84,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
	}
	if (m_bSmaller)
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 12.0f, m_tRect.top - 25.f, //출력될 위치의 xy 좌표 
			61.f, 59.f, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			61.f * m_tFrame.iFrameStart,
			0, // 시작 위치 
			61.f, 59.f,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
	}

	if (CGameMgr::Get_Instance()->m_bCollision)
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMonster::Release()
{
}

void CMonster::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CMonster::DOWN:
			m_pFrameKey = L"Mon1_Front";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::UP:
			m_pFrameKey = L"Mon1_back";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::LEFT:
			m_pFrameKey = L"Mon1_Left";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::RIGHT:
			m_pFrameKey = L"Mon1_Right";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::DOWN2:
			m_pFrameKey = L"Mon2_Down";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::UP2:
			m_pFrameKey = L"Mon2_Up";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::LEFT2:
			m_pFrameKey = L"Mon2_Left";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::RIGHT2:
			m_pFrameKey = L"Mon2_Right";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		// 한번 맞았을 때로 하자.
		case CMonster::BUBBLE:
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_pFrameKey = L"bazzi_bubble";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::DEAD:
			m_tFrame.dwFrameSpeed = 100;
			m_pFrameKey = L"Mon1_Dead";
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			break;
		case CMonster::UNDEAD:
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


void CMonster::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed <GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		if (m_eCurState == CMonster::DEAD)
			m_tFrame.iFrameStart = 2;
		else
			m_tFrame.iFrameStart = 0;
	}
}
Point CMonster::CheckMove(DIRECTION::DIR eDir)
{
	Point TargetPos = { m_tInfo.fX, m_tInfo.fY };
	bool bCheckIndexRange = false;

	INDEX arrIndexDir[DIRECTION::DIR_END] =
	{
		{ m_tIndex.x - 1, m_tIndex.y },		// LEFT
		{ m_tIndex.x + 1, m_tIndex.y },		// RIGHT
		{ m_tIndex.x, m_tIndex.y - 1 },		// UP
		{ m_tIndex.x, m_tIndex.y + 1 }		// DOWN
	};

	
	CTile* pTargetTile = nullptr;
	pTargetTile = CTileMgr::Get_Instance()->Get_Tile_Info(arrIndexDir[eDir]);
	
	if (nullptr != pTargetTile)
	{
		if ( pTargetTile->Get_IsPass() && pTargetTile->m_bMonsterPass) 
		{
			switch (eDir)
			{
			case DIRECTION::LEFT:
				if (arrIndexDir[LEFT].x - 1 >= 0)
					bCheckIndexRange = true;
				break;
			case DIRECTION::RIGHT:
				if (arrIndexDir[RIGHT].x + 1 <= TILEX)
					bCheckIndexRange = true;
				break;
			case DIRECTION::UP:
				if (arrIndexDir[UP].y - 1 >= 0)
					bCheckIndexRange = true;
				break;
			case DIRECTION::DOWN:
				if (arrIndexDir[DOWN].y + 1 <= TILEY)
					bCheckIndexRange = true;
				break;
			default:
				break;
			}
		}
		else 
			return TargetPos;
	}else 
		return TargetPos;		// 타일이 비어있으면 현재 좌표 반환
	
	// 범위 안의 인덱스 이면
	if (bCheckIndexRange)
	{
		TargetPos = pTargetTile->GET_Tile_Pos();
		// 방향 맴버 변수 바꿔주고
	
		// 타일 좌표 반환
		return TargetPos;
	}
	
	// 현재 좌표 반환
	return TargetPos;
}


void CMonster::Check_Dir()
{
	CObj::UpdateIndex();
	
	int dir = rand() % 2;
	Point CurrentPos = { m_tInfo.fX, m_tInfo.fY };

	switch (m_eDir)
	{
	case DIRECTION::LEFT:
		// 좌

		if (TargetPos.x <= CurrentPos.x)
		{
			m_eDir = DIRECTION::LEFT;
			Move(TargetPos);
			break;
		}
		else 
		{
			if (dir == 0) 
			{
				// 상
				TargetPos = CheckMove(DIRECTION::UP);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::UP;

					break;
				}
				// 하
				TargetPos = CheckMove(DIRECTION::DOWN);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::DOWN;
					break;
				}
			}
			if (dir == 1)
			{
				// 하
				TargetPos = CheckMove(DIRECTION::DOWN);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::DOWN;
					break;
				}
				// 상
				TargetPos = CheckMove(DIRECTION::UP);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::UP;

					break;
				}
			}
		

			TargetPos = CheckMove(DIRECTION::LEFT);
			if (TargetPos != CurrentPos)
			{
				m_eDir = DIRECTION::LEFT;
				break;
			}

			// 우
			m_eDir = DIRECTION::RIGHT;
		}
		break;
	case DIRECTION::RIGHT:
		if (TargetPos.x >= CurrentPos.x)
		{
			Move(TargetPos);
		}
		else
		{
			if (dir == 0)
			{
				// 상
				TargetPos = CheckMove(DIRECTION::UP);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::UP;

					break;
				}
				// 하
				TargetPos = CheckMove(DIRECTION::DOWN);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::DOWN;
					break;
				}
			}
			if (dir == 1)
			{
				// 하
				TargetPos = CheckMove(DIRECTION::DOWN);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::DOWN;
					break;
				}
				// 상
				TargetPos = CheckMove(DIRECTION::UP);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::UP;

					break;
				}
			}
			// 우
			TargetPos = CheckMove(DIRECTION::RIGHT);
			if (TargetPos != CurrentPos)
			{
				m_eDir = DIRECTION::RIGHT;
			
				break;
			}

			// 좌
			m_eDir = DIRECTION::LEFT;

		}
		break;
	case DIRECTION::UP:

		if (TargetPos.y <= CurrentPos.y)
		{
			Move(TargetPos);
		}
		else
		{

			if (dir == 0)
			{
				// 좌
				TargetPos = CheckMove(DIRECTION::LEFT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::LEFT;

					break;
				}
				// 우
				TargetPos = CheckMove(DIRECTION::RIGHT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::RIGHT;

					break;
				}
			}
			if (dir == 1)
			{
				// 우
				TargetPos = CheckMove(DIRECTION::RIGHT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::RIGHT;

					break;
				}
				// 좌
				TargetPos = CheckMove(DIRECTION::LEFT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::LEFT;

					break;
				}
			}
		
			// 상
			TargetPos = CheckMove(DIRECTION::UP);
			if (TargetPos != CurrentPos)
			{
				m_eDir = DIRECTION::UP;
		
				break;
			}

			//하

			m_eDir = DIRECTION::DOWN;
		}
		break;
	case DIRECTION::DOWN:
		if (TargetPos.y >= CurrentPos.y)
		{
			Move(TargetPos);
		}
		else
		{
			if (dir == 0)
			{
				// 좌
				TargetPos = CheckMove(DIRECTION::LEFT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::LEFT;

					break;
				}
				// 우
				TargetPos = CheckMove(DIRECTION::RIGHT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::RIGHT;

					break;
				}
			}
			if (dir == 1)
			{
				// 우
				TargetPos = CheckMove(DIRECTION::RIGHT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::RIGHT;

					break;
				}
				// 좌
				TargetPos = CheckMove(DIRECTION::LEFT);
				if (TargetPos != CurrentPos)
				{
					m_eDir = DIRECTION::LEFT;

					break;
				}
			}
			// 하
			TargetPos = CheckMove(DIRECTION::DOWN);
			if (TargetPos != CurrentPos)
			{
				m_eDir = DIRECTION::DOWN;
		
				break;
			}

			//상
			m_eDir = DIRECTION::UP;
		}
		break;
	default:
		break;
	}

}


void CMonster::Move(Point _TargetPos)
{
	switch (m_eDir)
	{
	case DIRECTION::LEFT:
		if (m_tRect.left > OFFSET_X && m_tRect.left != _TargetPos.x -20.f) {
			m_tInfo.fX -= m_fSpeed;
			if(!m_bSmaller)
				m_eNextState = LEFT;
			if (m_bSmaller)
				m_eNextState = LEFT2;
		}
		break;
	case DIRECTION::RIGHT:
		if (m_tRect.right < 620.f && m_tRect.right != _TargetPos.x +20.f) {
			m_tInfo.fX += m_fSpeed;
			if (!m_bSmaller)
				m_eNextState = RIGHT;
			if (m_bSmaller)
				m_eNextState = RIGHT2;
		}
		break;
	case DIRECTION::UP:
		if (m_tInfo.fY > OFFSET_Y && m_tInfo.fY != _TargetPos.y -20.f) {
			m_tInfo.fY -= m_fSpeed;
			if (!m_bSmaller)
				m_eNextState = UP;
			if(m_bSmaller)
				m_eNextState = UP2;
		}
		break;
	case DIRECTION::DOWN:
		if (m_tRect.bottom < 560.f && m_tRect.bottom != _TargetPos.y +20.f) {
			m_tInfo.fY += m_fSpeed;
			if (!m_bSmaller)
				m_eNextState = DOWN;
			if (m_bSmaller)
				m_eNextState = DOWN2;
		}
		break;
	default:
		break;
	}
}

void CMonster::Set_Smaller(bool _bSmaller)
{
	m_bSmaller = _bSmaller;
}

bool CMonster::Get_Smaller()
{
	return m_bSmaller;
}

void CMonster::Set_Dead()
{
	m_bIsDead = true;
}  

void CMonster::Start_CollisionTime()
{
	m_bStartCollision = false;
	m_dwCollisionDelayTime = GetTickCount();
}

void CMonster::Hit()
{
	if (!m_bSmaller) {
		m_dwRefreshTime = GetTickCount();
		m_bSmaller = true;
	}
	else if (m_bSmaller)
	{
 		m_eNextState = CMonster::DEAD;
		m_bIsFinalHit = true;
		m_dwDeadTime = GetTickCount();
	}
}

