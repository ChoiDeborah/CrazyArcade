#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{

public:
	enum STATE { DOWN, RIGHT, LEFT, UP, DOWN2, RIGHT2, LEFT2, UP2, BUBBLE, DEAD, UNDEAD };

public:
	CMonster();
	virtual ~CMonster();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SceneChange();
	void FrameMove();
	void Check_Dir();
	Point CheckMove(DIRECTION::DIR eDir);
	void Move(Point _TargetPos);
	void Set_HP(int _hp);

public:
	void Set_Smaller(bool _bSmaller);
	bool Get_Smaller();
	void Set_Dead();
	bool Get_Dead() { return m_bIsDead; }

	// for Collision
	//bool m_bCollision;
	DWORD m_dwCollisionDelayTime;
	bool m_bStartCollision;

public:
	void Start_CollisionTime();
	void Hit();
private:
	DIRECTION::DIR m_eDir;
	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState;
	DWORD m_dwRefreshTime;

	float m_fHeight;
	Point TargetPos;
	bool m_bSmaller;
	DWORD m_dwDeadTime;
	bool m_bIsFinalHit;




};

