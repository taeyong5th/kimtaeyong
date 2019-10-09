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
	// ��� �׸���
	int bitmapWidth; // �� ��Ʈ��(����)�� ���� ����
	int tempX = m_ix; // �ڳ����� ������ �׷��� ��ġ�� ������ ����
	for (int i = 0; tempX < bgWidth; i++)
	{
		// 6��°���� �ڳ����� �׸���.
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

		// �ʷϻ� �ܵ� �׸���
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
