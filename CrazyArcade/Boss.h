#pragma once
#include "Obj.h"
class CBoss :
	public CObj
{
public:
	CBoss();
	virtual ~CBoss();
public:
	enum STATE {IDLE, UP, DOWN, RIGHT, LEFT, ATTACK_1, ATTACK_2_RIGHT, ATTACK_2_LEFT, HURT, BUBBLE, DEAD, STATE_END };

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SceneChange();
	void Check_Dir();

	void Move(Point _TargetPos);
	Point CheckMove(DIRECTION::DIR eDir);

	void Attack(int _skill);
	void FrameMove();
	void Demage();
	bool m_bStartCollision;
	void Start_CollisionTime();
	int Get_State() { return (int)m_eCurState; };
	void Set_State_Dead();

private:
	DIRECTION::DIR m_eDir;
	int m_iHeight;

	STATE m_eNextState;
	STATE m_eCurState;
	TCHAR* m_pFrameKey;

	// 충돌 딜레이
	DWORD m_dwCollisionDelayTime;
	Point TargetPos;

	DWORD m_dwSkillTime;
	bool m_bAttack;
	bool m_bIsRight;
	bool m_bIsLeft;

	DWORD m_dwDemageTime;
	bool m_bDemage;
	DWORD m_dwDeadTime;
	void Create_Boom();

	int m_iHp;

	

};

