#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Bomb.h"
#include "Tile.h"
#include "TileMgr.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include "TileMgr.h"
#include "Boss.h"
#include "ExtraBomb.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRectMonstrBomb(OBJLIST & DestList, OBJLIST & SourList)
{
	RECT rc = {};
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (IntersectRect(&rc, &pDst->Get_Rect(), &pSrc->Get_Rect()))
			{
				//cout << "1" << endl;
				CMonster * pMonster = dynamic_cast<CMonster*>(pDst);

				if (pMonster->m_bStartCollision)
				{
					pMonster->Start_CollisionTime();
					pMonster->Hit();

				}
			}
		}
	}
}

void CCollisionMgr::CollisionRectArroundTile(CTile * pTargetTile)
{
	if (nullptr != pTargetTile)
	{
		INDEX TileIndex = pTargetTile->Get_Index();
		INDEX indexDir[4];
		float fMoveX = 0.f, fMoveY = 0.f;
		INDEX index;
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{

				// UP
			case 0:
				index = INDEX(TileIndex.x, TileIndex.y - 1);
				break;
				// DOWN
			case 1:
				index = INDEX(TileIndex.x, TileIndex.y + 1);
				break;
				// RIGHT
			case 2:
				index = INDEX(TileIndex.x + 1, TileIndex.y);
				break;
				// LEFT
			case 3:
				index = INDEX(TileIndex.x - 1, TileIndex.y);
				break;

			}

		}

		int iIndex = index.x + (index.y * TILEX);

		if (0 > iIndex || CTileMgr::Get_Instance()->Get_TileVector().size() <= (size_t)iIndex)
			return;

		//다른 타일 
		CTile* pDst = CTileMgr::Get_Instance()->Get_Tile_Info(index);
		CTile* pSrc = CTileMgr::Get_Instance()->Get_Tile_Info(TileIndex);

		float x = pSrc->Get_Info().fX;
		float y = pSrc->Get_Info().fY;

		// 지나갈 수 없는 타일 이면
		if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY) && !pDst->m_bIsPass)
		{
			float x = pSrc->Get_Info().fX;
			float y = pSrc->Get_Info().fY;
			//cout << "2" << endl;
			if (fMoveX > fMoveY)
			{

				if (y < pDst->Get_Info().fY)
					fMoveY *= -1.f;

				pSrc->Set_Pos(x, y + fMoveY);
			}
			else
			{

				if (x < pDst->Get_Info().fX)
					fMoveX *= -1.f;

				pSrc->Set_Pos(x + fMoveX, y);



			}
		}


	}
}


void CCollisionMgr::CollisionRect(OBJLIST & DestList, OBJLIST & SourList, OBJID::ID eDestID, OBJID::ID eSourID)
{
	RECT rc = {};
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{

			if (IntersectRect(&rc, &pDst->Get_Rect(), &pSrc->Get_Rect()))
			{
	//			cout << "3" << endl;
				//pDst->Set_Dead();
				//pSrc->Set_Dead();

				if (eDestID == OBJID::ITEM  && eSourID == OBJID::PLAYER)
				{
					// 아이템 먹기
					int iTypeOfItem = dynamic_cast<CItem*>(pDst)->Get_Type();
					dynamic_cast<CPlayer*>(pSrc)->Take_Item(iTypeOfItem);
					// 아이템은 삭제
					pDst->Set_Dead();
				}

				if (eDestID == OBJID::PLAYER && eSourID == OBJID::MONSTER)
				{
					//물풍선과 충돌 시 아이템 삭제
					pDst->Set_Dead();
				}

				if (eDestID == OBJID::ITEM && eSourID == OBJID::EXTRA_BOMB)
				{
					pDst->Set_Dead();
				}

				if (eDestID == OBJID::BOSS && eSourID == OBJID::EXTRA_BOMB)
				{
					CBoss* pBoss = dynamic_cast<CBoss*>(pDst);
					if (pBoss->m_bStartCollision && !dynamic_cast<CExtraBomb*>(pSrc)->m_bBossBomb)
					{
						pBoss->Start_CollisionTime();
						pBoss->Demage();
					}
				}

				// 물풍선 보스
				if (eDestID == OBJID::BOMB && eSourID == OBJID::BOSS)
				{
					CBomb* pBomb = dynamic_cast<CBomb*>(pDst);
					pBomb->Set_State_Boom();
				}

				if (eDestID == OBJID::BOMB && eSourID == OBJID::TILE)
				{
					if(!dynamic_cast<CTile*>(pSrc)->m_bIsPass)
						 pDst->Set_Speed(0);
				}

				
				if (eDestID == OBJID::PLAYER && 
					(eSourID == OBJID::EXTRA_BOMB || eSourID == OBJID::BOMB))
				{
					dynamic_cast<CPlayer*>(pDst)->Set_State_Bubble();
				}

				if (eDestID == OBJID::BOSS && eSourID == OBJID::PLAYER)
				{
					if (9 == dynamic_cast<CBoss*>(pDst)->Get_State())
					{
						dynamic_cast<CBoss*>(pDst)->Set_State_Dead();
					}
				}
				/*
				if (eDestID == OBJID::BOMB && eSourID == OBJID::EXTRA_BOMB)
				{
					dynamic_cast<CBomb*>(pDst)->Set_State_Boom();
				}

				if (eDestID == OBJID::BOMB && eSourID == OBJID::BOMB)
				{
					if (pDst != pSrc)
						pDst->Set_Dead();
				}
				*/
			}
		}
	}
}

