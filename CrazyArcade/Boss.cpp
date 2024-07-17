#include "stdafx.h"
#include "Boss.h"
#include "BitmapMgr.h"
#include "GameMgr.h"
#include "TileMgr.h"
#include "ExtraBomb.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"

CBoss::CBoss() :
	m_eCurState(STATE_END),
	m_eNextState(STATE_END),
	m_pFrameKey(L""),
	m_bStartCollision(true),
	m_bAttack(false),
	m_bIsRight(false),
	m_bIsLeft(false),
	m_bDemage(false),
	m_iHp(80)
{
	m_bTop = true;
}



CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;
	m_iHeight = 156.f;
	m_fSpeed = 1.f;

	POINT pos = CGameMgr::Get_Instance()->Get_Posiotn_From_Index(m_tIndex);
	m_tInfo.fX = (float)pos.x;
	m_tInfo.fY = (float)pos.y;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Attack_1.bmp", L"Boss_Attack_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Attack_2_Left.bmp", L"Boss_Attack_2_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Attack_2_Right.bmp", L"Boss_Attack_2_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Hurt.bmp", L"Boss_Hurt");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/ProgBar.bmp", L"ProgBar");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/UI/Bar.bmp", L"Bar");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Bubble.bmp", L"Boss_Bubble");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Hurt.bmp", L"Boss_Hurt");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Idle.bmp", L"Boss_Idle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Left.bmp", L"Boss_Left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Right.bmp", L"Boss_Right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Up.bmp", L"Boss_Up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Resource/Texture/Mon/Boss_Dead.bmp", L"Boss_Dead");

	TargetPos = { m_tInfo.fX, m_tInfo.fY };
	m_dwCollisionDelayTime = GetTickCount();
	m_eNextState = IDLE;
	m_dwDeadTime = 0.f;
	m_dwSkillTime = GetTickCount();
}

int CBoss::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	// 충돌 딜레이
	if (!m_bStartCollision && m_dwCollisionDelayTime + 1000 < GetTickCount())
	{
		m_bStartCollision = true;
	}

	if (m_dwSkillTime + 5000 < GetTickCount() && m_eCurState != BUBBLE && m_eCurState != DEAD)
	{
		m_dwSkillTime = GetTickCount();
		Attack(1);
	}
	if (m_eCurState == CBoss::ATTACK_2_LEFT)
	{
		if (m_tInfo.fX > 80.f)
			m_tInfo.fX -= 3.f;
		else m_eNextState = CBoss::IDLE;
	}

	if (m_eCurState == CBoss::ATTACK_2_RIGHT)
	{
		if (m_tInfo.fX < 560.f)
			m_tInfo.fX += 3.f;
		else m_eNextState = CBoss::IDLE;
	}

	if (m_bDemage && m_dwDemageTime + 500 < GetTickCount())
	{
		//m_eNextState = IDLE;
		//m_bDemage = false
		if (m_iHp <= 0)
		{
			m_iHp = 0;
			m_bDemage = false;
			m_eNextState = BUBBLE;
			//m_dwDeadTime = GetTickCount();
		}
	}

	if (m_eCurState == CBoss::DEAD && m_dwDeadTime + 1000 < GetTickCount())
	{
		m_bIsDead = true;
	}

	SceneChange();
	if (m_eCurState != CBoss::DEAD &&
		m_eCurState != CBoss::HURT&&
		m_eCurState != CBoss::BUBBLE
		&& 
		m_eCurState != CBoss::ATTACK_1
		&&m_eCurState != CBoss::ATTACK_2_LEFT
		&&m_eCurState != CBoss::ATTACK_2_RIGHT)
		Check_Dir();
	
	FrameMove();

	return OBJ_NOEVENT;
}

void CBoss::LateUpdate()
{
	if (m_eCurState != CBoss::DEAD &&
		m_eCurState != CBoss::HURT&&
		m_eCurState != CBoss::BUBBLE&&
		m_bAttack && m_dwSkillTime + 3000 < GetTickCount())
	{
		m_bAttack = false;
		m_eNextState = IDLE;
	}
}

