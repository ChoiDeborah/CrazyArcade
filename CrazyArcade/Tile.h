#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	// CObj��(��) ���� ��ӵ�
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
	// Ÿ�� �Ű����� �ɼ� �ٲ��ִ� �Լ�
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

	// ��� �����Ѱ�?
	bool m_bIsPass;
	// �μ����°�?
	bool m_bIsBroken;
	// �о����°�?
	bool m_bIsPush;
	// �����°�?
	bool m_bIsBoom;
	bool m_bMonsterPass;

	// DC ���� ����
	TCHAR* m_pFrameKey;

	int m_iHeight;
	INDEX m_tPrevIndex;
};

