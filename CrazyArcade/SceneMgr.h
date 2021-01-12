#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)


public:
	void SceneChange(SceneID::ID eScene);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	SceneID::ID Get_SceneID() { return m_eCurScene; }

private:
	CScene* m_pScene;
	// �̰��� ������ �޾ƿð� 
	SceneID::ID m_eNextScene;
	// �̰��� ����� ������ ������. 
	SceneID::ID m_eCurScene;
};

