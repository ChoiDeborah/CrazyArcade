#pragma once

#define WINCX			800
#define WINCY			600

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0
#define GRAVITY			9.8f

#define TILESIZEX		40.f
#define TILESIZEY		40.f

#define MAPSIZEX		600.f
#define MAPSIZEY		520.f

#define TILEX			15
#define TILEY			13

#define NUMOFTILE		15

#define OFFSET_X		20.f
#define OFFSET_Y		40.f

#define DegreeToRadian(Degree) Degree * 3.141592f / 180.f 
#define RadianToDegree(Radian) Radian * 180.f / 3.141592f

#define DECLARE_SINGLETON(Class)			\
private:									\
	Class();								\
	~Class();								\
public:										\
	static Class* Get_Instance()			\
	{										\
		if (nullptr == m_pInstance)			\
			m_pInstance = new Class;		\
											\
		return m_pInstance;					\
	}										\
	static void Destroy_Instance()			\
		{									\
			if (m_pInstance)				\
			{								\
				delete m_pInstance;			\
				m_pInstance = nullptr;		\
			}								\
	}										\
private:									\
	static Class* m_pInstance;

#define IMPLEMENT_SINGLETON(Class)			\
Class* Class::m_pInstance = nullptr; 
