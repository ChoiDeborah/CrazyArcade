#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	// 요거는 원 충돌할 때 사용할 것. 
	const INFO& Get_Info()const { return m_tInfo; }
	// 요건 사각형 충돌할 때 사용할 것. 
	// 그리는 렉트
	const RECT& Get_Rect()const { return m_tRect; }
	// 충돌 렉트
	const RECT& Get_CollisionRect()const { return m_tCollisionRect; }
public:
	void Set_Pos(float fx, float fy)
	{
		m_tInfo.fX = fx;
		m_tInfo.fY = fy;
	}
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Dead() { m_bIsDead = true; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
public:
	virtual void Initialize() = 0;
	virtual int  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
public:
	bool operator<(const CObj* other)
	{
		if (nullptr == other)
			return false;

		if (this->m_bFlat == true)
			return false;
		/*
		if (Dst->m_bTop == true)
			return false;
		*/
		return this->Get_Info().fY < other->Get_Info().fY;
	}


	void UpdateRect();
	void UpdateIndex();
	void FrameMove();
	virtual void LateInit();
	void Set_Rect_X(float _offset);
	void Set_Rect_Y(float _offset);
	INDEX Get_Index() { return m_tIndex; }
	Point Get_Position();
	const GroupID::ID Get_GroupID() { return m_eGroupID; }
	void Set_Index(int x, int y) { m_tIndex.x = x; m_tIndex.y = y; };
	bool Get_IsFlat() { return m_bFlat; }
	void Set_IsFlat(bool _isflat) { m_bFlat = _isflat; }
	OBJID::ID m_eOBJID;
	// Y축 소팅 시 가장 밑에 그려질 변수
	bool m_bFlat;
	bool m_bTop;
protected:
	GroupID::ID m_eGroupID;
	INFO m_tInfo;
	RECT m_tRect;
	RECT m_tCollisionRect;
	FRAME m_tFrame;
	float m_fSpeed;
	float m_fAngle;
	bool m_bIsDead;
	CObj* m_pTarget;
	bool m_bIsInit;
	INDEX m_tIndex;
};

