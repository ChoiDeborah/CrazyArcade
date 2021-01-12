#pragma once
#include "Obj.h"
class CExtraBomb :
	public CObj
{
public:
	CExtraBomb();
	virtual ~CExtraBomb();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_Dir(DIRECTION::DIR eDir) { m_eDir = eDir; }
	void Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	void Set_Option(int _iOption) { m_iOption = _iOption; }
	void Set_Type(BOMBTYPE::TYPE eType);
	BOMBTYPE::TYPE Get_Type() { return m_eType; }
	bool m_bBossBomb;
private:
	int m_iOption;
	TCHAR* m_pFrameKey;
	DIRECTION::DIR m_eDir;
	BOMBTYPE::TYPE m_eType;
	DWORD m_dwDestroyTime;

	
};

