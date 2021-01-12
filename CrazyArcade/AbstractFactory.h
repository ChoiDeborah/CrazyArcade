#pragma once

template<class T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fx, float fy)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fx, fy);
		return pObj;
	}

	static CObj* Create(int x, int y)
	{
		CObj* pObj = new T;
		
		pObj->Set_Index(x, y);
		pObj->Initialize();
		return pObj;
	}
};