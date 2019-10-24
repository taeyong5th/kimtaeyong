#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "GlobalDefine.h"

using namespace std;

class AstarNode
{
private:
	int _key; // 이 노드의 (x, y)위치
	int _from; // 부모 노드의 위치
	int _f, _g, _h;

public:
	AstarNode() { _f = _g = _h = 0; _key = _from = -1; };
	AstarNode(int key, int from, int g, int h) { this->_f = g + h; this->_g = g; this->_h = h; this->_key = key; this->_from = from; };
	~AstarNode() {};
	int f() { return _f; }
	int g() { return _g; }
	int h() { return _h; }
	int key() { return _key; }
	int from() { return _from; }
	//void print() { cout << "(" << _key / MAP_HEIGHT << "," << _key % MAP_HEIGHT << ") f,g,h = " << _f << ", " << _g << ", " << _h << endl; };
	bool operator > (const AstarNode& r) const { return _f > r._f; }
	bool operator < (const AstarNode& r) const { return _f < r._f; }
};

bool compareAstar(pair<int, AstarNode> a, pair<int, AstarNode> b)
{
	return a.second.f() < b.second.f();
}

int calcH(POINT from, POINT to)
{
	return abs(from.x - to.x) + abs(from.y - to.y);
}

bool isValidPoint(POINT p)
{
	if (p.x < 0) return false;
	if (p.y < 0) return false;
	if (p.x >= MAP_WIDTH) return false;
	if (p.y >= MAP_HEIGHT) return false;
	return true;
}

POINT keyToPoint(int key)
{
	POINT p;
	p.x = key / MAP_HEIGHT;
	p.y = key % MAP_HEIGHT;
	return p;
}

int PointToKey(POINT p)
{
	return p.x * MAP_HEIGHT + p.y;
}

// from -> to로 가기위해서 어느 방향으로 가야 하는지
MOVE_STATE direction(POINT from, POINT to)
{	
	if (from.x < to.x) return MOVE_STATE_RIGHT;
	if (from.x > to.x) return MOVE_STATE_LEFT;
	if (from.y > to.y) return MOVE_STATE_UP;
	if (from.y < to.y) return MOVE_STATE_DOWN;

	
	return MOVE_STATE_IDLE;
}
