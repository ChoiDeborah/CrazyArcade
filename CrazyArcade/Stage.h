#pragma once
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene을(를) 통해 상속됨
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

