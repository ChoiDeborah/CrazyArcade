#pragma once
#include "Scene.h"
class CMapEditor :
	public CScene
{
public:
	CMapEditor();
	virtual ~CMapEditor();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Render_Line(HDC hDC);
};

