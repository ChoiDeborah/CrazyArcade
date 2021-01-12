#pragma once
class CGameMgr
{
	DECLARE_SINGLETON(CGameMgr)


public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	// ��ǥ �ָ� ���� ����� ���� ��ȯ
	POINT Get_Tile_Positon_From_Position(POINT _pos);
	POINT Get_Tile_Positon_From_Position(float _posX, float _posY);
	// ��ǥ �ָ� �ε��� ��
	INDEX Get_Index_From_Position(POINT _pos);
	INDEX Get_Index_From_Position(float _posX, float _posY);
	// �ε��� �ָ� ��ǥ �ִ� �� 
	POINT  Get_Posiotn_From_Index(INDEX _index);

	// ��ǥ �ָ� ��Ʈ �ִ� ��
	RECT Get_Rect_From_Position(POINT _pos, float _fCX, float _fCY);
	RECT GET_Rect_From_Index(INDEX _index, float _fCX, float _fCY);
	bool m_bCollision;

public:
	MAPINFO* Get_MapInfo(INDEX _index);
	void Set_MapInfo(INDEX _index, bool _bIsExist, bool _bIsBoom);
	bool m_bGameLose;
	bool m_bReload;
private:
	// �� ���� �����ϰ� �ִ� �� 
	// ���� �ִ� ��, ������ �ִ� ��
	vector<MAPINFO*> m_vecMapInfo;
	int iNumOfBomb;
	int iLengthOfBomb;


};

