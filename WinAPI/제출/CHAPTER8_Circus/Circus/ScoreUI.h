#pragma once
#include "GameDefine.h"

class ScoreUI
{
private:
	int m_ix, m_iy; // 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;
	NumberBitmap m_NumberBitmap;

public:
	// 점수, 최고점수, 목숨개수를 x, y위치에 multiply배로 그린다.
	void draw(int score, int maxScore, int cHeart, int x, int y, float multiply);
	ScoreUI();
	~ScoreUI();
};