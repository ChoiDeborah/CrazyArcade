#pragma once
class CEditor
{
public:
	CEditor();
	~CEditor();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
private:
	HDC m_hDC;
};

