#pragma once
#include "Mecro.h"
#include "GameDefine.h"
#include "MapDraw.h"

enum BLOCK_STATE
{
	BLOCK_STATE_WALL,
	BLOCK_STATE_FOOD,
	BLOCK_STATE_SNAKE,
	BLOCK_STATE_SNAKE_HEAD
};

const string BLOCK_SHAPE_WALL = "��";
const string BLOCK_SHAPE_FOOD = "��";
const string BLOCK_SHAPE_SNAKE = "��";
const string BLOCK_SHAPE_SNAKE_HEAD = "��";
const string BLOCK_SHAPE_NOTHING = "  ";

class Block
{
private:
	MapDraw m_DrawManager;
	BLOCK_STATE m_eState; // �� ����
	int m_ix, m_iy; // ���� x, y ��ġ
	string m_shape; // �� ���	

public:
	Block* nextBlock; // ���� ���� ����Ű�� ������

	Block(BLOCK_STATE state, int x, int y);
	~Block();
	bool isCollision(const Block& block); // block�� �浹���� �˻�
	void moveTo(int x, int y); // x, y �� �̵�
	void draw(); // x, y ��ġ�� ���� �׸���.
	void undraw(); // x, y ��ġ�� ���� �����.	
	int getX(); // x ��ǥ�� ��ȯ
	int getY();  // y ��ǥ�� ��ȯ
	void setBlockState(BLOCK_STATE state); // �� ���� ������ �����Ѵ�.
};