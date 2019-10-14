#include "ScoreUI.h"

void ScoreUI::draw(int score, int maxScore, int cHeart, int x, int y, float multiply)
{
	BitmapManager::GetInstance()->prepare(IMG_NOW, x + 50, y + 30, multiply, multiply);
	BitmapManager::GetInstance()->prepare(IMG_BEST, x + 400, y + 30, multiply, multiply);
	m_NumberBitmap.draw(score, x + 150, y + 30, multiply, 6);
	m_NumberBitmap.draw(maxScore, x + 500, y + 30, multiply, 6);

	for (int i = 0; i < MAX_HEART; ++i)
	{
		BitmapManager::GetInstance()->prepare(IMG_ICON_BLANK, WINDOW_WIDTH - 90 - i * 30, y + 35, multiply, multiply);
	}
	for (int i = 0; i < cHeart; ++i)
	{
		BitmapManager::GetInstance()->prepare(IMG_ICON, WINDOW_WIDTH - 90 - i * 30, y + 35, multiply, multiply);
	}
}

ScoreUI::ScoreUI()
{
}

ScoreUI::~ScoreUI()
{
}
