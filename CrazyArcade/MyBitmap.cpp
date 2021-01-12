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
	// 그림을 그릴려면 일단 해야하는 작업이 현재 내가 만든 DC를 현재 그려주고 있는 DC와 호환이 되게끔 만들어 줘야 한다. 
	// 그래서 DC를 얻어 오는중. 
	HDC hDC = GetDC(g_hWnd);//
							// 얻어온 디씨와 호환이 되게끔 만들어주는게 바로 CreateCompatibleDC
	m_hMemDC = CreateCompatibleDC(hDC); // 인자를 넘겨주면 현재 출력하고 있는 DC와 호환이 되는 메모리 DC를 할당해주는 함수. 
										// hDC는 더이상 할 역할이 없기에 그냥 과감하게 지워준다. 
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,//프로그램 인스턴스 핸들. 우리는 파일을 대상으로 얻어올것이기때문에 딱히 필요 없다. 
		pPath,// 파일의 경로 
		IMAGE_BITMAP,//비트맵인지 커서인지 아이콘인지
		0, 0,//이건 x,y 그림의 크기인데 우리가 넣어줄 필요 없다. 파일에 다 데이타가 있으니. 0넣어주면 알아서 사이즈 받아옴. 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION// 그림을 읽어오는 방식 
	);
	// 위의 여기까지가 그림을 등록하는단계지 아직 그려진게 아니다. 

	// 그림을 그려준다. 어디에 ? 현재 DC가 아니라 다른 디씨에 
	// 즉 예비 도화지에 그림을 그려놓고 
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	// 삭제하고자 할때 유의해햐할 사항  현재 선택된 Object는 지울수 없다. 
	// 왜 ? 현재 사용되고 있는 객체를 함부로 삭제 하도록 내버려 둘수 없기때문에 생긴 일종의 안전장치역할을 수행하는 규정. 

	// 내가 받아둔 더미 OldBmp를 넣어주고 
	//1 형준이를 바꿔치기 한다( 비슷하게 생긴놈 갖다 놓기.)
	SelectObject(m_hMemDC, m_hOldBitmap);
	// 사용자가 만든 Bitmap 지운후. 
	//2. 형준이 본체를 죽인다. 
	DeleteObject(m_hBitmap);
	// 다 사용한 DC를 지워주는 요 순서는 지켜줘야 한다. 
	//3. 그대로 사라진다. 
	DeleteDC(m_hMemDC);
}
