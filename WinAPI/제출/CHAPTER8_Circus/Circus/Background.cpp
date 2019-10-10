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
}

void Background::draw()
{
	// ��� �׸���
	int bitmapWidth; // �� ��Ʈ��(����)�� ���� ����
	int tempX = m_ix; // �ڳ����� ������ �׷��� ��ġ�� ������ ����
	for (int i = 0; tempX < WINDOW_WIDTH; i++)
	{
		// 6��°���� �ڳ����� �׸���.
		if (i % 6 == 5)
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_ELEPHANT)->getWidth();
			BitmapManager::GetInstance()->prepare(IMG_BG_ELEPHANT, tempX, m_iy, m_iMultiple, m_iMultiple);
			tempX += bitmapWidth * m_iMultiple;
		}
		else
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_CROWD)->getWidth();
			BitmapManager::GetInstance()->prepare(IMG_BG_CROWD, tempX, m_iy + 3 * m_iMultiple, m_iMultiple, m_iMultiple);
			tempX += bitmapWidth * m_iMultiple;
		}

		// �ʷϻ� �ܵ� �׸���
		bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_GROUND)->getWidth();
		BitmapManager::GetInstance()->prepare(IMG_BG_GROUND, m_ix + (bitmapWidth * m_iMultiple * i), m_iy + 67 * m_iMultiple, m_iMultiple, m_iMultiple);
	}
}

Background::Background()
{
	

}

Background::~Background()
{
}
