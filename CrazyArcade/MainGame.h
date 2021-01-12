#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	// �ʱ�ȭ�� ���� �Լ�. 
	void Initialize();
	// ��ü���� ������ �� �Լ�. 
	void Update();
	// ���� �����̳� ������ �� �ʰ� ���ư����ϴ� �͵��� �� �Լ�. 
	void LateUpdate();
	// �׸� �׸� �Լ�. 
	void Render();
	// ���� �� �Լ�. 
	void Release();

public:


private:
	HDC m_hDC;
	TCHAR m_FPS[32];
	DWORD m_dwTime;
	int m_iFPS;

};

