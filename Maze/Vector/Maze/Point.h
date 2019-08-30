#ifndef __POINT_H__
#define __POINT_H__

enum PointType
{
	WALL,
	CHARACTER,
	GOAL,
	EMPTY
};

typedef struct _point
{
	int x;
	int y;
	PointType type;
} Point;

Point* createPoint(int x, int y, PointType type);
void PrintPoint(Point *point);


#endif