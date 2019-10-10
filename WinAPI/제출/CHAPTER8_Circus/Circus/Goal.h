#pragma once
#include "GameDefine.h"

class Goal
{
private:
	int m_ix, m_iy; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // ���� �̹����� �� �� ũ��� �׸���

	RECT m_Rect; // �浹 ����

public:
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	RECT getRect();
	Goal();
	~Goal();
};