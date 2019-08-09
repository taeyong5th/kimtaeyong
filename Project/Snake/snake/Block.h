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

const string BLOCK_SHAPE_WALL = "■";
const string BLOCK_SHAPE_FOOD = "☆";
const string BLOCK_SHAPE_SNAKE = "○";
const string BLOCK_SHAPE_SNAKE_HEAD = "⊙";
const string BLOCK_SHAPE_NOTHING = "  ";

class Block
{
private:
	MapDraw m_DrawManager;
	BLOCK_STATE m_eState; // 블럭 상태
	int m_ix, m_iy; // 블럭의 x, y 위치
	string m_shape; // 블럭 모양	

public:
	Block* nextBlock; // 다음 블럭을 가리키는 포인터

	Block(BLOCK_STATE state, int x, int y);
	~Block();
	bool isCollision(const Block& block); // block과 충돌여부 검사
	void moveTo(int x, int y); // x, y 로 이동
	void draw(); // x, y 위치에 블럭을 그린다.
	void undraw(); // x, y 위치에 블럭을 지운다.	
	int getX(); // x 좌표를 반환
	int getY();  // y 좌표를 반환
	void setBlockState(BLOCK_STATE state); // 블럭 상태 정보를 변경한다.
};