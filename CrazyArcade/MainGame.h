#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	// 초기화를 위한 함수. 
	void Initialize();
	// 전체적인 로직이 들어갈 함수. 
	void Update();
	// 같은 로직이나 순서상 좀 늦게 돌아가야하는 것들이 들어갈 함수. 
	void LateUpdate();
	// 그림 그릴 함수. 
	void Render();
	// 헤제 할 함수. 
	void Release();

public:


private:
	HDC m_hDC;
	TCHAR m_FPS[32];
	DWORD m_dwTime;
	int m_iFPS;

};