void CBoss::Render(HDC hDC)
{
	CObj::UpdateRect();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_eCurState != CBoss::DEAD)
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 22.5, m_tRect.top - 18, //출력될 위치의 xy 좌표 
			175, 156, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			175 * m_tFrame.iFrameStart,
			0, // 시작 위치 
			175, 156,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 0, 255)
		);
	}

	else
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - 22.5, m_tRect.top - 18, //출력될 위치의 xy 좌표 
			175, 156, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			175 * m_tFrame.iFrameStart,
			0, // 시작 위치 
			175, 156,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
	Point ptProgBar = Point(m_tInfo.fX - 40.f, m_tInfo.fY - 90.f);

	hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"ProgBar");


		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			ptProgBar.x, ptProgBar.y, //출력될 위치의 xy 좌표 
			86, 11, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,
			0, // 시작 위치 
			86, 11,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	

	
	hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Bar");
	
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		ptProgBar.x + 3+m_iHp, ptProgBar.y+2, //출력될 위치의 xy 좌표 
		80-m_iHp, 7, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		0, 0, // 시작 위치 
		80 - m_iHp, 7,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);


	if (CGameMgr::Get_Instance()->m_bCollision)
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

	//// 세로
	//float x = OFFSET_X;
	//float y = OFFSET_Y;

	//for (int i = 0; i < TILEX; ++i)
	//{
	//	x = i * TILESIZEX + OFFSET_X;
	//	MoveToEx(hDC, x, y, NULL);
	//	LineTo(hDC, x, y + MAPSIZEY);
	//}

	//for (int i = 0; i < TILEY; ++i) {
	//	x = OFFSET_X;
	//	y = i * TILESIZEY + OFFSET_Y;
	//	MoveToEx(hDC, x, y, NULL);
	//	LineTo(hDC, x + MAPSIZEX, y);
	//}
}

void CBoss::Release()
{
}

