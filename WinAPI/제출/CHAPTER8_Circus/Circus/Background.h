#pragma once

#include "GameDefine.h"

class Background
{
private:
	int m_ix, m_iy; // ����� �׷��� ��ġ
	const float m_iMultiple = 2.0f; // ���� �̹����� �� ��ũ��� �׸���	

public:
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	Background();
	~Background();
};
