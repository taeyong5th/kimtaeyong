#include "Jar.h"

RECT Jar::getJarRect()
{
	RECT rect;
	rect.left = m_ix - m_iWidth / 3;
	rect.right = m_ix + m_iWidth / 3;
	rect.top = m_iy - m_iHeight / 3;
	rect.bottom = rect.top + m_iHeight;
	return rect;
}

void Jar::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getHeight() * m_iMultiple;
}

void Jar::update(int cameraX)
{
	m_iCameraX = cameraX;

	m_RectList.clear();
	m_RectList.push_back(getJarRect());
}

void Jar::draw()
{

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_JAR)->getHeight() * m_iMultiple;

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
	BitmapManager::GetInstance()->prepare(m_aAnimation[animCount], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
}

Jar::Jar()
{
	m_aAnimation[0] = IMG_ENEMY_JAR;
	m_aAnimation[1] = IMG_ENEMY_JAR2;
}

Jar::~Jar()
{
}