void CCollisionMgr::CollisionRectEX(OBJLIST & DestList, OBJLIST & SourList, OBJID::ID eDestID, OBJID::ID eSourID)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (eDestID == OBJID::BOMB && eSourID == OBJID::PLAYER)
			{
				Point posDest = pDst->Get_Position();
				Point posSour = pSrc->Get_Position();
				float fDist = sqrtf((posDest.x - posSour.x) *(posDest.x - posSour.x) +
					(posDest.y - posSour.y) * (posDest.y - posSour.y));

				// 플레이어와 폭탄 간 거리가 20 이상이면 충돌 시작 
				if (fDist > 30.f)
				{
					if (!dynamic_cast<CBomb*>(pDst)->Get_Start_Collision())
						dynamic_cast<CBomb*>(pDst)->Set_Start_Collision(true);
				}

				CPlayer * pPlayer = dynamic_cast<CPlayer*>(pSrc);
				CBomb * pBomb = dynamic_cast<CBomb*>(pDst);

				if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY) && dynamic_cast<CBomb*>(pDst)->Get_Start_Collision())
				{
					cout << "4" << endl;
					float x = pSrc->Get_Info().fX;
					float y = pSrc->Get_Info().fY;

					//pBomb->Set_Speed(0);

					if (fMoveX > fMoveY)
					{
						if (!pPlayer->m_bKick)
						{
							if (y < pDst->Get_Info().fY)
								fMoveY *= -1.f;

							pSrc->Set_Pos(x, y + fMoveY);
						}

						else if (pPlayer->m_bKick)
						{
							if (y < pDst->Get_Info().fY)
								fMoveY *= -1.f;

							if (fMoveY < 0)
								pBomb->m_eDir = DIRECTION::DOWN;
							if (fMoveY > 0)
								pBomb->m_eDir = DIRECTION::UP;

						}
						
					
					}
					else
					{
						if (!pPlayer->m_bKick)
						{
							if (x < pDst->Get_Info().fX)
								fMoveX *= -1.f;

							pSrc->Set_Pos(x + fMoveX, y);
						}
						else if (pPlayer->m_bKick)

						{
							if (x < pDst->Get_Info().fX)
								fMoveX *= -1.f;

							if (fMoveX < 0)
								pBomb->m_eDir = DIRECTION::RIGHT;
							if (fMoveX > 0)
								pBomb->m_eDir = DIRECTION::LEFT;

						}

					}
				}

				if (eDestID == OBJID::TILE && eSourID == OBJID::BOMB)
				{

					if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY) && dynamic_cast<CBomb*>(pDst)->Get_Start_Collision())
					{
						//cout << "5" << endl;
						float x = pSrc->Get_Info().fX;
						float y = pSrc->Get_Info().fY;
						pSrc->Set_Speed(0);

						if (fMoveX > fMoveY)
						{

							if (y < pDst->Get_Info().fY)
								fMoveY *= -1.f;

							pSrc->Set_Pos(x, y + fMoveY);
						}
						else
						{

							if (x < pDst->Get_Info().fX)
								fMoveX *= -1.f;

							pSrc->Set_Pos(x + fMoveX, y);



						}
					}
				}
			}
		}

	}
}

