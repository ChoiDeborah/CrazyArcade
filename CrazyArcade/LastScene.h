#pragma once
#include "Scene.h"
class CLastScene :
	public CScene
{
public:
	CLastScene();
	virtual ~CLastScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

