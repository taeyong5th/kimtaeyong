#pragma once
#include "GameDefine.h"

class ScoreUI
{
private:
	int m_ix, m_iy; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	NumberBitmap m_NumberBitmap;

public:
	// ����, �ְ�����, ��������� x, y��ġ�� multiply��� �׸���.
	void draw(int score, int maxScore, int cHeart, int x, int y, float multiply);
	ScoreUI();
	~ScoreUI();
};