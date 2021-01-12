#pragma once 

#include "../CrazyArcade/Obj.h"
#include "../CrazyArcade/Tile.h"


class CMyStrCmp
{
public:
	CMyStrCmp() {}
	CMyStrCmp(const TCHAR* pString)
		:m_pString(pString)
	{}
public:
	template<class T>
	bool operator()(T& rPair)
	{
		return !lstrcmp(rPair.first, m_pString);
	}
private:
	const TCHAR* m_pString;
};

template<class T>
bool CompareY(T Dst, T Src)
{
	if(Dst->m_bFlat == true)
		return true;
	/*
	if (Dst->m_bTop == true)
		return false;
	*/
	return Dst->Get_Info().fY < Src->Get_Info().fY;
}