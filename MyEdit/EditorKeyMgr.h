#pragma once
#define VK_MAX 0xff
class CEditorKeyMgr
{
private:
	CEditorKeyMgr();
	~CEditorKeyMgr();

public:
	static CEditorKeyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEditorKeyMgr;
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
	static CEditorKeyMgr* m_pInstance;
	bool m_bKeyState[VK_MAX];
};