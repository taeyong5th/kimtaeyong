#pragma once

#include "GameDefine.h"

class Background
{
private:
	int m_ix, m_iy; // ����� �׷��� ��ġ
	const float multiple = 2.0f; // ���� �̹����� �� ��ũ��� �׸���	
	const int bgWidth = WINDOW_WIDTH; // 

public:
	void init(int x, int y);
	void update(int x, int y);
	Background();
	~Background();
};
