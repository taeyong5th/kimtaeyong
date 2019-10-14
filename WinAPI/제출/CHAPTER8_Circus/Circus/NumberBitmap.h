#pragma once
#include "GameDefine.h"

class NumberBitmap
{
private:
	int m_ix, m_iy; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;

public:
	// Number�� x, y��ġ�� multiply���� ũ��� �׸���.
	void draw(int number, int x, int y, float multiply, UINT digits);
	NumberBitmap();
	~NumberBitmap();
};