void CCollisionMgr::CollisionRectEX(OBJVEC& TileVec, CObj* pPlayer)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDst : TileVec)
	{
		// 통과할 수 없으면서 밀 수 없으면 
		if (!dynamic_cast<CTile*>(pDst)->Get_IsPass() && !dynamic_cast<CTile*>(pDst)->Get_IsPush())
		{
			if (CheckRect(pDst, pPlayer, &fMoveX, &fMoveY))
			{
				//cout << "6" << endl;
				float x = pPlayer->Get_Info().fX;
				float y = pPlayer->Get_Info().fY;

				if (fMoveX > fMoveY)
				{
					if (y < pDst->Get_Info().fY)
						fMoveY *= -1.f;

					pPlayer->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pDst->Get_Info().fX)
						fMoveX *= -1.f;

					pPlayer->Set_Pos(x + fMoveX, y);
				}
			}
		}

		// 밀 수 있으면
		if (dynamic_cast<CTile*>(pDst)->Get_IsPush())
		{
			if (CheckRect(pDst, pPlayer, &fMoveX, &fMoveY))
			{
				//cout << "7" << endl;
				float x = pDst->Get_Info().fX;
				float y = pDst->Get_Info().fY;
				//cout << x << "," << y << endl;

				// 박스 무게감 있게 0.2 곱해서 밀어주기.

				if (fMoveX > fMoveY)
				{
					if (y < pPlayer->Get_Info().fY)
						fMoveY *= -0.2f;

					pDst->Set_Pos(x, y + fMoveY);

				}
				else
				{
					if (x < pPlayer->Get_Info().fX)
						fMoveX *= -0.2f;

					pDst->Set_Pos(x + fMoveX, y);
				}

				// 현재 박스랑 사방의 다른 박스랑 충돌처리
				//CollisionRectEx_Tile(pDst, TileVec);
				CollisionRectArroundTile(dynamic_cast<CTile*>(pDst));

				// 상자 밖으로 안나가게 처리
				// 플레이어가 안으로 들어간다.. 왜죠?
				if (pDst->Get_Info().fX > 600.f)
					pDst->Set_Pos(600, y);
				if (pDst->Get_Info().fX < 40.f)
					pDst->Set_Pos(40.f, y);
				if (pDst->Get_Info().fY > 540.f)
					pDst->Set_Pos(x, 540.f);
				if (pDst->Get_Info().fY < 60.f)
					pDst->Set_Pos(x, 60.f);
			}

			if (pDst->Get_Info().fX == 600.f || pDst->Get_Info().fY == 60.f ||
				pDst->Get_Info().fY == 540.f || pDst->Get_Info().fX == 40.f)
			{
				//플레이어 밀어주기
				if (CheckRect(pDst, pPlayer, &fMoveX, &fMoveY))
				{
					//cout << "8" << endl;
					float x = pPlayer->Get_Info().fX;
					float y = pPlayer->Get_Info().fY;
					//cout << x << "," << y << endl;
					// 박스 무게감 있게 0.2 곱해서 밀어주기.
					if (fMoveX > fMoveY)
					{
						if (y < pDst->Get_Info().fY)
							fMoveY *= -1.f;

						pPlayer->Set_Pos(x, y + fMoveY);
					}
					else
					{

						if (x < pDst->Get_Info().fX)
							fMoveX *= -1.f;

						pPlayer->Set_Pos(x + fMoveX, y);
					}
				}
			}
		}
	}
}




