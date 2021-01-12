#pragma once
#include "Scene.h"
class CMapEditor :
	public CScene
{
public:
	CMapEditor();
	virtual ~CMapEditor();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Render_Line(HDC hDC);
};

