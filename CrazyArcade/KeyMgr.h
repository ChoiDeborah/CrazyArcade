#pragma once
#define VK_MAX	0xff

class CKeyMgr
{
public:
	CKeyMgr();
	~CKeyMgr();
public:
	static CKeyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;
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
	bool KeyPressing(int iKey);
	bool KeyDown(int iKey);
	bool KeyUP(int iKey);
	void KeyUpdate();
	
private:
	static CKeyMgr* m_pInstance;
	bool m_bKeyState[VK_MAX];
};

