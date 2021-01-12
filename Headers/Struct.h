#pragma once
typedef struct tagInfo
{
	// 객체의 좌표. 
	float fX; 
	float fY; 
	// 객체의 크기 
	float fCX;
	float fCY;
}INFO;
typedef struct tagLinePos
{
	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float x, float y)
		:fx(x)
		, fy(y)
	{}
	float fx; 
	float fy; 
}LINEPOS;

typedef struct tagLine
{
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOS& rLP, LINEPOS& rRP)
		:tLeftPoint(rLP)
		, tRightPoint(rRP)
	{}
	LINEPOS tLeftPoint;
	LINEPOS tRightPoint;
}LINEINFO;

typedef struct tagFrame
{
	int iFrameStart;// 시작 지점. 
	int iFrameEnd; // 끝점
	int iFrameScene; // // y 즉, 상태값. 
	DWORD dwFrameSpeed; //재생 속도. 
	DWORD dwFrameTime; // 시간값. 

}FRAME;

typedef struct tagIndex
{
public:
	tagIndex() {};
	tagIndex(int _x, int _y) :x(_x), y(_y) {};
	int x;
	int y;

	bool operator != (tagIndex& index)
	{
		if (x != index.x || y != index.y)
			return true;
		return false;
	}

	bool operator == (tagIndex& index)
	{
		if (x == index.x && y == index.y)
			return true;
		return false;
	}
}INDEX;

typedef struct tagPoint
{
public:
	tagPoint() {};
	tagPoint(float _x, float _y) :x(_x), y(_y) {};
	float x;
	float y;

	bool operator != (tagPoint& point)
	{
		if (x != point.x || y != point.y)
			return true;
		return false;
	}

	bool operator == (tagPoint& point)
	{
		if (x == point.x && y == point.y)
			return true;
		return false;
	}
}Point;

typedef struct tagMapInfo
{

	tagMapInfo() :bIsExist(false), bIsBoom(false) {}

	// Something exist on the map?
	bool bIsExist;
	// Is burning?
	bool bIsBoom;
	INDEX index;

}MAPINFO;