#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum STATE { IDLE, DOWN, RIGHT, LEFT, UP, BUBBLE, DEAD, UNDEAD};
public:
	CPlayer();
	virtual ~CPlayer();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	template<class T>
	CObj* CreateBomb()
	{
		CObj* pObj = CAbstractFactory<T>::Create(float(m_tPosin.x), static_cast<float>(m_tPosin.y));
		pObj->Set_Angle(m_fAngle);
		pObj->Set_Target(this);
		return pObj;
	}

public:
	void KeyCheck();
	void SceneChange();
	void FrameMove();
	void Take_Item(int _iItemType);
	void Use_Niddle();

	void Set_State_Bubble();
	bool m_bKick;

	CTile* m_pTargetTile;
	CTile* Get_Pushing_Tile();
	bool Get_IsKick() { return m_bKick; }
private:
	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState;
	DWORD m_dwBubbleTime;
	bool m_bIsBubble;
	int m_iLengthOfBomb;
	int m_iNumOfBomb;
	bool m_bNeedle;
	DWORD m_dwNiddleTime;
	
	bool m_Developter;
	DWORD m_dwCreateBoomTime;
	bool m_bIsDrop;

};

