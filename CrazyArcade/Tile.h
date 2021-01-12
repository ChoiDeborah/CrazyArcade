#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void Set_Option(int iOption);
	int Get_DrawID(void) { return m_iDrawID; }
	int Get_Option(void) { return m_iOption; }

	void Set_IsPass(bool _bIsPass) { m_bIsPass = _bIsPass; }
	void Set_IsBroken(bool _bIsBroken) { m_bIsPass = _bIsBroken; }
	void Set_IsPush(bool _bIsPush) { m_bIsPush = _bIsPush; }

	bool Get_IsPass() { return m_bIsPass; }
	bool Get_IsBroken() { return m_bIsBroken; }
	bool Get_IsPush() { return m_bIsPush; }
	bool Get_IsBoom() { return m_bIsBoom; }
	void Create_Item();
	void Update_Option();
	// 타일 옮겨지면 옵션 바꿔주는 함수
	void Check_Move_Tile();
	void reset_option(int _option) 
	{ 
		m_iOption = 0;
		m_pFrameKey = L"";
	}

	TCHAR* Get_Key()
	{
		return m_pFrameKey;
	}
public:
	void UpdateRect();

	void Set_Tile_Size(float _fCX, float _fCY);
	INDEX Get_Tile_Index() { return m_tIndex; };
	Point GET_Tile_Pos();
	
	int m_iOption;
	int m_iDrawID;

	// 통과 가능한가?
	bool m_bIsPass;
	// 부서지는가?
	bool m_bIsBroken;
	// 밀어지는가?
	bool m_bIsPush;
	// 터지는가?
	bool m_bIsBoom;
	bool m_bMonsterPass;

	// DC 얻어올 변수
	TCHAR* m_pFrameKey;

	int m_iHeight;
	INDEX m_tPrevIndex;
};

