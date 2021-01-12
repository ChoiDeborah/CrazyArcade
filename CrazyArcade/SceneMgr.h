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
	// 이것이 다음씬 받아올것 
	SceneID::ID m_eNextScene;
	// 이것이 현재씬 가지고 있을것. 
	SceneID::ID m_eCurScene;
};

