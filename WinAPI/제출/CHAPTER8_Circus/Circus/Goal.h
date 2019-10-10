#pragma once
#include "GameDefine.h"

class Goal
{
private:
	int m_ix, m_iy; // 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배 크기로 그릴지

	RECT m_Rect; // 충돌 범위

public:
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	RECT getRect();
	Goal();
	~Goal();
};