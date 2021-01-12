#pragma once
#include "Obj.h"
class CBomb :
	public CObj
{
public:
	enum STATE { IDLE, BOOM, DESTROY, STATE_END };
public:
	CBomb();
	virtual ~CBomb();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SceneChange();
	void FrameMove();
	void Render_Boom(HDC _hDC);
	void Boom(HDC _hDC, INDEX index);
	void UpdateState();
	bool Get_IsBoom() { return m_bIsBoom; }
	void Set_Bomb_State(bool _bIsExist, bool _bIsBoom);
	// ��������� Ÿ�� üũ
	bool Dir_Tile_Check(INDEX _index, bool& _bDir);
	void Set_Length(int _iLenth) { m_iLength = _iLenth; };
	void Create_ExtraBoom(INDEX _index, BOMBTYPE::TYPE _eType, bool& bDir);
	void Set_Start_Collision(bool _bCol) { m_bStartCollison = _bCol; }
	bool Get_Start_Collision() { return m_bStartCollison; }
	bool Check_Distance(CObj* pPlayer);
	void Set_State_Boom();
//
public:
	DIRECTION::DIR m_eDir;
private:
	// ������ �ð�
	DWORD m_dwBoomTime;
	// �Ҹ�Ǵ� �ð�
	DWORD m_dwDestroyTime;
	// �׸�
	TCHAR * m_pFrameKey;
	// �����°�?
	bool m_bIsBoom;
	STATE m_eNextState;
	STATE m_eCurState;
	int m_iLength;
	int m_iHeight;
	int m_iWidth;
	bool m_bBoomRender;
	bool bArrDir[DIRECTION::DIR_END];
	// �浹 ���� 
	// �÷��̾�� �Ÿ��� ������ �̻��̸� �浹üũ�Ѵ�.
	bool m_bStartCollison;

};

