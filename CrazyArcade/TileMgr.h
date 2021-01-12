#pragma once
class CTile;
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)

public:
	enum MAPID {CAMP, MAP_END};

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	void Show_Tile(HDC hDC);
	void Show_Mouse_Positon(HDC hDC) const;
public:
	void PickTile(const POINT& pt, const int iDrawID, const int iOption);
	void Save_Tile();
	void Load_Tile(TCHAR* pFilePath);
public:
	void Set_TileOption(int _iTileNum)
	{
		m_iOption += _iTileNum;
		if (m_iOption < 1)
			m_iOption = 1;
		if (m_iOption > NUMOFTILE)
			m_iOption = NUMOFTILE;
	}

public:
	CTile* Get_Tile_Info(INDEX _index);

	vector<CObj*> Get_TileVector() { return m_vecTile;  };
private:
	vector<CObj*> m_vecTile;
	TCHAR* m_pFrameKey;
	int m_iOption;
	int m_iDrawID;
	INFO m_tInfo;
	//¸¶¿ì½º ÁÂÇ¥ 
	POINT pt;
};

