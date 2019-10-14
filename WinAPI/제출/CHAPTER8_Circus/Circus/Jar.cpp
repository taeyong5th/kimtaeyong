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

	m_eAnim = JAR_ANIM_START;
	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fAnimTick = 0.0f;

	m_RectList.clear();
	m_RectList.push_back(getJarRect());
	m_bScoreAcquired = false;
}

void Jar::update(int cameraX)
{
	m_iCameraX = cameraX;
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;
	
	if (m_eAnim == JAR_ANIM_START && m_fAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
	{
		m_fAnimTick = 0.0f;
		m_iAnimCount = ++m_iAnimCount % 2;
	}	
	
	m_RectList.clear();
	m_RectList.push_back(getJarRect());
	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}

void Jar::draw()
{

	BitmapManager::GetInstance()->prepare(m_aAnimation[m_iAnimCount], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
	
}

void Jar::setAnimation(JAR_ANIM anim)
{
	m_eAnim = anim;
}

Jar::Jar()
{
	m_aAnimation[0] = IMG_ENEMY_JAR;
	m_aAnimation[1] = IMG_ENEMY_JAR2;
	m_eAnim = JAR_ANIM_START;
	m_iAnimCount = 0;
}

Jar::~Jar()
{
}