void CBoss::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CBoss::IDLE:
			m_pFrameKey = L"Boss_Idle";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::UP:
			m_pFrameKey = L"Boss_Up";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::DOWN:
			m_pFrameKey = L"Boss_Idle";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::RIGHT:
			m_pFrameKey = L"Boss_Right";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::LEFT:
			m_pFrameKey = L"Boss_Left";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::ATTACK_1:
			m_pFrameKey = L"Boss_Attack_1";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::ATTACK_2_RIGHT:
			m_pFrameKey = L"Boss_Attack_2_Right";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::ATTACK_2_LEFT:
			m_pFrameKey = L"Boss_Attack_2_Left";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::BUBBLE:
			m_pFrameKey = L"Boss_Bubble";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::DEAD:
			m_pFrameKey = L"Boss_Dead";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			break;
		case CBoss::HURT:
			m_pFrameKey = L"Boss_Hurt";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameScene = 0;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CBoss::Check_Dir()
{
	CObj::UpdateIndex();

	int dir = 0;
	Point CurrentPos = { m_tInfo.fX, m_tInfo.fY };

	switch (m_eDir)
	{
	case DIRECTION::LEFT:
		// 좌

		if (TargetPos.x < CurrentPos.x && m_tInfo.fX != 80.f)
		{
			m_eDir = DIRECTION::LEFT;
			Move(TargetPos);
			break;
		}
		else
		{
			dir = rand() % 2;
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
		if (TargetPos.x > CurrentPos.x && m_tInfo.fX != 560.f)
		{
			Move(TargetPos);
		}
		else
		{
			dir = rand() % 2;
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

		if (TargetPos.y < CurrentPos.y && m_tInfo.fY != 140.f)
		{
			Move(TargetPos);
		}
		else
		{
			dir = rand() % 2;
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
		if (TargetPos.y > CurrentPos.y && m_tInfo.fY != 460.f)
		{
			Move(TargetPos);
		}
		else
		{
			dir = rand() % 2;
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


void CBoss::Move(Point _TargetPos)
{
	switch (m_eDir)
	{
	case DIRECTION::LEFT:
		if (m_tInfo.fX >= 79.f) {
			m_tInfo.fX -= m_fSpeed;
			m_eNextState = LEFT;

		}
		break;
	case DIRECTION::RIGHT:
		if (m_tInfo.fX <= 559.f) {
			m_tInfo.fX += m_fSpeed;
			m_eNextState = RIGHT;
		}
		break;
	case DIRECTION::UP:
		if (m_tInfo.fY >= 139.f) {
			m_tInfo.fY -= m_fSpeed;
			m_eNextState = UP;

		}
		break;
	case DIRECTION::DOWN:
		if (m_tInfo.fY <= 459.f)
		{
			m_tInfo.fY += m_fSpeed;
			m_eNextState = DOWN;
		}
		break;
	default:
		break;
	}
}

Point CBoss::CheckMove(DIRECTION::DIR eDir)
{
	Point TargetPos = { m_tInfo.fX, m_tInfo.fY };
	bool bCheckIndexRange = false;

	int iRandWalkLength = rand() % 4 + 1;
	INDEX arrIndexDir[DIRECTION::DIR_END] =
	{
		{ m_tIndex.x - iRandWalkLength, m_tIndex.y },		// LEFT
		{ m_tIndex.x + iRandWalkLength, m_tIndex.y },		// RIGHT
		{ m_tIndex.x, m_tIndex.y - iRandWalkLength },		// UP
		{ m_tIndex.x, m_tIndex.y + iRandWalkLength }		// DOWN
	};


	CTile* pTargetTile = nullptr;
	pTargetTile = CTileMgr::Get_Instance()->Get_Tile_Info(arrIndexDir[eDir]);

	if (nullptr != pTargetTile)
	{
		
			switch (eDir)
			{
			case DIRECTION::LEFT:
				if (arrIndexDir[0].x > 1)
					bCheckIndexRange = true;
				break;
			case DIRECTION::RIGHT:
				if (arrIndexDir[RIGHT].x  < 13)
					bCheckIndexRange = true;
				break;
			case DIRECTION::UP:
				if (arrIndexDir[UP].y > 2 )
					bCheckIndexRange = true;
				break;
			case DIRECTION::DOWN:
				if (arrIndexDir[DOWN].y < 9)
					bCheckIndexRange = true;
				break;
			default:
				break;
			}
		
	
	}
	else
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

void CBoss::Attack(int _skill)
{
	m_bAttack = true;


	int iRand = rand() % 3+1;

	if (iRand == 1)
	{
		CSoundMgr::Get_Instance()->PlayBGM(L"boss2.wav", CSoundMgr::MONSTER);
		m_dwSkillTime = GetTickCount();
		m_eNextState = CBoss::ATTACK_1;
		Create_Boom();
	}

	if (iRand == 2 )
	{
		CSoundMgr::Get_Instance()->PlayBGM(L"boss1.wav", CSoundMgr::MONSTER);
		m_eNextState = CBoss::ATTACK_2_LEFT;
	}

	if (iRand == 3 )
	{
		CSoundMgr::Get_Instance()->PlayBGM(L"boss1.wav", CSoundMgr::MONSTER);
		m_eNextState = CBoss::ATTACK_2_RIGHT;
	}
}

void CBoss::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		if (m_eCurState == CBoss::DEAD || m_eCurState == CBoss::BUBBLE)
		{
			m_tFrame.iFrameStart = 1;
		}
		else
		{
			m_tFrame.iFrameStart = 0;

		}
	}
}

void CBoss::Demage()
{
	m_bDemage = true;
	CSoundMgr::Get_Instance()->PlayBGM(L"boss3.wav", CSoundMgr::MONSTER);

	m_dwDemageTime = GetTickCount();
	m_eNextState = CBoss::HURT;
	m_iHp -= 10;
}

void CBoss::Start_CollisionTime()
{
	m_bStartCollision = false;
	m_dwCollisionDelayTime = GetTickCount();

}

void CBoss::Set_State_Dead()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"boss4.wav", CSoundMgr::MONSTER);
	m_dwDeadTime = GetTickCount();
	m_eNextState = DEAD;
	
}

void CBoss::Create_Boom()
{
	int x = rand() % 13 + 1;
	int y = rand() % 9 + 2;

	INDEX index = INDEX(x, y);
	CObj* pObj = CAbstractFactory<CExtraBomb>::Create(index.x, index.y);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	// 터지고 있는 상황 업데이트
	

	pObj = CAbstractFactory<CExtraBomb>::Create(index.x-1, index.y-1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	// 터지고 있는 상황 업데이트
	
	pObj = CAbstractFactory<CExtraBomb>::Create(index.x, index.y-1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	
	pObj = CAbstractFactory<CExtraBomb>::Create(index.x+1, index.y-1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);

	pObj = CAbstractFactory<CExtraBomb>::Create(index.x-1, index.y);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);

	pObj = CAbstractFactory<CExtraBomb>::Create(index.x, index.y-1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);

	pObj = CAbstractFactory<CExtraBomb>::Create(index.x+1, index.y);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	
	pObj = CAbstractFactory<CExtraBomb>::Create(index.x-1, index.y+1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);

	pObj = CAbstractFactory<CExtraBomb>::Create(index.x-1, index.y+1);
	dynamic_cast<CExtraBomb*>(pObj)->Set_Type(BOMBTYPE::CENTER);
	dynamic_cast<CExtraBomb*>(pObj)->m_bBossBomb = true;
	CObjMgr::Get_Instance()->AddObject(OBJID::EXTRA_BOMB, pObj);
	

}
