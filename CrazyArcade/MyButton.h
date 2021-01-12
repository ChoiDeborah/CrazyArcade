#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	void Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_Button_Size(float _fCX, float _fCY);

private:
	// DC 얻어올때 쓸 변수
	TCHAR* m_pFrameKey;
	int m_iDrawID;
};

