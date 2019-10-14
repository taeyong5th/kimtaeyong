#pragma once
#include "GameDefine.h"

class NumberBitmap
{
private:
	int m_ix, m_iy; // 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;

public:
	// Number를 x, y위치에 multiply배의 크기로 그린다.
	void draw(int number, int x, int y, float multiply, UINT digits);
	NumberBitmap();
	~NumberBitmap();
};