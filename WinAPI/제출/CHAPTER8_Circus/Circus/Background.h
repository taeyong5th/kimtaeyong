#pragma once

#include "GameDefine.h"

class Background
{
private:
	int m_ix, m_iy; // 배경이 그려질 위치
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배크기로 그릴지	

public:
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	Background();
	~Background();
};
