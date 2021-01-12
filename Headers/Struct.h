#pragma once
typedef struct tagInfo
{
	// ��ü�� ��ǥ. 
	float fX; 
	float fY; 
	// ��ü�� ũ�� 
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
	int iFrameStart;// ���� ����. 
	int iFrameEnd; // ����
	int iFrameScene; // // y ��, ���°�. 
	DWORD dwFrameSpeed; //��� �ӵ�. 
	DWORD dwFrameTime; // �ð���. 

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