void CCollisionMgr::CollisionRectEx_Tile(CObj * pTargetBox, OBJVEC & TileVec)
{
	CTile* pSrc = dynamic_cast<CTile*>(pTargetBox);
	CTile *pDst = nullptr;
	INDEX index = pTargetBox->Get_Index();

	//CTile* pSrc = dynamic_cast<CTile*>(pTargetBox);

	for (auto& pDst : TileVec)
	{
		//pDst = dynamic_cast<CTile*>(pDst);
		float fMoveX = 0.f;
		float fMoveY = 0.f;
		if (!dynamic_cast<CTile*>(pDst)->Get_IsPass() && !pSrc->Get_IsPass())
		{
			if (pDst == pSrc)
				break;
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				//cout << "9" << endl;
				float x = pSrc->Get_Info().fX;
				float y = pSrc->Get_Info().fY;

				if (fMoveX > fMoveY)
				{
					if (y < pDst->Get_Info().fY)
						fMoveY *= -1.f;
					//pDst->Set_Pos(x, y + fMoveY);
					pSrc->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pDst->Get_Info().fX)
						fMoveX *= -1.f;
					//pDst->Set_Pos(x + fMoveX, y);
					pSrc->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}

	//for (int i = 0; i < 4; ++i)
	//{
	//	switch (i)
	//	{
	//	case 0:
	//		pDst = CTileMgr::Get_Instance()->Get_Tile_Info(INDEX(index.x, index.y - 1));
	//		break;
	//	case 1:
	//		pDst = CTileMgr::Get_Instance()->Get_Tile_Info(INDEX(index.x, index.y + 1));
	//		break;
	//	case 2:
	//		pDst = CTileMgr::Get_Instance()->Get_Tile_Info(INDEX(index.x + 1, index.y));
	//		break;
	//	case 3:
	//		pDst = CTileMgr::Get_Instance()->Get_Tile_Info(INDEX(index.x - 1, index.y));
	//		break;
	//	}
	//	float fMoveX = 0.f, fMoveY = 0.f;

	//	if (nullptr != pDst) 
	//	{
	//		if (!pDst->Get_IsPass() && !pSrc->Get_IsPass())
	//		{
	//			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
	//			{
	//				float x = pSrc->Get_Info().fX;
	//				float y = pSrc->Get_Info().fY;

	//				if (fMoveX > fMoveY)
	//				{
	//					if (y < pDst->Get_Info().fY)
	//						fMoveY *= -1.f;
	//					//pDst->Set_Pos(x, y + fMoveY);
	//					pSrc->Set_Pos(x, y + fMoveY);
	//				}
	//				else
	//				{
	//					if (x < pDst->Get_Info().fX)
	//						fMoveX *= -1.f;
	//					//pDst->Set_Pos(x + fMoveX, y);
	//						pSrc->Set_Pos(x + fMoveX, y);
	//				}
	//			}
	//		}
	//	}
	//}
}

void CCollisionMgr::CollisionSphere(OBJLIST & DestList, OBJLIST & SourList)
{
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (CheckSphere(pDst, pSrc))
			{
				pDst->Set_Dead();
				pSrc->Set_Dead();
			}
		}
	}
}


bool CCollisionMgr::CheckSphere(CObj * pDest, CObj * pSour)
{
	// 반지름의 합 구하기. 
	float fRadiusSum = (pDest->Get_Info().fCX * 0.5f) + (pSour->Get_Info().fCX * 0.5f);
	// 밑변과 높이 구하기. 
	float fx = pDest->Get_Info().fX - pSour->Get_Info().fX;
	float fy = pDest->Get_Info().fY - pSour->Get_Info().fY;

	// 피타고라스의 정리를 사용하여 거리를 구하기. 
	float fDist = sqrtf(fx * fx + fy * fy); // a^2 + b^2 = fDist;
											// 거리와 반지름의 합으로 충돌판정. 
	return fDist <= fRadiusSum;
}

bool CCollisionMgr::CheckRect(CObj * pDest, CObj * pSour, float * pMoveX, float * pMoveY)
{
	// 반지름의 합. 
	float fRadiusSumX = (pDest->Get_Info().fCX * 0.5f) + (pSour->Get_Info().fCX * 0.5f);
	float fRadiusSumY = (pDest->Get_Info().fCY * 0.5f) + (pSour->Get_Info().fCY * 0.5f);

	float fDistX = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float fDistY = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	if (fRadiusSumX >= fDistX && fRadiusSumY >= fDistY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}

	return false;
}
