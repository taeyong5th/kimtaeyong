#include "FireCircle.h"

void FireCircle::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_iAnimCount = 0;
	m_iCameraX = 0;
}

void FireCircle::update(int cameraX)
{
	m_iCameraX = cameraX;
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;
	if (m_fAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
	{
		m_fAnimTick = 0.0f;
		m_iAnimCount = ++m_iAnimCount % 2;
	}
	m_ix -= 3;
}

void FireCircle::draw(FIRE_CIRCLE loc)
{
	int width = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_L)->getWidth() * m_iMultiple;
	int height = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_L)->getHeight() * m_iMultiple;

	switch (loc)
	{
	case FIRE_L:
		BitmapManager::GetInstance()->prepare(m_aAnimationL[m_iAnimCount], m_ix - width / 2 - m_iCameraX, m_iy - height / 2, m_iMultiple, m_iMultiple);
		break;
	case FIRE_R:
		BitmapManager::GetInstance()->prepare(m_aAnimationR[m_iAnimCount], m_ix + width / 2 - m_iCameraX, m_iy - height / 2, m_iMultiple, m_iMultiple);
		break;
	}	
}

FireCircle::FireCircle()
{
	init(900, 270);
	m_aAnimationL[0] = IMG_ENEMY_L;
	m_aAnimationL[1] = IMG_ENEMY_L2;
	m_aAnimationR[0] = IMG_ENEMY_R;
	m_aAnimationR[1] = IMG_ENEMY_R2;
}

FireCircle::~FireCircle()
{
}
