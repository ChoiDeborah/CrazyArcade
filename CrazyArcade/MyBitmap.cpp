#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::LoadBmp(const TCHAR * pPath)
{
	// �׸��� �׸����� �ϴ� �ؾ��ϴ� �۾��� ���� ���� ���� DC�� ���� �׷��ְ� �ִ� DC�� ȣȯ�� �ǰԲ� ����� ��� �Ѵ�. 
	// �׷��� DC�� ��� ������. 
	HDC hDC = GetDC(g_hWnd);//
							// ���� �𾾿� ȣȯ�� �ǰԲ� ������ִ°� �ٷ� CreateCompatibleDC
	m_hMemDC = CreateCompatibleDC(hDC); // ���ڸ� �Ѱ��ָ� ���� ����ϰ� �ִ� DC�� ȣȯ�� �Ǵ� �޸� DC�� �Ҵ����ִ� �Լ�. 
										// hDC�� ���̻� �� ������ ���⿡ �׳� �����ϰ� �����ش�. 
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,//���α׷� �ν��Ͻ� �ڵ�. �츮�� ������ ������� ���ð��̱⶧���� ���� �ʿ� ����. 
		pPath,// ������ ��� 
		IMAGE_BITMAP,//��Ʈ������ Ŀ������ ����������
		0, 0,//�̰� x,y �׸��� ũ���ε� �츮�� �־��� �ʿ� ����. ���Ͽ� �� ����Ÿ�� ������. 0�־��ָ� �˾Ƽ� ������ �޾ƿ�. 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION// �׸��� �о���� ��� 
	);
	// ���� ��������� �׸��� ����ϴ´ܰ��� ���� �׷����� �ƴϴ�. 

	// �׸��� �׷��ش�. ��� ? ���� DC�� �ƴ϶� �ٸ� �𾾿� 
	// �� ���� ��ȭ���� �׸��� �׷����� 
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	// �����ϰ��� �Ҷ� ���������� ����  ���� ���õ� Object�� ����� ����. 
	// �� ? ���� ���ǰ� �ִ� ��ü�� �Ժη� ���� �ϵ��� ������ �Ѽ� ���⶧���� ���� ������ ������ġ������ �����ϴ� ����. 

	// ���� �޾Ƶ� ���� OldBmp�� �־��ְ� 
	//1 �����̸� �ٲ�ġ�� �Ѵ�( ����ϰ� ����� ���� ����.)
	SelectObject(m_hMemDC, m_hOldBitmap);
	// ����ڰ� ���� Bitmap ������. 
	//2. ������ ��ü�� ���δ�. 
	DeleteObject(m_hBitmap);
	// �� ����� DC�� �����ִ� �� ������ ������� �Ѵ�. 
	//3. �״�� �������. 
	DeleteDC(m_hMemDC);
}
