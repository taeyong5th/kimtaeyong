#include "Point.h"
#include "MapDraw.h"

Point * createPoint(int x, int y, PointType type)
{
	Point* p = (Point*)malloc(sizeof(Point));
	p->x = x;
	p->y = y;
	p->type = type;
	return p;
}

void PrintPoint(Point * point)
{
	MapDraw mapDraw;
	switch (point->type)
	{
	case WALL:
		mapDraw.DrawPoint("¡á", point->x, point->y);
		break;
	case CHARACTER:
		mapDraw.DrawPoint("¡Ú", point->x, point->y);
		break;
	case GOAL:
		mapDraw.DrawPoint("£À", point->x, point->y);
		break;
	default:
		mapDraw.ErasePoint(point->x, point->y);
		break;
	}
}
