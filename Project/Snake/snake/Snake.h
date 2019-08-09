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

	void addHead(int x, int y); // x, y ��ġ�� �Ӹ��� �߰�
	void removeTail(); // ���� �ϳ��� ����
	void removeAllBlock(Block *head); // ����Լ��� ��� �� ����
public:	
	void init(int x, int y); // x, y ��ġ�� ���� �ʱ�ȭ �Ѵ�.
	void release(); // �����Ҵ�� ���ҽ��� ��� ��ȯ

	void action(SNAKE_ACTION action); // 
	void draw(); // ���� �׸���.
	bool isSelfCollision(); // ���� �ڱ��ڽŰ� �浹�ϴ��� �˻�
	bool isCollisiton(int x, int y); // x, y ��ġ�� ��(�Ӹ�, ��������)�� �ִ��� �˻�
	
	int getX(); // �� �Ӹ���ġ x
	int getY(); // �� �Ӹ���ġ y
	void speedUp(); // �� �ӵ��� �ø���.
	int getSpeed(); // �� �ӵ��� ��ȯ�Ѵ�.
	void setDirection(SNAKE_DIRECTION dir); // ���� ���ư� ������ �����Ѵ�.
	SNAKE_DIRECTION getDirection();
	
public:
	Snake();
	~Snake();
};