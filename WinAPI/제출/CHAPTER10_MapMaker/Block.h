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
	BLOCK_TYPE getData();
	void setData(BLOCK_TYPE data);
	void toggleNext();
	void draw(int top = 0, int left = 0);	
	
private:
	int m_ix;
	int m_iy;	
	BLOCK_TYPE m_iData; // -1이면 지뢰 0 이상이면 지뢰 개수	
	LPCWSTR getShape(); // 그려질 모양을 반환한다.	
};