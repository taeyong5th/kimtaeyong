#pragma once
#include "GlobalDefine.h"

enum BLOCK_TYPE
{
	BLOCK_TYPE_BLANK,
	BLOCK_TYPE_A,
	BLOCK_TYPE_U,
	BLOCK_TYPE_L,
	BLOCK_TYPE_D,
	BLOCK_TYPE_R,
	BLOCK_TYPE_GRAY,
	BLOCK_TYPE_FOREST,
	BLOCK_TYPE_WATER,
	BLOCK_TYPE_A_HARD,
	BLOCK_TYPE_U_HARD,
	BLOCK_TYPE_L_HARD,
	BLOCK_TYPE_D_HARD,
	BLOCK_TYPE_R_HARD,
	BLOCK_TYPE_MARK,
	BLOCK_TYPE_FLAG,
	BLOCK_COUNT
};

class Block
{
public:
	Block(int x, int y);
	~Block();
	const float multifly = 1.0f;
	BLOCK_TYPE getData();
	void setData(BLOCK_TYPE data);
	void draw();
	RECT getRect();
	void init();
	void Attacked(MOVE_STATE from); // from 방향으로부터 공격을 당함
	bool movable();
	
private:
	int m_ix;
	int m_iy;
	int m_iWidth, m_iHeight;

	BLOCK_TYPE m_iData; // 어떤 종류의 블럭인지
	LPCWSTR getShape(); // 그려질 모양을 반환한다.
};