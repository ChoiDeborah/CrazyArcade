#pragma once
class CLine;
class CLineMgr
{
public:
	CLineMgr();
	~CLineMgr();
public:
	static CLineMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Render(HDC hDC);
	void Release();
public:
	bool LineCollision(float fInX, float* pOutY);
	void LoadData();
private:
	static CLineMgr* m_pInstance;
	list<CLine*> m_listLine;
};

