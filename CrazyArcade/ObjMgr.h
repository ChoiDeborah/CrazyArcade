#pragma once
class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void Destory_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	CObj* Get_Player() { return m_Objlist[OBJID::PLAYER].front(); }
	CObj* Get_Target(CObj* pSrc, OBJID::ID eID);
public:
	void AddObject(OBJID::ID eID, CObj* pObj);
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
	void DeleteID(OBJID::ID eID);
	OBJLIST Get_Objlist(OBJID::ID eID);
	bool CompareYOrder(CObj* left, CObj* right);

private:
	static CObjMgr* m_pInstance;
	OBJLIST m_Objlist[OBJID::END];
	OBJLIST m_RenderSort[GroupID::END];
};

