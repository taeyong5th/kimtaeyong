#pragma once

#include "GameDefine.h"

class Background
{
private:
	int m_ix, m_iy; // 배경이 그려질 위치
	const float multiple = 2.0f; // 원본 이미지의 몇 배크기로 그릴지	
	const int bgWidth = WINDOW_WIDTH; // 

public:
	void init(int x, int y);
	void update(int x, int y);
	Background();
	~Background();
};
