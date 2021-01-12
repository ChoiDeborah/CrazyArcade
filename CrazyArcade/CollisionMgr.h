#pragma once
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(OBJLIST& DestList, OBJLIST& SourList, OBJID::ID eDestID, OBJID::ID eSourID);
	static void CollisionRectEX(OBJLIST& DestList, OBJLIST& SourList, OBJID::ID eDestID, OBJID::ID eSourID);
	static void CollisionRectEX(OBJVEC& TileVec, CObj* pPlayer);
	//static void CollisionRectEX(CObj* pPlayer, OBJVEC& TileVec);
	// Ÿ�� ���� �浹 ó��
	static void CollisionRectEx_Tile(CObj* pTargetBox, OBJVEC & TileVec);
	static void CollisionSphere(OBJLIST& DestList, OBJLIST& SourList);
	static void CollisionRectMonstrBomb(OBJLIST& DestList, OBJLIST& SourList);
	static void CollisionRectArroundTile(CTile * pTarget);
	

private:
	static bool CheckSphere(CObj* pDest, CObj* pSour);
	static bool CheckRect(CObj* pDest, CObj* pSour, float* pMoveX, float* pMoveY);

};

