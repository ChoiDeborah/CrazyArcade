#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	bool m_bGameEnd;
	DWORD m_dwGameStartTime;
	bool m_bWin;
	bool m_bLose;
	bool m_bGameStart;
	bool m_bResult;
};

