#pragma once
class CEditorLine;
class CEditorLineMgr
{
private:
	CEditorLineMgr();
	~CEditorLineMgr();
public:
	static CEditorLineMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEditorLineMgr;

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
	void Update();
	void Release();
private:
	void SaveData();

private:
	static CEditorLineMgr* m_pInstance;
	list<CEditorLine*> m_listLine;
};