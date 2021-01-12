#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;



CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj * CObjMgr::Get_Target(CObj * pSrc, OBJID::ID eID)
{
	if (m_Objlist[eID].empty())
		return nullptr;

	CObj* pTarget = m_Objlist[eID].front();
	float x = pTarget->Get_Info().fX - pSrc->Get_Info().fX;
	float y = pTarget->Get_Info().fY - pSrc->Get_Info().fY;
	float fDist = sqrtf(x* x + y * y);

	for (auto& pDest : m_Objlist[eID])
	{
		float x1 = pDest->Get_Info().fX - pSrc->Get_Info().fX;
		float y1 = pDest->Get_Info().fY - pSrc->Get_Info().fY;
		float fDist1 = sqrtf(x1* x1 + y1 * y1);

		if (fDist > fDist1)
		{
			pTarget = pDest;
			fDist = fDist1;
		}
	}
	return pTarget;
}

void CObjMgr::AddObject(OBJID::ID eID, CObj * pObj)
{
	m_Objlist[eID].emplace_back(pObj);
}

int CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (OBJITER iter = m_Objlist[i].begin(); iter != m_Objlist[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if ((*iter) != nullptr)
				{
					delete *iter;
					*iter = nullptr;
					iter = m_Objlist[i].erase(iter);
				}
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::LateUpdate()
{
	// for y sorting 
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_Objlist[i])
		{
			pObj->LateUpdate();
			if (m_Objlist[i].empty())
				break;

			GroupID::ID eGroupID = pObj->Get_GroupID();
			if(!pObj->m_bTop)
				m_RenderSort[eGroupID].emplace_back(pObj);

		}
	}
	
	//CCollisionMgr::CollisionRectEX(m_Objlist[OBJID::PLAYER], m_Objlist[OBJID::MONSTER]);
	CCollisionMgr::CollisionRectEX(m_Objlist[OBJID::BOMB], m_Objlist[OBJID::PLAYER], OBJID::BOMB, OBJID::PLAYER);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < GroupID::END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);
		for (auto & pObj : m_RenderSort[i])
		{
			pObj->Render(hDC);

			if (nullptr == pObj)
					break;
		}
		// 보스 가장 위에 출력
		if(!CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS).empty())
			CObjMgr::Get_Instance()->Get_Objlist(OBJID::BOSS).front()->Render(hDC);
		if(!m_RenderSort[i].empty())
			m_RenderSort[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_Objlist[i])
		{
			// 타일은 벡터에서 같은 메모리 참조
			// 여기서 지우지 마
			if (i != OBJID::TILE)
			{
				if (nullptr != pObj)
				{
					delete pObj;
					pObj = nullptr;
				}
			}
		}
		m_Objlist[i].clear();
	}
}

void CObjMgr::DeleteID(OBJID::ID eID)
{
	if (eID == OBJID::TILE)
	{
		m_Objlist[OBJID::TILE].clear();
		return;
	}
	for (auto& pObj : m_Objlist[eID])
	{
		if (pObj)
		{
			delete pObj;
			pObj = nullptr;
		}
	}
	m_Objlist[eID].clear();
}

OBJLIST CObjMgr::Get_Objlist(OBJID::ID eID)
{
	return m_Objlist[eID];
}
