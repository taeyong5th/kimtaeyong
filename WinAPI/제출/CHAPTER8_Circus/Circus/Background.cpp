#include "Background.h"

void Background::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_eAnim = BG_ANIM_STOP;
}

void Background::update(int x, int y)
{
	m_ix = -x;
	m_iy = -y;
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;
	if (m_fAnimTick > 0.1f) // 0.1�ʸ��� �׸� �̹��� ����
	{
		m_fAnimTick = 0.0f;
		m_iAnimCount = ++m_iAnimCount % 2;
	}
	// �ִϸ��̼��� ���� ���¸� 0��° �̹����θ� ����������
	if (m_eAnim == BG_ANIM_STOP)
	{
		m_iAnimCount = 0;
	}	
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
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(m_aAnimation[m_iAnimCount])->getWidth();
			BitmapManager::GetInstance()->prepare(m_aAnimation[m_iAnimCount], tempX, m_iy + 3 * m_iMultiple, m_iMultiple, m_iMultiple);
			tempX += bitmapWidth * m_iMultiple;
		}

		// �ʷϻ� �ܵ� �׸���
		bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_GROUND)->getWidth();
		BitmapManager::GetInstance()->prepare(IMG_BG_GROUND, m_ix + (bitmapWidth * m_iMultiple * i), m_iy + 67 * m_iMultiple, m_iMultiple, m_iMultiple);
	}
}

void Background::setAnimState(BG_ANIM anim)
{
	m_eAnim = anim;
}

Background::Background()
{

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fAnimTick = 0.0f;
	m_iAnimCount = 0;

	m_aAnimation[0] = IMG_BG_CROWD;
	m_aAnimation[1] = IMG_BG_CROWD2;

}

Background::~Background()
{
}
