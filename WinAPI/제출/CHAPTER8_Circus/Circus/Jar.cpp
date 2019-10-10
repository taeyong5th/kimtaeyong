#include "Jar.h"

void Jar::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
}

void Jar::update(int x, int y)
{
	init(x, y);

}

void Jar::draw()
{
	int width = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getWidth() * m_iMultiple;
	int height = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getHeight() * m_iMultiple;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;

	static int animCount = 0;

	if (m_fAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
	{
		m_fAnimTick = 0.0f;
		animCount = ++animCount % 2;
	}
	BitmapManager::GetInstance()->prepare(m_aAnimation[animCount], m_ix - width / 2, m_iy - height / 2, m_iMultiple, m_iMultiple);

}

Jar::Jar()
{
	init(0, 0);
	m_aAnimation[0] = IMG_ENEMY_JAR;
	m_aAnimation[1] = IMG_ENEMY_JAR2;
}

Jar::~Jar()
{
}
