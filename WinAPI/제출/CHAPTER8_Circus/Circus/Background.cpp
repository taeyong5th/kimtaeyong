#include "Background.h"

void Background::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
}

void Background::update(int x, int y)
{
	m_ix = -x;
	m_iy = -y;
	// 배경 그리기
	int bitmapWidth; // 각 비트맵(원본)의 가로 길이
	int tempX = m_ix; // 코끼리와 관중이 그려질 위치를 저장할 변수
	for (int i = 0; tempX < bgWidth; i++)
	{
		// 6번째마다 코끼리를 그린다.
		if (i % 6 == 5)
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_ELEPHANT)->getWidth();
			BitmapManager::GetInstance()->prepare(IMG_BG_ELEPHANT, tempX, m_iy, multiple, multiple);
			tempX += bitmapWidth * multiple;
		}
		else
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_CROWD)->getWidth();
			BitmapManager::GetInstance()->prepare(IMG_BG_CROWD, tempX, m_iy + 3 * multiple, multiple, multiple);
			tempX += bitmapWidth * multiple;
		}

		// 초록색 잔디 그리기
		bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_GROUND)->getWidth();
		BitmapManager::GetInstance()->prepare(IMG_BG_GROUND, m_ix + (bitmapWidth * multiple * i), m_iy + 67 * multiple, multiple, multiple);
	}
}

Background::Background()
{
	

}

Background::~Background()
{
}
