#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	
public:
	void Set_Index(INDEX _index);
	int Get_Type() { return m_iTypeOfItem; };
	void Set_Type(int _iType);
public:
	int m_iTypeOfItem;
	bool m_bExist;
	TCHAR* m_pFrameKey;
};

