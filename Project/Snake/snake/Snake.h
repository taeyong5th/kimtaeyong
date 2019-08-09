#pragma once
#include "MapDraw.h"
#include "Block.h"

enum SNAKE_DIRECTION
{
	DIRECTION_NONE,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

enum SNAKE_ACTION
{
	SNAKE_ACTION_WAIT,
	SNAKE_ACTION_MOVE,
	SNAKE_ACTION_EAT
};

class Snake
{
private:
	MapDraw m_MapDraw;
	SNAKE_DIRECTION m_eDirection;
	Block *m_head;
	int m_iSpeed;

	void addHead(int x, int y); // x, y 위치에 머리를 추가
	void removeTail(); // 꼬리 하나를 지움
	void removeAllBlock(Block *head); // 재귀함수로 모든 블럭 지움
public:	
	void init(int x, int y); // x, y 위치로 뱀을 초기화 한다.
	void release(); // 동적할당된 리소스를 모두 반환

	void action(SNAKE_ACTION action); // 
	void draw(); // 뱀을 그린다.
	bool isSelfCollision(); // 뱀이 자기자신과 충돌하는지 검사
	bool isCollisiton(int x, int y); // x, y 위치에 뱀(머리, 몸통포함)이 있는지 검사
	
	int getX(); // 뱀 머리위치 x
	int getY(); // 뱀 머리위치 y
	void speedUp(); // 뱀 속도를 올린다.
	int getSpeed(); // 뱀 속도를 반환한다.
	void setDirection(SNAKE_DIRECTION dir); // 뱀이 나아갈 방향을 설정한다.
	SNAKE_DIRECTION getDirection();
	
public:
	Snake();
	~Snake();
};